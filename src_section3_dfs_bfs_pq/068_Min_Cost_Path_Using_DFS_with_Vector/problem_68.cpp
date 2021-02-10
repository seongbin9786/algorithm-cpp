#include "problem_68.hpp"

/*
유형: 구현
[풀이 전략]

67에서 Pair Vector로 바꾸기만 하는 작업

*/

using namespace std;

int n68, min68 = 9999;
bool visited68[21][21] = {false};
vector<pair<int, int>> map68[21];

void dfs68(int from, int sum)
{
    if (from == n68)
    {
        min68 = min(min68, sum);
        return;
    }
    // Vector 크기만큼 순회
    for (int i = 0; i < (int)map68[from].size(); i++)
    {
        int to = map68[from][i].first;
        int cost = map68[from][i].second;
        if (!visited68[from][to])
        {
            visited68[from][to] = true;
            dfs68(to, sum + cost);
            visited68[from][to] = false;
        }
    }
}

void problem_68()
{
    int i, m, from, to, cost;
    // 67 이랑 같은 파일 읽음
    READ_TXT("./resources/input67.txt", "rt", stdin);
    scanf("%d %d", &n68, &m);
    for (i = 1; i <= m; i++)
    {
        scanf("%d %d %d", &from, &to, &cost);
        // 1. Dynamic Vector => push_back 사용해야.
        // 2. Pair literal
        map68[from].push_back({to, cost});
    }
    dfs68(1, 0);
    printf("%d\n", min68);
}
