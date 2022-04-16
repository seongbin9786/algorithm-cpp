#include "problem_79.hpp"

/*
유형: Graph
[풀이 전략]

Prim MST는 Union-Find를 사용하지 않고, 완전 탐색하면서 간선 중 일부만 방문한다.
간선 방문은 최소 비용을 우선으로 탐색하며 모든 정점이 탐색되면 종료한다.
각 정점을 방문할 때 인접 정점으로의 비용을 확인해 인접 행렬(or 리스트)에 갱신하고,
다음 정점 방문 시 min 정점으로 바로 이동한다.

즉, [정점 방문] -> [인접 정점 비용 갱신] -> [최소 비용 정점 방문] -> [총 비용에 간선 비용 추가] -> (반복)

Priority Queue 도 사용하지 않는다. 대신 방문 여부와 인접 행렬이 필요하다.

---
[강의 구현]
PQ를 써도 된다. 아마 getMinVertex를 PQ로 구현하는 듯하다.
다만 굳이 PQ를 쓸 필요가 없어서...
*/

const int INF79 = 99999;
bool visited79[101] = {0}; // 0은 false나 마찬가지
int adj79[101][101];       // = {INF79}; 로 쓰면 첫 상수만 INF고 나머진 0이 됨;;
int dist79[101];
int sum79 = 0;

int getMinVertex(int vsize)
{
    // !visited && min dist로 고르면 되는거 아닌가? ㅇㅇ 방문 비용 최소인 v를 반환하는 게 핵심
    int i, minv = INF79, mindist = INF79; // minv를 INF로 놓는 이유는 더 이상 방문할 정상 정점이 없다는 뜻

    for (i = 1; i <= vsize; i++)
    {
        if (visited79[i])
            continue;
        if (dist79[i] >= mindist)
            continue;
        mindist = dist79[i];
        minv = i;
    }
    if (minv < INF79)
        sum79 += mindist; // 여기서 sum 계산 해야 함
    return minv;
}

void problem_79()
{
    ios_base::sync_with_stdio(false);
    int i, j, u, v, e, a, b, c;
    READ_TXT("./resources/input78.txt", "rt", stdin);
    cin >> v >> e;
    for (i = 1; i <= v; i++)
        dist79[i] = INF79; // dist도 갱신될 거기 때문에 INF여야 의미 있게 됨
    for (i = 1; i <= v; i++)
        for (j = 1; j <= v; j++)
            adj79[i][j] = INF79; // adj에서 INF는 비연결을 의미함. cost가 음수일 수도 있어서 0으론 안 됨.
    for (i = 1; i <= e; i++)
    {
        cin >> a >> b >> c;
        adj79[a][b] = c; // 인접 행렬 초기화
        adj79[b][a] = c; // 양방향 간선 (이거 해야 되는거네; 아우)
    }

    // 1. 시작 정점 = 1
    dist79[1] = 0;

    // 2. 순회하며 최저 비용 정점 확인
    for (i = 1; i <= v; i++)
    {
        u = getMinVertex(v); // 3. 최소 정점 반환 (v는 개수 때문에 넘김)
        visited79[u] = true;
        if (dist79[u] == INF79)
            return; // 4. 이제 갈 수 없는 정점만 남은 경우

        // 5. 인접 정점으로 더 작은 비용을 발견한 경우 dist79 갱신 (다익스트라 유사)
        // Q. 이것도 O(V) 로 치나? 인접 행렬로 구현해서 괜히 시간복잡도만 늘어난 것일 수 있음
        for (j = 1; j <= v; j++)
            if (adj79[u][j] < INF79 && !visited79[j] && adj79[u][j] < dist79[j])
                dist79[j] = adj79[u][j];
    }

    cout << sum79 << "\n";
}