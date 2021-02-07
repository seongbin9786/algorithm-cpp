#include "problem_08.hpp"

/*
유형: 구현
[풀이 전략]
보통 스택으로 설명하지만 더 쉬운게 있을듯.
++, -- 로 하고, 만약 < 0 인 상태가 오면 NO 출력
*/
void problem_08()
{
    char paren[31];
    int i, sum = 0;

    READ_TXT("./resources/input08.txt", "rt", stdin);
    scanf("%s", paren);
    for (i = 0; paren[i] != 0; i++)
    {
        if (paren[i] == '(')
            sum++;
        else
            sum--;
        if (sum < 0)
        {
            printf("NO");
            return;
        }
    }
    printf("YES");
}
