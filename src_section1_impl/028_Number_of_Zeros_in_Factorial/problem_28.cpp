#include "problem_28.hpp"

/*
유형: 구현
[풀이 전략]
일단 N!을 직접 구해야 할 건 아닌 듯하다.
어떻게 하면 뒤에 붙는 0의 개수를 구할 수 있을까?
=> 2와 5의 페어의 개수를 구하면 되는구나. 개꿀~

=> 이거 굳이 풀어야 되나?
=> 27 그대로 복붙 후 2, 5의 개수 중 작은거 반환하도록 함.
*/
void problem_28()
{
    int i, j, n, cur;
    READ_TXT("./resources/input28.txt", "rt", stdin);
    scanf("%d", &n);
    std::vector<int> primes(n + 1); // 소수 idx를 위해서. 0으로 초기화되기도 하고.
    for (i = 2; i <= n; i++)
    {
        cur = i;
        for (j = 2; cur > 1 && j <= i; j++)
        {
            if (cur % j == 0)
            {
                primes[j]++;
                cur /= j;
                j--;
            }
        }
    }
    printf("%d\n", std::min(primes[2], primes[5]));
}
