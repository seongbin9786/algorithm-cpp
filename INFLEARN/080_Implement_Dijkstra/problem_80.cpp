#include "problem_80.hpp"

/*
유형: Graph
[풀이 전략]

단순 다익스트라 구현
다만 안 보고 정확하게 구현하기는 아직 좀 어렵다

IDEA:
1. 음수 가중치 없는 그래프
2. 시작 정점에서 나머지 모든 정점까지의 거리와 경로를 구하는 알고리즘
3. 각 정점을 방문할 때마다 현재정점+간선비용 vs 현재dist 비교해서 dist 갱신
4. dist 중 최소 비용인 정점 방문
*/

void problem_80()
{
    ios_base::sync_with_stdio(false);
    READ_TXT("./resources/input80.txt", "rt", stdin);
    int dist[21];               // INF로 초기화해야 함
    bool visited[21] = {false}; // false로 초기화
    //int path[21];               // 초기화 필요 없음 (근데 이 문제에선 아예 필요도 없음)
    int adj[21][21]; // INF로 초기화해야 함 (인접 행렬)
    const int INF = 9999;
    int i, j, n, m, a, b, c, minv, mindist;
    cin >> n >> m;
    // INF 초기화
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            adj[i][j] = INF;
    for (i = 1; i <= n; i++)
        dist[i] = INF;
    // 인접 행렬 초기화 (단방향) <------------- 중요 (이 문제에선)
    for (i = 1; i <= m; i++)
    {
        cin >> a >> b >> c;
        adj[a][b] = c;
    }
    // 2. SET node #1 to be the one being reached next
    dist[1] = 0;
    visited[1] = true;

    // 3. UPDATE adj nodes' costs
    for (i = 1; i <= n; i++)
    {
        minv = 1;
        mindist = INF;
        // 4. find min vertex by comparing mindist
        for (j = 2; j <= n; j++)
        {
            if (!visited[j] && dist[j] < mindist)
            {
                minv = j;
                mindist = dist[j];
            }
        }
        visited[minv] = true;
        // 5. Visit and Update Costs if possible
        for (j = 1; j <= n; j++)
        {
            if (!visited[j] && dist[minv] + adj[minv][j] < dist[j])
            {
                dist[j] = dist[minv] + adj[minv][j];
                // path[j] = minv; // parent 느낌으로 이렇게 저장하면 나중에 역순으로 path 파악 가능
            }
        }
    }

    // 5. 출력하면 끝
    for (i = 2; i <= n; i++)
        if (dist[i] == INF)
            cout << i << " : impossible\n";
        else
            cout << i << " : " << dist[i] << "\n";
}
