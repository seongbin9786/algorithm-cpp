#include "problem_12.hpp"

/*
[풀이 전략]
(ex) n = 256
sum     d       c       cnt
0       9       1       9
9       90      2       189
99      900     3       993 [안 됨]

=> sum+d=999 > 256 이므로 while break
=> cnt=189
=> cnt=189 + (256-99)*3
=> 정답

(굉장히 똑똑한 것 같다.)
*/
// run 하려면 얘를 problem_12로 바꿔줘야 함.
int problem_12_teacher()
{
    READ_TXT("input12.txt", "rt", stdin);
    int n, sum = 0, c = 1, d = 9, cnt = 0;
    scanf("%d", &n);
    // sum=0 부터 시작해서 sum+d로 체크
    while (sum + d < n)
    {
        // d에 c(자리수) 곱해서 더해줌.
        cnt += c * d;
        // sum은 답을 구하는 변수가 아니라 9->99->999 이렇게 자리수 비교하는 변수
        sum += d;
        c++;
        // 9->90->900 이렇게 가는게 참 똑똑한것 같다.
        // sum이 9->99->999->9999 이렇게 되니까.
        d *= 10;
    }
    // 마지막 자리수 * 숫자개수 더해주면 끝.
    cnt += (c * (n - sum));
    printf("%d\n", cnt);
    return 0;
}
