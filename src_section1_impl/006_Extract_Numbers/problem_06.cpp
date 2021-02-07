#include "problem_06.hpp"

/*
유형: 구현
[풀이 전략]
앞 0을 무시하는 것 말인데 그동안 배운 res= res*c + d 이런 테크닉을 써보자.
=> 쉽게 풀렸다 ㅎㅎ 이 부분 처리만 쉽게 한다면 어려운 문제는 전혀 아니다.
*/
void problem_06()
{
    char str[51];
    int i, res = 0, cnt = 0;

    READ_TXT("./resources/input06.txt", "rt", stdin);
    scanf("%s", str);
    // 자연수 계산
    for (i = 0; str[i] != 0; i++)
        if (str[i] >= '0' && str[i] <= '9')
            res = res * 10 + (str[i] - '0'); // 테크닉 활용 성공한듯?ㅋㅋ

    // 약수 개수 계산
    for (i = 1; i <= res; i++)
    {
        if (res % i == 0)
            cnt++;
    }
    printf("%d\n%d\n", res, cnt);
}
