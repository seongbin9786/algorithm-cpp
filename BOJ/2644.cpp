#include <iostream>
#include <queue>
#include "../include/debugopen.hpp"

/*
	[Silver 2]
	촌수 계산

	문제
	기본적으로 부모와 자식 사이를 1촌으로 정의하고 이로부터 사람들 간의 촌수를 계산한다. 
	예를 들면 나와 아버지, 아버지와 할아버지는 각각 1촌으로 나와 할아버지는 2촌이 되고, 아버지 형제들과 할아버지는 1촌, 나와 아버지 형제들과는 3촌이 된다.

	[촌수 개념]:
    촌수는 그냥 부모면 +1 이고 자식이면 -1 이다. 형제는 위로 올라갔다 내려가는 것으로 계산한다.
	https://m.blog.naver.com/PostView.nhn?blogId=mysky4you&logNo=221251231178

	[입력]
	n <= 100
	src dest (src=시작점, dest=종착점)
	m (관계의 개수)
	x1 y1 (부모, 자식 순)

	각 사람의 <부모는 최대 한 명>만 주어진다.
    => 트리이므로, 
	=> 그냥 BFS로 detph(이동거리) 구하면 된다.
*/

using namespace std;

struct Node2644
{
    int cur, cnt;

    Node2644(int cur, int cnt)
    {
        this->cur = cur;
        this->cnt = cnt;
    }
};

int main()
{

    int i, m, n, x, y, src, dest, cnt, cur;
    READ_TXT("./input.txt", "rt", stdin);
    cin >> n >> src >> dest >> m;
    bool visited[n + 1] = {0};
    bool matrix[n + 1][n + 1] = {0};
    queue<Node2644> Q;

    for (i = 0; i < m; i++)
    {
        cin >> x >> y;
        // 양방향 노드
        matrix[x][y] = 1;
        matrix[y][x] = 1;
    }

    // cur, cnt 이다.
    // BFS를 통해
    Q.push(Node2644(src, 0));
    while (!Q.empty())
    {
        cur = Q.front().cur;
        cnt = Q.front().cnt;
        Q.pop();

        if (cur == dest)
        {
            cout << cnt << '\n';
            return 0;
        }

        visited[cur] = 1;
        for (int i = 1; i <= n; i++)
            // BFS 탐색 (완전 탐색), 탐색마다 1씩 증가
            if (matrix[cur][i] && !visited[i])
                Q.push(Node2644(i, cnt + 1));
    }
    cout << "-1\n";
    return 0;
}
