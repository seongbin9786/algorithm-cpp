#include "problem_80.hpp"

/*
유형: 
[풀이 전략]

*/
struct cmpPairSecond
{
    //연산자 오버로딩
    //얘는 기준이 less일까 greater일까 (그냥 해 보면 됨 ㅇㅅㅇ)
    // > 로 계산하면 오름차순으로 정렬되는듯
    bool operator()(pair<int, int> &a, pair<int, int> &b)
    {
        return a.second > b.second;
    }
};

void problem_80pq()
{
    ios_base::sync_with_stdio(false);
    READ_TXT("./resources/input80.txt", "rt", stdin);
    // PQ로 간선
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmpPairSecond> pq;
    int u, v, ucost, vcost, i, n, m, a, b, c;
    const int INF = 99999;
    bool visited[21] = {false};
    int dist[21];                     // INF 초기화 필요
    vector<pair<int, int>> graph[21]; // 연결 리스트 생성
    cin >> n >> m;
    for (i = 1; i <= n; i++)
        dist[i] = INF;
    for (i = 1; i <= m; i++)
    {
        cin >> a >> b >> c;
        graph[a].push_back(make_pair(b, c)); // 연결 리스트
    }
    pq.push(make_pair(1, 0)); // 1번 노드의 방문 가격 0
    dist[1] = 0;
    while (!pq.empty())
    {
        // 현재 노드
        int u = pq.top().first;
        int ucost = pq.top().second;
        pq.pop();

        if (ucost > dist[u])
            continue; // 해당 간선은 고려하면 안 됨. 최적 X

        // 연결 리스트 순회
        for (i = 0; i < (int)graph[u].size(); i++)
        {
            // 인접 노드 확인 중.
            v = graph[u][i].first;
            vcost = ucost + graph[u][i].second;

            // 인접 노드로 갱신 + 해당 간선 방문을 위해 PQ에 추가함
            // => 이렇게 PQ에 추가되지 않는 간선은 방문되지 않게 됨 (u는 이미 방문했으니까)
            if (dist[v] > vcost)
            {
                dist[v] = vcost;
                pq.push(make_pair(v, vcost)); // Q. 이걸 푸시하는 이유?
            }
        }
    }
    for (i = 2; i <= n; i++)
        if (dist[i] == INF)
            cout << i << " : impossible\n";
        else
            cout << i << " : " << dist[i] << "\n";
}
