#include "problem_78.hpp"

/*
유형: Graph
[풀이 전략]

1. 간선을 PQ로 cost에 대해 오름차순으로 정렬해 저장한다.
2. 하나씩 pop() 한다.
3. 현재 간선을 그래프에 추가한 후 Union-Find를 통해 사이클을 확인한다.
- 현재 완전 그래프이고, 새로 들어올 점이 현재 그래프에 포함되지 않은 경우 사이클이 안 생김.
4. [2~3]을 MST가 될 때까지 반복한다. ( 간선 개수 = 노드 개수 - 1)

*/
int unf78[1001] = {0}; // C++은 자동으로 0으로 초기화되는건가? 잘 모르겠음

int Find78(int v)
{
    return v == unf78[v] ? v : Find78(unf78[v]); // 내 주인을 따라감 /내가 주인이면 반환
}

// 다른 집합에 속하는 경우 u의 root를 v로 만들어 통합함.
void Union78(int u, int v)
{
    u = Find78(u);
    v = Find78(v);

    if (u == v)
        return;

    unf78[u] = v;
}

struct Edge78
{
    int u, v, cost;

    Edge78(int u, int v, int cost)
    {
        this->u = u;
        this->v = v;
        this->cost = cost;
    }

    // 아직도 뭔지 모르겠음 a < b 이면 true 반환인 거 같은데? ㅇㅇ
    // operator> 가 greater에 사용되고 operator<가 less에 사용되는듯
    bool operator>(const Edge78 &b) const
    {
        return cost > b.cost;
    }
}; // 세미 콜론이 꼭 있어야 함. 아니면 Syntax Error

void problem_78()
{
    ios_base::sync_with_stdio(false);
    priority_queue<Edge78, vector<Edge78>, greater<Edge78>> pq; // less가 기본값. greater로 오름차순 정렬하게 함. (vector가 기본 구현)
    int i, v, e, a, b, c, accepted = 0, sum = 0;
    READ_TXT("./resources/input78.txt", "rt", stdin);
    cin >> v >> e;
    for (i = 1; i <= e; i++)
    {
        cin >> a >> b >> c;
        pq.push(Edge78(a, b, c));
    }
    for (i = 1; i <= e; i++)
        unf78[i] = i;

    // accepted == v-1 이면 탈출
    while (accepted < v - 1)
    {
        Edge78 cur = pq.top();
        pq.pop();

        // TODO: 기존 그래프를 어떻게 유지하지?
        // Q. 만약 완전 그래프가 아니라면 어떻게 하지?
        // A. 그럴 순 없음. 간선을 pick하기 때문에 사이클이 없으면 무조건 뽑은 간선 + 1 만큼의 노드가 있는 그래프가 됨.
        // 따라서 한 노드만 갖고 있어도 충분함.

        a = Find78(cur.u);
        b = Find78(cur.v);

        if (a == b)
            continue; // 해당 간선 PASS

        // 사이클이 없으므로 병합
        Union78(a, b);
        sum += cur.cost;
        accepted++;
    }
    printf("%d\n", sum);
}
