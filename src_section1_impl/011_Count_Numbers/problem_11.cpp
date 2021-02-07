#include "problem_11.hpp"

/*
유형: 구현
[풀이 전략]
1<=i<=N번 순회하면서
i의 자리수만큼 더해주면 된다.
*/
int problem_11()
{
    READ_TXT("./resources/input11.txt", "rt", stdin);
    int n, i, cnt = 0, tmp;

    scanf("%d", &n);
    for (i = 1; i <= n; i++)
    {
        tmp = i;
        while (tmp > 0)
        {
            tmp = tmp / 10;
            cnt++;
        }
    }
    printf("%d\n", cnt);
    return cnt;
}
