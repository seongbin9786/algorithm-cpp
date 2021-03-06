#include <stdio.h>

int main()
{
    int a, b;
    scanf("%d %d", &a, &b);
    // 1. 일단 정수 나눗셈에서 소수 몫을 보이려면 둘 다 double로 캐스팅해야 함 (하나라도 빼면 X)
    // 2. 그냥 %f 하면 6자리까지만 나오는데 "(절대|상대)오차가 10^(-9) 이하이면 정답이라고 하는 부분을 이해 못했음
    // => 0.3333과 0.33333333333의 차이 = 0.00003... > 0.000000001 이므로 틀리는 것임.
    // => 그래서 .9f 와 같이 거기까지 자릿수를 출력해야만 정답임
    printf("%.9f\n", (double)a / (double)b);
    return 0;
}
