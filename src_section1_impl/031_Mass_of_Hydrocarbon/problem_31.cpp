#include "problem_31.hpp"

/*
유형: 구현
[풀이 전략]
쉽게 가기 위해 %c로 buf 먹어버리고 scanf로 파싱 해결
그냥 %d %d 를 쓰면 char를 무시하지 않음...

C,H는 적어도 하나 존재하며 <=100
---
4. Time Limit Exceeded
5. Wrong Answer
=> 뭐지 흠?
=> C 다음 바로 H가 오는 경우 실패함

---
결국 str로 갈 수 밖에 없네...

    int a = '100' - '0'; // garbage
    int b = '5' - '0'; // 5

[강의 방식]
- atoi를 쓰지 않고 자리수를 순회하면서 직접 구했다:
sum = 0;
for (i = 0; a[i] != 0; i++) {
    sum = sum * 10 + (a[i] - '0');
}
// 꽤 좋은 구현인 것 같다. 굳굳.
*/
void problem_31()
{
    int i, c = 1, h = 1; // 1을 기본값으로 주면 예외 처리 안 해도 됨.
    char str[10];

    READ_TXT("./resources/input31.txt", "rt", stdin);
    scanf("%s", str);
    for (i = 0; str[i] != 'H'; i++)
        ;
    if (str[i + 1] != 0)       // H 이후에 글자가 없는 경우
        h = atoi(str + i + 1); // H 다음 idx 부터
    str[i] = 0;                // H 인덱스를 끝으로 함.
    if (i != 1)                // C 이후에 H인 경우
        c = atoi(str + 1);     // C를 파싱하지 않음. 문자가 없어서 0이 되기 때문.
    printf("%d\n", c * 12 + h);
}
