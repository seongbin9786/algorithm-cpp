#include "problem_21.hpp"

/*
유형: 구현
[풀이 전략]
그냥 배열로 저장하고 comp하면 될듯
마지막에 이긴 게임이 문젠데 어떻게 트래킹할까?
그냥 flag하나 주면 될 거 같다. 마지막에 이긴 게임의 num=0으로 해놓고 하나라도 누가 이기면 num=[~] 세팅.
*/
void problem_21()
{
    int i, sum_a = 0, sum_b = 0;
    int a[10], b[10];
    char last = 'D'; // D로 초기화해놓으면 편하다.
    READ_TXT("./resources/input21.txt", "rt", stdin);
    for (i = 0; i < 10; i++)
        scanf("%d", a + i);
    for (i = 0; i < 10; i++)
        scanf("%d", b + i);
    for (i = 0; i < 10; i++)
    {
        if (a[i] > b[i])
        {
            sum_a += 3;
            last = 'A';
        }
        else if (a[i] < b[i])
        {
            sum_b += 3;
            last = 'B';
        }
        else
        {
            sum_a += 1;
            sum_b += 1;
        }
    }
    printf("%d %d\n", sum_a, sum_b);
    printf("%c\n", sum_a > sum_b ? 'A' : (sum_a != sum_b ? 'B' : last));
}
