#include "problem_76.hpp"

/*
유형: 재귀
[풀이 전략]

1. nCr = (n-1)C(r-1) + (n-1)Cr (재귀로 해결 + 메모이제이션 활용 매우 좋음)

2. fib(n) = fib(n-1) + fib(n-2) (재귀로 해결 + 메모이제이션 활용 매우 좋음)
=> 피보나치도 동일한 메커니즘이므로 생략

*/
int cache76[21][21] = {0};

// nC1 =
int nCr76(int n, int r)
{
    // 종료 조건
    if (n == r || r == 0)
        return 1;
    // cache if needed
    if (!cache76[n][r])
        cache76[n][r] = nCr76(n - 1, r - 1) + nCr76(n - 1, r);
    return cache76[n][r];
}

void problem_76()
{
    int n, r;
    // input (5 3) -> output (10)
    scanf("%d %d", &n, &r); // n <= 20, r <= 20
    printf("%d\n", nCr76(n, r));
}
