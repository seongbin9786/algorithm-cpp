#include <iostream>

#include "../include/debugopen.hpp"

/*
	[Silver 2]
    외판원 순회2

    - 1번부터 N번까지 번호가 매겨져 있는 도시들이 있고, 도시들 사이에는 길이 있다. (길이 없을 수도 있다) 
        - N <= 10
        
    - N개의 도시를 한 번씩만 거쳐 원래의 도시로 돌아오는 경로

    - 가장 적은 비용을 소모하는 경로를 찾고 최소 비용을 출력

    - 대칭적이지 않은 비용

    - 어느 한 도시에서 출발 (즉 상관 없음)

    -----
    [IDEA]
    1. 각 도시에서 출발해봐야 함 (for 문 사용하면 되겠다.)

    2. 이것도 순열 출력과 동일하다.
    - 대신 제약이 있는 게, 현재 도시에서 연결된 도시만 방문할 수 있다는 것임
    - case 1) 모든 도시를 방문할 수 있는 순서였음 => sum 구한 후 min 갱신
    - case 2) 모든 도시를 방문할 수 없는 순서였음 => 버림

    3. 다시 돌아와야 하는 게 어렵다. 흠?
    => 자동으로 다시 돌아오는 코스가 만들어지도록 할 수는 없을까?
    => 
*/
using namespace std;

int map[10][10] = {0};
int seq[10] = {0};
bool visited[10] = {0};
int N;
int minCost = INT32_MAX;

void backtrack(int curIdx, int begin)
{
    int i, sum, cur;

    // 순열을 완성했을 때
    if (curIdx == N)
    {
        sum = 0;
        for (i = 0; i < N - 1; i++)
        {
            cur = map[seq[i]][seq[i + 1]];
            if (cur == 0)
                return; // 중간에 길이 없음
            sum += cur;
        }
        cur = map[seq[i]][begin];
        if (cur == 0)
            return; // 마지막에 길이 없음
        sum += cur; // 마지막 원소와 시작 지점 연결
        if (sum < minCost)
            minCost = sum;
        for (i = 0; i < N - 1; i++)
            cout << map[seq[i]][seq[i + 1]] << " + "; // (0,1), (1,2), (2,3) 아 이렇게? ㅇㅋ 이게 맞긴하네
        cout << map[seq[i]][begin] << " = " << minCost << "\n";
        return;
    }

    for (i = 0; i < N; i++)
    {
        if (visited[i])
            continue;

        // 완전 탐색
        visited[i] = true;
        seq[curIdx] = i;
        backtrack(curIdx + 1, begin);
        visited[i] = false;
        seq[curIdx] = 0;
    }
}

int main()
{
    int i, j;
    READ_TXT("./input.txt", "rt", stdin);
    cin >> N;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            cin >> map[i][j];

    // 시작 점은 마지막으로 방문하기 때문에
    for (i = 0; i < N; i++)
    {
        visited[i] = true;
        seq[0] = i;
        backtrack(1, i);
        visited[i] = false;
        seq[0] = 0;
    }
    cout << minCost << "\n";
}
