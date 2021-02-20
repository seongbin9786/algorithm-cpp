#include "problem_81.hpp"

/*
유형: Graph
[풀이 전략]

벨만 포드 알고리즘

음의 사이클만 없으면 음수 가중치 포함한 최단 경로 발견 가능

일단 따라치는 것으로 시작

*/
struct Edge81
{
    int u, v, cost;

    Edge81(int u, int v, int cost)
    {
        this->u = u;
        this->v = v;
        this->cost = cost;
    }

    // PQ를 안 쓰므로 비교 연산자 오버로딩하지 않음
};

void problem_81()
{
    ios_base::sync_with_stdio(false);
    READ_TXT("./resources/input81.txt", "rt", stdin);
    vector<Edge81> arr;
    int dist[101];
    int i, j, n, m, a, b, c, u, v;
    const int INF = 99999;
    cin >> n >> m;
    for (i = 1; i <= m; i++)
    {
        cin >> a >> b >> c;
        arr.push_back(Edge81(a, b, c));
    }
    for (i = 1; i <= n; i++)
        dist[i] = INF;

    cin >> u >> v;
    dist[u] = 0;            // 방문할 노드
    for (i = 1; i < n; i++) // 1~n-1
        for (j = 0; j < arr.size(); j++)
        {
            a = arr[j].u;
            b = arr[j].v;
            c = arr[j].cost;
            if (dist[a] != INF && dist[a] + c < dist[b])
                dist[b] = dist[a] + c;
        }
    for (i = 0; i < arr.size(); i++)
    {

        a = arr[i].u;
        b = arr[i].v;
        c = arr[i].cost;
        if (dist[a] != INF && dist[a] + c < dist[b])
        {
            cout << "-1\n";
            exit(0);
        }
    }
    cout << dist[v] << "\n";
}
