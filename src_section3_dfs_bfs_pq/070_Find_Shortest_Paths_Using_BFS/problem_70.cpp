#include "problem_70.hpp"

/*
유형: BFS
[풀이 전략]
최단 거리 No
최단 간선 수
를 BFS로 찾자.

=> 1번 정점에서 출발, 각 정점까지의 거리

[1] 1번 정점과 연결된 모든 정점은 cost=1
[2] 방문하지 않은 정점은 방문 시마다 cost=1++
[3] 완전 그래프이므로, 방문한 정점에 연결된 정점을 방문 큐에 넣음
[4] 새 점 방문 시 cost + 1로 방문함. 

이렇게 간단하게 예외가 없는 이유는 BFS이므로.
더 나중 단계에 방문할수록 무조건 cost가 더 높기 때문임.

---
벡터를 쓸까
배열을 쓸까?

벡터로 List처럼 하는 게 편하니까 그걸로 하자.

---
강의 코드를 봤는데,
[1]. costs 보단 distance 가 낫다
[2]. Q에 pair보다 그냥 int를 쓰면 된다. distance[to] = distance[from] + 1;
[3]. BFS는 재귀가 아니기 때문에 main에 같이 넣어써도 된다.

*/

using namespace std;

int n70;
vector<int> map70[21]; // unintialized
queue<pair<int, int>> q70;
bool visited70[21] = {false};
int costs[21] = {0};

void bfs70()
{
    int x, cost, i, to;
    while (!q70.empty())
    {
        x = q70.front().first;
        cost = q70.front().second;
        q70.pop();
        if (visited70[x])
            continue;
        costs[x] = cost;
        visited70[x] = true;
        debug("Visiting: %d with cost of [%d]\n", x, cost);
        for (i = 0; i < (int)map70[x].size(); i++)
        {
            to = map70[x][i];
            if (!visited70[to])
            {
                debug("Queuing %d\n", to);
                q70.push(make_pair(to, cost + 1)); // 왜 { to, cost + 1 } 이 안되고 make_pair만 되지? Vector는 또 됨
                // https://stackoverflow.com/questions/52236209/difference-between-make-pair-and-curly-brackets-for-assigning-a-pair-in-c
            }
        }
    }
}

void problem_70()
{
    int i, m, from, to;
    READ_TXT("./resources/input70.txt", "rt", stdin);
    scanf("%d %d", &n70, &m);
    for (i = 0; i < m; i++)
    {
        scanf("%d %d", &from, &to);
        map70[from].push_back(to); // 아 쉽다.
    }
    q70.push({1, 0});
    bfs70();
    for (i = 2; i <= n70; i++) // 2번 정점부터 출력
        printf("%d : %d\n", i, costs[i]);
}
