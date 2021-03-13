#include <iostream>
#include "../include/debugopen.hpp"

/*
	[Silver 3]
	바이러스

	BFS/DFS로 같은 그래프 내의 노드 개수를 출력

	입력
	N <= 100
	M (순서쌍)
	x1 y1
	x2 y2
	...

	출력
	노드 개수
*/

using namespace std;

// 쉬운 dfs로 갈까? yes
bool visited2606[101] = {0};     // 이렇게도 컴파일 됨.
bool matrix2606[101][101] = {0}; // 가장 간단한 행렬 구현 ㄱㄱ

int n2606;
int cnt2606 = 0;

void dfs(int cur)
{
    if (visited2606[cur])
        return;

    cnt2606++;
    visited2606[cur] = 1;

    for (int i = 1; i <= n2606; i++)
        if (matrix2606[cur][i])
            dfs(i);
}

int main()
{
    int i, m, x, y;
    READ_TXT("./input.txt", "rt", stdin);
    cin >> n2606 >> m;
    for (i = 0; i < m; i++)
    {
        cin >> x >> y;
        // 양방향 노드
        matrix2606[x][y] = 1;
        matrix2606[y][x] = 1;
    }

    // 1번부터 시작
    dfs(1);
    // 1을 통해 전파되는 컴퓨터의 개수이므로 1을 제외함
    cout << cnt2606 - 1 << '\n';
    return 0;
}
