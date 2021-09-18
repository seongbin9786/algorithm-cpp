#include <stdio.h>
#include <queue>
#include "../include/debugopen.hpp"

/*
    [Silver 2]
    트리의 부모 찾기

    루트 없는 트리가 주어진다. 이때, 트리의 루트를 1이라고 정했을 때, 각 노드의 부모를 구하는 프로그램을 작성하시오.

    첫째 줄에 노드의 개수 N (2 ≤ N ≤ 100,000)이 주어진다. 둘째 줄부터 N-1개의 줄에 트리 상에서 연결된 두 정점이 주어진다.

    첫째 줄부터 N-1개의 줄에 각 노드의 부모 노드 번호를 2번 노드부터 순서대로 출력한다.

    ---
    [틀린 이유]
    1. 이미 완성된 그래프에서 추가되는 게 아니다.

    ---
    [시간 초과 이유]
    1. Queue에서 계속 넣고 빼서 그런 것 같다. 애초에 비연결된 게 너무 많아서 그런가보다.
    2. 처음부터 그래프를 한 번에 완성하고 나서 (아니, 이게 완성이 되긴 하는가?)

*/

using namespace std;

int main()
{
    int i, a, b, N;
    READ_TXT("./input.txt", "rt", stdin);
    scanf("%d", &N);
    bool visited[N + 1] = {0};
    int parent[N + 1] = {0};
    queue<pair<int, int>> unconn;
    pair<int, int> cur;
    visited[1] = true;
    for (i = 0; i < N - 1; i++)
    {
        scanf("%d %d", &a, &b);
        if (visited[a] && !visited[b])
        {
            parent[b] = a;
            visited[b] = true;
        }
        else if (!visited[a] && visited[b])
        {
            parent[a] = b;
            visited[a] = true;
        }
        else
        {
            // do nothing
            // 나중에 연결하자.
            unconn.push(make_pair(a, b));
        }
    }
    while (unconn.size() > 0)
    {
        // 만약 Q의 push/pop 때문에 느린거라면,
        // 그냥 flag를 쓸까? 그걸로 된다면 해보자.
        // 근데 애초에 다른 아이디어로 충분히 풀린다면,
        // 그 아이디어를 알아보는 것도 좋을 것 같다.
        cur = unconn.front();
        unconn.pop();
        a = cur.first;
        b = cur.second;
        if (!visited[a] && !visited[b])
        {
            unconn.push(cur);
            continue;
        }
        if (visited[a] && !visited[b])
        {
            parent[b] = a;
            visited[b] = true;
        }
        else
        {
            parent[a] = b;
            visited[a] = true;
        }
    }
    for (i = 2; i <= N; i++)
        printf("%d\n", parent[i]);
    printf("\n");
    return 0;
}
