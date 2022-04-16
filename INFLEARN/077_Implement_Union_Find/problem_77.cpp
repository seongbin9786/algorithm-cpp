#include "problem_77.hpp"

/*
유형: Graph
[풀이 전략]

*/
using namespace std;

int unf77[1001];

int Find77(int v)
{
    if (v == unf77[v])
        return v;
    return Find77(unf77[v]);
}

// a의 root가 b가 됨. (group label이 b인 것)
void Union77(int a, int b)
{
    a = Find77(a);
    b = Find77(b);
    if (a != b)
        unf77[a] = b;
}

void problem_77()
{
    ios_base::sync_with_stdio(false); // 이게 뭘까? 배운 적 없다.
    int i, n, m, a, b;
    READ_TXT("./resources/input77.txt", "rt", stdin);
    cin >> n >> m;
    // unf 배열 초기화
    for (i = 1; i <= n; i++)
        unf77[i] = i;
    // Union 작업 수행 (labeling)
    for (i = 1; i <= m; i++)
    {
        cin >> a >> b;
        Union77(a, b);
    }
    // 마지막 라인으로 a, b 확인
    cin >> a >> b;
    a = Find77(a);
    b = Find77(b);
    cout << (a == b ? "YES\n" : "NO\n"); // 괄호로 감싸야 되는 이유?
}
