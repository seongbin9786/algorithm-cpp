#include <iostream>
#include <queue>
#include "../include/debugopen.hpp"

/*
	[Silver 1]
	안전 영역

	1. 일정한 높이 이하의 모든 지점은 물에 잠긴다
	2. 높이 정보는 행과 열의 크기가 각각 N <= 100인 2차원 배열 형태
	3. 각 원소는 해당 지점의 높이 1<=M<=100
	4. 안전 영역은 물에 잠기지 않는 지점들이 위, 아래, 오른쪽 혹은 왼쪽으로 인접해 있으며 그 크기가 최대인 영역
	5. 아무 지역도 물에 잠기지 않을 수도 있다.

	[출력]
	어떤 지역의 높이 정보가 주어졌을 때, 장마철에 물에 잠기지 않는 안전한 영역의 최대 개수
	
	---
	IDEA:
	비오는 높이는 1~max(M)개가 될 수도 있다.
	(비오는 높이가 0이면 안전 영역은 1개임)

	1. 높이를 1씩 증가시키면서 전체 원소에서 높이를 빼준 상태로 DFS/BFS 해서 영역의 개수를 센다.

	그냥 이렇게 풀어도 N<=100이어서 가능할 것 같다.

	---
	81% 에서 틀렸습니다.
	[1] 조건 다시 확인하기 (v)
	[2] 나름의 최적화 시도해보기 (v) // 이건 필요 없었을듯
	[3] 논리가 틀렸나 확인하기 // 1,1 일 때 회피 해봤는데 된다.. 아니, 비가 안 올수도 있는거임; 하
*/

#define N 100

using namespace std;

// [y,x] = 동서남북
// [x,y] = 북남서동
const int px[] = {1, -1, 0, 0};
const int py[] = {0, 0, -1, 1};
int SIZE, cur_island, cur_height;

int visited2468[N][N] = {0}; // 시간 절약 아이디어
int matrix2468[N][N] = {0};

void DFS(int x, int y)
{
    if (visited2468[x][y] >= cur_height)
        return;

    visited2468[x][y] = cur_height;
    // printf("visiting (%d, %d) at height of %d\n", x, y, matrix2468[x][y] - cur_height);
    for (int i = 0; i < 4; i++)
    {
        int nx = x + px[i];
        int ny = y + py[i];
        if (nx < 0 || ny < 0 || nx >= SIZE || ny >= SIZE)
            continue;
        // visited 초기화 안 하기 전략: true 대신 cur_height 값으을 할당하면 됨
        if (visited2468[nx][ny] >= cur_height || matrix2468[nx][ny] - cur_height <= 0)
            continue;
        DFS(nx, ny);
    }
}

int main()
{
    int i, j, tmp, max = 0, max_island = 1; // 1,1 일 때 회피
    READ_TXT("./input.txt", "rt", stdin);
    cin >> SIZE;
    // (x, y)로 하지 않고, 그냥 범위만 [Y, X]로 쓰고 나머진 그냥 써도 된다! (신기하당)
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            cin >> tmp;
            matrix2468[i][j] = tmp;
            max = max < tmp ? tmp : max; // max 높이 구하기
        }
    }

    // max까지 오면 0임
    for (cur_height = 1; cur_height < max; cur_height++)
    {
        cur_island = 0;
        // 가능한 모든 칸에 대해 BFS,DFS로 완전 탐색 시도
        for (i = 0; i < SIZE; i++)
            for (j = 0; j < SIZE; j++)
                if (visited2468[i][j] < cur_height && matrix2468[i][j] - cur_height > 0)
                {
                    DFS(i, j); // 같은 영역 내의 모든 노드에 대해 visited 설정만
                    cur_island++;
                }
        max_island = max_island < cur_island ? cur_island : max_island;
        // visited 초기화
        //for (i = 0; i < SIZE; i++)
        //	for (j = 0; j < SIZE; j++)
        //		visited2468[i][j] = false;
    }
    cout << max_island << "\n";
    return 0;
}
