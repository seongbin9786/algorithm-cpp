#include <iostream>
#include <queue>
#include "../include/debugopen.hpp"

/*
	[Silver 1]
	미로 탐색

	N×M크기의 배열로 표현되는 미로가 있다.

	1	0	1	1	1	1
	1	0	1	0	1	0
	1	0	1	0	1	1
	1	1	1	0	1	1
	미로에서 1은 이동할 수 있는 칸을 나타내고, 0은 이동할 수 없는 칸을 나타낸다. 
	이러한 미로가 주어졌을 때, (1, 1)에서 출발하여 (N, M)의 위치로 이동할 때 
	지나야 하는 최소의 칸 수를 구하는 프로그램을 작성하시오.  (===> BFS 써서 (N, M) 도착 시의 cnt 계산하면 됨)
	한 칸에서 다른 칸으로 이동할 때, 
	서로 인접한 칸으로만 이동할 수 있다.

	칸을 셀 때에는 시작 위치와 도착 위치도 포함한다.

	입력
	첫째 줄에 두 정수 N, M(2 ≤ N, M ≤ 100)이 주어진다. 
	다음 N개의 줄에는 M개의 정수로 미로가 주어진다. 
	각각의 수들은 붙어서 입력으로 주어진다.

	출력
	첫째 줄에 지나야 하는 최소의 칸 수를 출력한다. 
	항상 도착위치로 이동할 수 있는 경우만 입력으로 주어진다.
*/

using namespace std;

struct Node2178
{
    int x, y, cnt;

    Node2178(int x, int y, int cnt)
    {
        this->x = x;
        this->y = y;
        this->cnt = cnt;
    }
};

int main()
{
    int i, j, n, m, x, y, nx, ny;
    READ_TXT("./input.txt", "rt", stdin);
    cin >> n >> m;
    char buf[m + 1];
    bool visited[n + 1][m + 1] = {0};
    bool matrix[n + 1][m + 1] = {0};
    // 동서남북으로 ㄱㄱ
    int pos_x[] = {1, -1, 0, 0};
    int pos_y[] = {0, 0, -1, 1};
    queue<Node2178> Q;

    for (i = 1; i <= n; i++)
    {
        cin >> buf;
        for (j = 1; j <= m; j++)
            matrix[i][j] = buf[j - 1] == '1' ? 1 : 0; // map처럼 사용. 양방향 X
    }
    // BFS
    Q.push(Node2178(1, 1, 0));
    while (!Q.empty())
    {
        Node2178 cur = Q.front();
        Q.pop();

        // 좌표는 다 거꾸로 돼야함
        if (cur.x == m && cur.y == n)
        {
            cout << cur.cnt + 1 << '\n';
            return 0;
        }

        // visited 되기 전에 push된 애들은 여기서 걸러야 함
        if (visited[cur.y][cur.x])
            continue;

        visited[cur.y][cur.x] = 1;
        /*
			matrix로 바로 연결 여부를 알 수 없고,
			Bound 체크를 하면서 동서남북을 확인해야 함.
		*/
        for (int i = 0; i < 4; i++)
        {
            nx = cur.x + pos_x[i];
            ny = cur.y + pos_y[i];
            if (nx < 1 || nx > m || ny < 1 || ny > n) // out of bounds
                continue;
            // [ny][nx]로 놓아야 제대로 된 x,y 축 이동을 함
            if (matrix[ny][nx] && !visited[ny][nx])
                Q.push(Node2178(nx, ny, cur.cnt + 1));
        }
    }
    return 0;
}
