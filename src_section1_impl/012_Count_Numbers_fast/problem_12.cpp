#include "problem_12.hpp"

/*
유형: 구현
[풀이 전략]
N이 100,000 => 1,000,000,000이 됐다. 약 천 배 늘었는데 천 배 빨라져야 한다. (제한시간 1초)
--
수학적인 IDEA가 있을까?
각 자리수별로 똑같음. 무슨 소리냐?
100대면 숫자는 3개일거임
(ex)
1~9: 9 x 1자리 숫자
10~99: 90 x 2자리 숫자
100 ~ 999: 900 x 3자리 숫자
1000 ~ 9999: 9000 x 4자리 숫자
10000 ~ 99999: 90000 x 5자리 숫자
=> 즉 이것들은 계산할 필요가 없음 for 문으로.
=> 단, 이렇게 되면 재귀로 여러 번 계산하게 되는 거 아닌가?

(구현 전략)
15,365 => 10,000 + 5000 + 300 + 60 + 5

=> 10000 = 9000 x 4 + 900 x 3 + 90 x 2 + 9 x 1
=> 5000 = 4000 x 4 + 900 x 3 + 90 x 2 + 9 x 1
=> 300 = 200 x 3 + 90 x 2 + 9 x 1
=> 60 = 50 x 2 + 9 x 1 ()
=> 5 = 5 x 1 (1의 자리는 그냥 더해주면 됨)

(헷갈린다.)
이거 중복으로 세는 거 아닌가?
- 10,000까지는 세는거 맞음
- 10,000부터는 숫자 5개로 고정임
=> 10,000까지는 그냥 숫자로 센다.
=> 15365 까지의 5366개의 숫자는 계속 5개임

(결론)
15365
digit = 0; 
while (n > 0) {
    n /= 10;
    digit++;
}
15365 / 10 = 1536
1536 / 10 = 153
153 / 10 = 15
15 / 10 = 1
1 / 10 = 0
=> digit=5

=> digit-- => digit=4
=> 10^(digit) => 10 * 10 * 10 * 10 = 10,000

digit--;
int tmp = pow(10, digit-1);
while (digit > 0) {
    cnt += digit * 9 * tmp;
    digit--;
    tmp /= 10;
}
+= 4 * 9 * 1000
+= 3 * 9 * 100
+= 2 * 9 * 10
+= 1 * 9 * 1
(digit = 0) => break while;

// digit 복구한 후 수행
cnt += digit * (n - pow(10, digit-1) + 1); // 10,000~15,365 * 5

--
1<=i<=N번 순회하면서
i의 자리수만큼 더해주면 된다.

*/
int problem_12()
{

    int n, tmp;
    int cnt = 0, digit = 0;

    READ_TXT("./resources/input11.txt", "rt", stdin);
    scanf("%d", &n);
    debug("[problem 12] n: %d\n", n);
    // digit 세기
    tmp = n;
    while (tmp > 0)
    {
        tmp = tmp / 10;
        digit++;
    }

    digit--;
    tmp = pow(10, digit - 1);
    while (digit > 0)
    {
        cnt += digit * 9 * tmp;
        digit--;
        tmp /= 10;
    }

    // digit 다시 구하기
    digit = 0;
    tmp = n;
    while (tmp > 0)
    {
        tmp = tmp / 10;
        digit++;
    }

    cnt += digit * (n - pow(10, digit - 1) + 1);

    debug("[problem12] digit: %d, cnt: %d\n", digit, cnt);
    printf("%d\n", cnt);
    return 0;
}
