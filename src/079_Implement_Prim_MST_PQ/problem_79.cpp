#include "problem_79.hpp"

/*
유형: Graph
[풀이 전략]

이게 더 어려운거 같은데?

=> PQ를 쓰기 때문에 PQ의 시간복잡도인 O(log 2 V) 덕을 보아
=> 총 시간 복잡도는 O ( V * log 2 V ) 이다. 개 좋네
*/

bool visited79pq[31] = {0};

// Pair을 PQ에서 쓰는 경우 first 비교 후 second 비교로 정렬한다.
// Pair를 쓰는 게 코드는 간단해지겠지만 PQ라 연산자 오버로딩을 해야 하기 때문에 어렵다.
// 그냥 sort 함수를 넘겨줄 순 없는 걸까?
// ====> 가능하다.
/*
// 이걸로 구조체를 넘겨줄 수 있음.
struct cmp {
    //연산자 오버로딩
    bool operator()(pair<int, int>&a, pair<int, int>&b) {
        if (a.first == b.first) {
            return a.second > b.second;
        }
        else {
            return a.first < b.first;
        }
    }
};
// 사용
priority_queue<pair<int,int>,vector<pair<int,int>>, cmp> pq;
*/
struct Edge79
{
    int e, cost;

    Edge79(int e, int cost)
    {
        this->e = e;
        this->cost = cost;
    }

    bool operator<(const Edge79 &b) const
    {
        return cost > b.cost;
    }
};

void problem_79pq()
{
    ios_base::sync_with_stdio(false);
    READ_TXT("./resources/input78.txt", "rt", stdin);
    priority_queue<Edge79> pq;
    int i, n, m, a, b, c, res = 0;
    cin >> n >> m;
    // 인접 리스트 생성 (도착점, 비용) pair 사용
    vector<pair<int, int>> map[31]; // 이게 왜 되지? C++은 입력 후 초기화도 가능한가? => 안 됨 ㅋㅋㅋ
    for (i = 1; i <= m; i++)
    {
        // 양방향 간선 적용
        cin >> a >> b >> c;
        map[a].push_back(make_pair(b, c));
        map[b].push_back(make_pair(a, c));
    }
    pq.push(Edge79(1, 0));
    // O(E)
    while (!pq.empty())
    {
        Edge79 cur = pq.top();
        pq.pop();
        if (visited79pq[cur.e])
            continue;
        res += cur.cost;
        visited79pq[cur.e] = true;
        for (i = 0; i < (int)map[cur.e].size(); i++)
            pq.push(Edge79(map[cur.e][i].first, map[cur.e][i].second));
    }
    cout << res << "\n";
}
