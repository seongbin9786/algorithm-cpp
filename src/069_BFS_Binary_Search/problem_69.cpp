#include "problem_69.hpp"

/*
유형: 구현
[풀이 전략]

BFS를 구현해야 한다.
BFS는 DFS와 호출 순서가 다른데
DFS는 계속 한 호출이 쭉 들어가는 형태 (스택) 인데 반해
BFS는 호출이 레벨 단위로 한꺼번에 들어가는 형태 (큐) 이다.

그래서 bfs는 실행 큐가 있으며 하위 호출 시 큐에 쌓이므로
상위 호출한 bfs()가 먼저 수행된다.

=> 아무튼 큐가 필요하다.

---
C++에서 Queue 구현체가 아마 있을 것이다. 
아마 동적 배열인 Vector로 구현할 수 있겠지만
Queue가 분명히 있을 것 같다 ㅎㅎ..

BFS Pseudo Code:

// binary search using BFS
// 종료 조건이 없음 그냥 방문만 함

vector<int> map69[4]; // 1 ~ 3

void bfs(int from)
{
    printf("visit %d\n", from);
    for (int i = 0; i < map69[from].size; i++)
    {
        // Bin Tree라서 visited 의미 없을듯 (부모가 하나니까)
        Q.push(map69[from][i]);
    }
    if (!Q.isEmpty())
        bfs(Q.pop());
}

int i, from, to;
for (i = 1; i <= 3; i++) 
{
    scanf("%d %d", &from, &to);
    map69[from].push_back(to);
}
bfs(1);

---
첫 시도에 구현 성공
*/
using namespace std;

vector<int> map69[8]; // 1 ~ 7
queue<int> Q;

void bfs(int from)
{
    printf("visit %d\n", from);
    for (int i = 0; i < (int)map69[from].size(); i++)
    {
        // Bin Tree라서 visited 의미 없을듯 (부모가 하나니까)
        Q.push(map69[from][i]);
    }
    if (!Q.empty())
    {
        int next = Q.front();
        Q.pop();
        bfs(next);
    }
}

void problem_69()
{
    int i, from, to;
    READ_TXT("./resources/input69.txt", "rt", stdin);
    for (i = 1; i <= 6; i++)
    {
        scanf("%d %d", &from, &to);
        map69[from].push_back(to);
    }
    bfs(1);
}
