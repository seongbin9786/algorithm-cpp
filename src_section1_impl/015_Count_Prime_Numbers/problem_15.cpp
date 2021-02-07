#include "problem_15.hpp"

/*
유형: 구현
[풀이 전략]
에라토스테네스의 체를 쓴다 (이하 에라 체)
bool[N] 배열 만들고 sqrt(N) [#14 참고] 까지의 숫자로 모조리 나눠서 남는 소수는 모두 소수다~
그냥 소수구하기인데 배열 아이디어만 추가됨

근데 이거 잘 쳐봤자 O(N * sqrt(N)) 인데요?

(반성)
굳이 체로 구할 필요가 없다.
왜 체로 구하자는 판단을 했을까?
그냥 반복해서 구하면서 sqrt 최적화만 했어도
더 느리진 않는데.

그냥 체로 풀어보고 싶었긴 했지만 다음부턴 이런식 x
*/
int problem_15()
{
    int n, xn, i, j, cnt = 0;

    READ_TXT("./resources/input15.txt", "rt", stdin);
    scanf("%d", &n);
    bool *arr = new bool[n + 1]; // C++은 이렇게도 되는구나.
    memset(arr, 0, sizeof(bool) * (n + 1));

    xn = sqrt(n);
    for (i = 2; i <= xn; i++)                   // i = 2 ~ sqrt(n) 반복자 (나누는 수)
        for (j = 2; j <= n; j++)                // j = 2 ~ N 반복자 (나눠지는 수)
            if (!arr[j] && j > i && j % i == 0) // 지금까지_살아남음 && j % j 방지 && 소수가 아닌 경우 true로 놓아 필터링
                arr[j] = true;
    for (i = 2; i <= n; i++)
        if (!arr[i])
            cnt++;
    printf("%d\n", cnt);
    return 0;
}
