#include <iostream>
#include <queue>
#include <stack>
#include "../include/debugopen.hpp"

/*
	[Silver 1]
	순열 사이클

	1~N까지 정수 N개로 이루어진 순열을 나타내자

	{3,2,7,8,1,4,5,6} => ?

	방향 그래프로 나타내자
	idx -> 파이[idx] 로 매핑 (idx=1...)

	(ex): [1 2 3 4 5 6 7 8]
		  [3 2 7 8 1 4 5 6]

	=> 	1->3 [사이클 1 (1/4)]
		2->2 [사이클 2]
		3->7 [사이클 1 (2/4)]
		4->8 [사이클 3 (1/3)]
		5->1 [사이클 1 (4/4)]
		6->4 [사이클 3 (2/3)]
		7->5 [사이클 1 (3/4)]
		8->6 [사이클 3 (3/3)]

		1->3->7->5->1

		2->2

		4->8->6->4

		순열이 주어졌을 때 사이클의 개수를 구하시오.

	----
	[IDEA]

	사이클의 개수를 구하는 방법이 뭐가 있을까?
	- 방향 그래프니까, 완전 탐색으로 방문하면 언젠가 자신이 방문 대상이 될 것임
	- 애초에 방향 그래프니까 visited가 필요 없음
		=> 변경: visited를 관리하자 일단

	즉 시작점에서 dfs/bfs를 수행해서 다시 본인을 방문할 때 cycle++ 하고 종료 하면 되지 않을까?
		=> 변경: visited를 다시 방문한 경우 cycle++
	=> 근데 그러면 한 점이 N개의 사이클의 기점이 되는 경우는 셀 수 없음 :(
		=> ㄴㄴ 이걸 시작점의 각 점에 대해서 수행하면 되지 ㅇㅇ (방향 그래프라서 가능)

	=> visited를 관리하는 상태에서, 매 점에서 사이클 검사를 시작하면 된다.
	=> 일단 첫 점에서 사이클을 검사하고, visited를 모두 수행한다.
	=> 이후 다음 점이 visited인 경우 pass하고, visited가 아닌 경우 사이클을 검사한다.

	이런식으로 전수 조사를 하면 사이클의 개수를 알 수 있게 된다.
	내가 사이클에 대한 그래프 개념이 아예 안 떠올라서 좋은 개념이 따로 있는 지는 모르겠고 일단 시작한다.

    ---
    첫 시도에 맞았고 특별히 최적화는 필요 없는 그냥 다 해봐도 되는 문제인걸로 '-'
*/

using namespace std;

int get_cycle_of_graph(int m)
{
    int cycle = 0;
    int cur, i, j;
    bool visited[m + 1] = {0};
    vector<int> matrix[m + 1];
    for (i = 1; i <= m; i++)
    {
        cin >> j;
        matrix[i].push_back(j);
    }
    for (i = 1; i <= m; i++)
    {
        if (visited[i])
            continue;

        // dfs로 탐색해서 visited 나오면 cycle++ 하려고 했는데,
        // dfs를 하려면 visited, matrix를 전달해야 하는데,
        // 이게 순열별로 생성되니까 좀 그렇다.
        stack<int> s;
        s.push(i);
        while (!s.empty())
        {
            cur = s.top();
            s.pop();
            if (visited[cur])
            {
                cycle++;
                printf("visiting: %d\n", cur);
                continue;
            }
            visited[cur] = true;
            for (j = 0; j < (int)matrix[cur].size(); j++)
            {
                s.push(matrix[cur][j]);
                printf("pushing: %d\n", matrix[cur][j]);
            }
        }
    }
    return cycle;
}

int main()
{
    int i, n, m;
    READ_TXT("./input.txt", "rt", stdin);
    // 테스트 케이스의 개수
    cin >> n;
    // n개의 순열에 대해 사이클 검사를 해야 함
    for (i = 1; i <= n; i++)
    {
        cin >> m;
        printf("%d\n", get_cycle_of_graph(m));
    }
    return 0;
}
