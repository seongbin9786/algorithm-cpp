#include <stdio.h>
#include <stack>
#include "../include/debugopen.hpp"

/*
    [Silver 2]
    침투
    https://www.acmicpc.net/problem/13565

    인제대학교 생화학연구실에 재직중인 석교수는 전류가 침투(percolate) 할 수 있는 섬유 물질을 개발하고 있다. 
    이 섬유 물질은 2차원 M × N 격자로 표현될 수 있다. 
    편의상 2차원 격자의 위쪽을 바깥쪽(outer side), 아래쪽을 안쪽(inner side)라고 생각하기로 한다. 

    또한 각 격자는 검은색 아니면 흰색인데, 검은색은 전류를 차단하는 물질임을 뜻하고 흰색은 전류가 통할 수 있는 물질임을 뜻한다. 
    전류는 섬유 물질의 가장 바깥쪽 흰색 격자들에 공급되고, 이후에는 상하좌우로 인접한 흰색 격자들로 전달될 수 있다.

    김 교수가 개발한 섬유 물질을 나타내는 정보가 2차원 격자 형태로 주어질 때, 
    바깥쪽에서 흘려 준 전류가 안쪽까지 침투될 수 있는지 아닌지를 판단하는 프로그램을 작성하시오.

    예를 들어, Figure 1(a) 에서는 바깥쪽에서 공급된 전류가 안쪽까지 침투하지만, Figure 1(b)에서는 그렇지 못한다.


    ---
    첫째 줄에는 격자의 크기를 나타내는  M (2 ≤ M ≤ 1,000) 과 N (2 ≤ N ≤ 1,000) 이 주어진다. 
    M줄에 걸쳐서, N개의 0 또는 1 이 공백 없이 주어진다. 
    0은 전류가 잘 통하는 흰색, 1은 전류가 통하지 않는 검은색 격자임을 뜻한다.

    ---
    바깥에서 흘려준 전류가 안쪽까지 잘 전달되면 YES를 출력한다.그렇지 않으면 NO를 출력한다.


    => 그래프를 구성하고, DFS/BFS를 수행해 M행에 닿기만 하면 된다.
    => MxN 행렬을 탐색하면 된다. 그냥 완전 탐색이다.
    => 맨 윗 행렬의 각 점에서 출발하면 된다.
    => 탐색하던중 도달하는 순간 YES고, 다 돌아서 나오면 NO를 출력하면 된다.
    => 좌표를 [1,M] 형태로 표현하면 좋겠다.
*/

using namespace std;

// 동서남북
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

int main()
{
    int i, j, M, N;
    stack<pair<int, int>> S;
    READ_TXT("./input.txt", "rt", stdin);
    //[1,M][1,N]으로 배열 초기화
    scanf("%d %d", &M, &N);
    char tmp[N + 1];
    bool map[M + 1][N + 1] = {0};
    bool visited[M + 1][N + 1] = {0};
    for (i = 1; i <= M; i++)
    {
        scanf("%s", tmp);
        for (j = 1; j <= N; j++)
            map[i][j] = tmp[j - 1] == '0' ? 1 : 0; // 0 이어야 전류가 통한다고 한다.
    }
    // dfs 문제니까 dfs 사용
    // x: [1,1]~[1,N] 부터 시작.
    for (i = 1; i <= N; i++)
    {
        if (!map[1][i])
            continue;
        S.push(make_pair(1, i)); // [y,x]
        while (S.size() > 0)
        {
            int x, y, nx, ny;
            y = S.top().first;
            x = S.top().second;
            S.pop();
            visited[y][x] = true;
            if (y == M) // 바닥에 닿음.
            {
                printf("YES\n");
                return 0;
            }
            for (j = 0; j < 4; j++)
            {
                nx = x + dx[j];
                ny = y + dy[j];
                if (nx < 1 || nx > N || ny < 1 || ny > M)
                    continue;
                if (visited[ny][nx])
                    continue;
                if (!map[ny][nx])
                    continue;
                S.push(make_pair(ny, nx));
            }
        }
    }
    printf("NO\n");
    return 0;
}
