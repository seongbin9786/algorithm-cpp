#include <iostream>
#include <queue>
#include "../include/debugopen.hpp"

/*
	[Silver 2]
	촌수 계산

	문제
	기본적으로 부모와 자식 사이를 1촌으로 정의하고 이로부터 사람들 간의 촌수를 계산한다. 
	
	예를 들면 나와 아버지, 아버지와 할아버지는 각각 1촌으로 나와 할아버지는 2촌이 되고, 아버지 형제들과 할아버지는 1촌, 나와 아버지 형제들과는 3촌이 된다.

	여러 사람들에 대한 부모 자식들 간의 관계가 주어졌을 때, 주어진 두 사람의 촌수를 계산하는 프로그램을 작성하시오.

	촌수 개념 참고:
	https://m.blog.naver.com/PostView.nhn?blogId=mysky4you&logNo=221251231178

	입력
	n <= 100
	src dest (src=시작점, dest=종착점)
	m (관계의 개수)
	x1 y1 (이 때 x1이 y1의 부모)

	각 사람의 부모는 최대 한 명만 주어진다.

	출력
	촌수 출력
	친척 관계가 전혀 없으면 -1

	[IDEA]
	1. 그냥 BFS로 도착 시의 depth만 세기: 단순 up이면 가능
	- [자식으로 갈 때는 (-) 하고] => 아니었음. 촌수가 그렇게 세는 게 아님
	- [부모로 갈 때는 (+) 하면 되는 거 아닌가? 0에서 시작하고]
	- [연결되어있지 않은 경우도 확인해봐야 하므로, dfs/bfs로 모두 돌긴 해야 함]
	- []

	예: 같은 부모(=1)인 형제(=2)의 아들(= 3) => 3촌 띠딩;; 
	
	===> 그냥 BFS로 detph 구하면 되는 거 같네
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

    // 쉬운 dfs로 갈까? yes
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
            if (matrix[cur][i] && !visited[i])
                Q.push(Node2644(i, cnt + 1));
    }
    cout << "-1\n";
    return 0;
}
