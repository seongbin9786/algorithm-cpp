#include <stdio.h>

/*
	[Bronze 2]
	그리디
	
	{1000 - 구매가}의 거스름돈을 줄 때, 동전의 개수가 가장 적게 출력

	1. 틀렸습니다. 이유가 뭘까? 50원을 빼먹었음..
*/

int main()
{
    int i, cnt = 0, sum;
    int coins[] = {500, 100, 50, 10, 5, 1};
    scanf("%d", &sum);
    sum = 1000 - sum;
    for (i = 0; i < 6; i++)
    {
        if (sum <= 0)
            break;
        if (sum / coins[i] > 0) // 적어도 1이 나와야
        {
            cnt += sum / coins[i];
            sum %= coins[i];
        }
    }
    printf("%d\n", cnt);
    return 0;
}
