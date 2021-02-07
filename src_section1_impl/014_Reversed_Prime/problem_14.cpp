#include "problem_14.hpp"

/*
유형: 구현
[풀이 전략]

(1). Wrong Answer x 5
=> 흠 뭐가 문젤까?
=> prime 함수 구현 논리 문제였음. 

(2). Test Case 2, 3 Wrong Answer
=> 아마 reverse 함수가 문제일듯
=> 내 생각엔 잘 짠 것 같음.
=> Test Case 2 돌려보니 자꾸 1이 나오길래 확인해봄.
=> (ex) 100 => 1 => prime=false로 판별한 게 문제
=> 애초에 1이 들어올거라 전혀 상상하지 못 했음.
*/
int reverse(int x)
{
    int tmp = x, digit = 1;
    // 어쩔 수 없이 digit을 먼저 구해야 함.
    while (tmp > 0)
    {
        tmp /= 10;
        digit *= 10;
    }
    digit /= 10;

    tmp = 0;
    while (x > 0)
    {
        if (x % 10 != 0)
            tmp += x % 10 * digit;
        x /= 10;
        digit /= 10;
    }
    return tmp;
    // 스택에 튜플로 넣었다가 계산하면 좋긴 하겠다 흠..
}

/*
    옛날에 찾아본 O(sqrt(N))
    WHY 근호까지만 구하느냐?
    https://stackoverflow.com/questions/5811151/why-do-we-check-up-to-the-square-root-of-a-prime-number-to-determine-if-it-is-pr

    => Let n is not a prime number
    => n = a * b 로 나타낼 수 있다.
    => 이 때 a >= sqrt(n) 인 정수로 가정하자.
    => a*b=n 이므로 b <= sqrt(n) 이어야 한다.
    => 따라서 i <= sqrt(n) 까지 체크했는데 n을 나누는 인자를 찾지 못한 경우는 b가 존재하지 않는 경우이다. 
    => 따라서 n=a*b 인 a, b 가 존재하지 않으므로 소수이다.
*/
bool isPrime(int x)
{
    if (x == 1)
        return false;
    int i, xs = floor(sqrt(x));
    for (i = 2; i <= xs; i++)
    {
        if (x % i == 0)
            return false;
    }
    return true;
}

int problem_14()
{
    int i, n, num;

    READ_TXT("./resources/input14.txt", "rt", stdin);
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &num);
        num = reverse(num);
        if (isPrime(num))
            printf("%d ", num);
    }
    return 0;
}
