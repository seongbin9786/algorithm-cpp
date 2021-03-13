#include <iostream>
#include <queue>
#include <stack>
#include "../include/debugopen.hpp"

/*
	[Silver 2]
	DFS와 BFS (그냥 구현하라는듯)

	문제
	그래프를 DFS로 탐색한 결과와 BFS로 탐색한 결과를 출력하는 프로그램을 작성하시오. 
	
	단, 방문할 수 있는 정점이 여러 개인 경우에는 정점 번호가 작은 것을 먼저 방문하고, 
	더 이상 방문할 수 있는 점이 없는 경우 종료한다. 
	
	정점 번호는 1번부터 N번까지이다.

	입력
	첫째 줄에 정점의 개수 N(1 ≤ N ≤ 1,000), 
	간선의 개수 M(1 ≤ M ≤ 10,000), 
	탐색을 시작할 정점의 번호 V가 주어진다. 
	다음 M개의 줄에는 간선이 연결하는 두 정점의 번호가 주어진다. 
	어떤 두 정점 사이에 여러 개의 간선이 있을 수 있다. 			// 이거 고려해야 되는건가?

	출력
	첫째 줄에 DFS를 수행한 결과를, 
	그 다음 줄에는 BFS를 수행한 결과를 출력한다. 
	V부터 방문된 점을 순서대로 출력하면 된다.
*/

using namespace std;

int main()
{
    int i, n, m, x, y, src, cur;
    READ_TXT("./input.txt", "rt", stdin);
    cin >> n >> m >> src;
    // DFS 용도
    bool visited1[n + 1] = {0};
    bool matrix1[n + 1][n + 1] = {0};
    // BFS 용도
    bool visited2[n + 1] = {0};
    bool matrix2[n + 1][n + 1] = {0};
    stack<int> S;
    queue<int> Q;

    for (i = 0; i < m; i++)
    {
        cin >> x >> y;
        // 양방향 노드
        matrix1[x][y] = 1;
        matrix1[y][x] = 1;
        // 행렬 2개에 저장
        matrix2[x][y] = 1;
        matrix2[y][x] = 1;
    }

    // DFS
    // 깔끔하게 main에서 끝내려고 재귀말고 스택 사용
    S.push(src);
    while (!S.empty())
    {
        cur = S.top();
        S.pop();

        if (visited1[cur])
            continue;

        cout << cur << ' ';

        visited1[cur] = 1;
        // 작은것부터 먼저 방문하려면, 스택은 반대로 쌓아야 됨.
        for (int i = n; i >= 1; i--)
            if (matrix1[cur][i])
                S.push(i);
    }
    cout << '\n';

    // BFS
    Q.push(src);
    while (!Q.empty())
    {
        cur = Q.front();
        Q.pop();

        if (visited2[cur])
            continue;

        cout << cur << ' ';

        visited2[cur] = 1;
        for (int i = 1; i <= n; i++)
            if (matrix2[cur][i])
                Q.push(i);
    }
    cout << '\n';
    return 0;
}
