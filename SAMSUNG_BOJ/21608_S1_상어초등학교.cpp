#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include "../include/debugopen.hpp"

using namespace std;

typedef struct
{
    int y;
    int x;
} Loc;

int table[21][21] = {0};
int N;
vector<int> students;

vector<Loc> findBestLocsForStudent(int studentIdx)
{
    int i, y, x, cnt, maxCnt = 0;
    vector<Loc> bests;

    // 테이블의 빈 자리 순회
    for (y = 0; y < N; y++)
    {
        for (x = 0; x < N; x++)
        {
            if (table[y][x] != 0)
                continue;

            // 주변 상하좌우를 확인해 좋아하는 학생의 수를 센다.
            cnt = 0;
            for (i = 1; i <= 4; i++)
            {
                if (y > 0 && table[y - 1][x] == students[studentIdx + i])
                    cnt++;
                if (y < N - 1 && table[y + 1][x] == students[studentIdx + i])
                    cnt++;
                if (x > 0 && table[y][x - 1] == students[studentIdx + i])
                    cnt++;
                if (x < N - 1 && table[y][x + 1] == students[studentIdx + i])
                    cnt++;
            }

            if (cnt < maxCnt)
            {
                printf("[studentIdx=%d] (%d, %d)은 cnt < maxCnt 이므로 삽입하지 않음.\n", studentIdx, y + 1, x + 1);
                continue; // maxCnt 보다 작은 경우는 필요 없음.
            }

            if (cnt > maxCnt)
            {
                printf("[studentIdx=%d] (%d, %d)은 cnt(%d) > maxCnt(%d) 이므로 모두 제거함.\n", studentIdx, y + 1, x + 1, cnt, maxCnt);
                maxCnt = cnt;
                bests.clear(); // 이전에 삽입된 모든 원소를 제거한다.
            }

            // cnt >= 이면 삽입
            bests.push_back({y, x});
            printf("[studentIdx=%d] (%d, %d)에서 cnt=%d 이어서 삽입함\n", studentIdx, y + 1, x + 1, cnt);
        }
    }
    return bests;
}

// 1의 후보가 여럿이면 인접한 칸 중에서 비어있는 칸이 가장 많은 칸으로 결정한다.
vector<Loc> findMostEmptyLocsAmongLocs(vector<Loc> bests)
{
    int i, cnt, maxCnt = 0;
    vector<Loc> empties;

    // 테이블의 빈 자리 순회
    for (i = 0; i < bests.size(); i++)
    {
        auto [y, x] = bests[i];

        // 주변 상하좌우를 확인해 빈 칸의 수를 센다.
        cnt = 0;
        if (y > 0 && table[y - 1][x] == 0)
            cnt++;
        if (y < N - 1 && table[y + 1][x] == 0)
            cnt++;
        if (x > 0 && table[y][x - 1] == 0)
            cnt++;
        if (x < N - 1 && table[y][x + 1] == 0)
            cnt++;

        if (cnt < maxCnt)
        {
            printf("(%d, %d)은 cnt < maxCnt 이므로 삽입하지 않음.\n", y + 1, x + 1);
            continue; // maxCnt 보다 작은 경우는 필요 없음.
        }

        if (cnt > maxCnt)
        {
            printf("(%d, %d)은 cnt(%d) > maxCnt(%d) 이므로 모두 제거함.\n", y + 1, x + 1, cnt, maxCnt);
            maxCnt = cnt;
            empties.clear(); // 이전에 삽입된 모든 원소를 제거한다.
        }

        // cnt >= 이면 삽입
        empties.push_back(bests[i]);
        printf("(%d, %d)에서 cnt=%d 이어서 삽입함\n", y + 1, x + 1, cnt);
    }
    return empties;
}

bool cmpEarliest(const Loc &a, const Loc &b)
{
    // [y, x] 로 배치가 된다.
    // 행의 번호가 작다 => y가 작다.
    // 열의 번호가 작다 => x가 작다.

    // < 로 반환하면 오름차순 반환 (작은 순으로 반환)
    if (a.y == b.y)
        return a.x < b.x;
    return a.y < b.y;
}

// 2를 만족하는 칸도 여러 개인 경우에는 행의 번호가 가장 작은 칸으로,
// 그러한 칸도 여러 개이면 열의 번호가 가장 작은 칸으로 자리를 정한다.
Loc findEarliestLocAmongLocs(vector<Loc> empties)
{
    printf("[findEarliest] size: %d, arr[0]: (%d, %d) ---->", empties.size(), empties[0].y + 1, empties[0].x + 1);
    sort(empties.begin(), empties.end(), cmpEarliest);
    printf("arr[0]: (%d, %d)\n", empties[0].y + 1, empties[0].x + 1);
    return empties[0];
}

typedef struct
{
    int y;
    int x;
    int idx;
} MapIdx;

map<int, MapIdx> mapping;

// 만족도 계산 함수의 구현
int satisfactionPointsMapping[] = {0, 1, 10, 100, 1000};

int calcSatisfactionOfStudent(int studentId)
{
    // 이게 되는 문법인지는 모르겠음.
    // 그냥 MapIdx struct로 받아와도 될듯.
    // C++ 17부터 되는 거 같기도 함.. (나는 C++14 이고 대부분 14 지원일듯?)
    auto [y, x, idx] = mapping[studentId];

    int cnt = 0;
    for (int i = 1; i <= 4; i++)
    {
        if (y > 0 && table[y - 1][x] == students[idx + i])
            cnt++;
        if (y < N - 1 && table[y + 1][x] == students[idx + i])
            cnt++;
        if (x > 0 && table[y][x - 1] == students[idx + i])
            cnt++;
        if (x < N - 1 && table[y][x + 1] == students[idx + i])
            cnt++;
    }
    return satisfactionPointsMapping[cnt];
}

int main()
{
    int i, x;
    READ_TXT("input.txt", "rt", stdin);

    scanf("%d", &N);
    for (i = 0; i < 5 * N * N; i++)
    {
        scanf("%d", &x);
        students.push_back(x);
    }

    // 1~3번 규칙 적용
    int curStudent, curStudentIdx;
    for (i = 0; i < N * N; i++)
    {
        curStudentIdx = i * 5;
        curStudent = students[curStudentIdx];
        printf("curStudent: %d, curStudentIdx: %d\n", curStudent, curStudentIdx);
        vector<Loc> bests = findBestLocsForStudent(curStudentIdx);
        if (bests.size() == 1)
        {
            table[bests[0].y][bests[0].x] = curStudent;
            mapping.insert({curStudent, {bests[0].y, bests[0].x, curStudentIdx}});
            printf("1번 규칙에서 종료\n");
            continue;
        }
        printf("2번 규칙 시작\n");
        vector<Loc> empties = findMostEmptyLocsAmongLocs(bests);
        if (empties.size() == 1)
        {
            table[empties[0].y][empties[0].x] = curStudent;
            mapping.insert({curStudent, {empties[0].y, empties[0].x, curStudentIdx}});
            printf("학생 %d를 (%d, %d)에 삽입하고 2번 규칙에서 종료\n", curStudent, empties[0].y + 1, empties[0].x + 1);
            continue;
        }

        Loc earliest = findEarliestLocAmongLocs(empties);
        table[earliest.y][earliest.x] = curStudent;
        mapping.insert({curStudent, {earliest.y, earliest.x, curStudentIdx}});
        printf("3번 규칙에서 종료\n");
    }

    // 배치된 학생들의 만족도 계산
    int satisfaction = 0;
    for (i = 0; i < N * N; i++)
    {
        curStudentIdx = i * 5;
        satisfaction += calcSatisfactionOfStudent(students[curStudentIdx]);
    }

    printf("%d\n", satisfaction);
}
