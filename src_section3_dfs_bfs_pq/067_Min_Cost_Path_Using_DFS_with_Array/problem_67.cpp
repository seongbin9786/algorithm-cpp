#include "problem_67.hpp"

/*
유형: 구현
[풀이 전략]

큰 고민 없이 ㄹㅇ 한 번에 다 써 내려갔는데 TC 맞아서 신기함

*/

using namespace std;

int n67, min67 = 9999;
bool visited67[21][21] = {false};
int map67[21][21] = {0};

void dfs67(int from, int sum)
{
    if (from == n67)
    {
        min67 = min(min67, sum);
        return;
    }
    for (int i = 1; i <= n67; i++)
        if (map67[from][i] && !visited67[from][i])
        {
            visited67[from][i] = true;
            dfs67(i, sum + map67[from][i]);
            visited67[from][i] = false;
        }
}

void problem_67()
{
    int i, m, from, to, cost;
    READ_TXT("./resources/input67.txt", "rt", stdin);
    scanf("%d %d", &n67, &m);
    for (i = 1; i <= m; i++)
    {
        scanf("%d %d %d", &from, &to, &cost);
        map67[from][to] = cost;
    }
    dfs67(1, 0);
    printf("%d\n", min67);
}
