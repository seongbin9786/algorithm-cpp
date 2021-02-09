#include "problem_41.hpp"

/*
유형: 구현
[풀이 전략]
Let a = any natrual number
1. Let N = (a+1)/2
1). N=2k => a=N/2
2). N=2k-1 => a=(N+1)/2

(ex) N=15 => a=8
(ex) N=7 => a=4

2. N = a + a-1
=> First Sequence: [a-1], [a]

3. Next sequence: [a], [a-1], [a-2], ... (i--)
=> if sum of the sequence is equal to N
=> cnt++;

4. 출력이 문제였는데 역시 배열 말곤 답이 없을 것 같았다.
이게 trial-and-error 여서 그럴 수 밖에..
*/
void problem_41()
{
    int i, j, k, n, sum, cnt = 0, len = 0;
    READ_TXT("./resources/input41.txt", "rt", stdin);
    scanf("%d", &n);
    if (n % 2 == 1)
        i = (n + 1) / 2;
    else
        i = n / 2;
    std::vector<int> buf(i); // i개 해놓으면 걱정 없지. 좀 더 좋은 계산법이 있을지도
    // 배열에 넣으면 좀 쉽겠지.. 근데 초기화 하기가 너무 귀찮다.
    while (i > 0)
    {
        sum = 0;
        for (j = i; j > 0; j--)
        {
            sum += j;
            buf[len++] = j;
            if (sum == n)
            {
                for (k = len - 1; k > 0; k--) // 일부러 buf[0] 출력 X
                    printf("%d + ", buf[k]);
                printf("%d = %d\n", buf[0], sum);
                len = 0;
                cnt++; // 다음 수열 찾으러 감
                break;
            }
            else if (sum > n) // 초과했으면 실패한 수열
            {
                len = 0; // 굳이 배열을 초기화할 필요는 없다. len까지 덮어쓰면 됨.
                break;
            }
            if (j == 1) // 이제부터 수열의 합은 무조건 sum < n. 여기서 탈출.
            {
                printf("%d\n", cnt);
                return;
            }
        }
        i--;
    }
}
