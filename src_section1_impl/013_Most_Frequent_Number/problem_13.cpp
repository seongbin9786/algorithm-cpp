#include "problem_13.hpp"

/*
유형: 구현[풀이 전략]
(1). % 10으로 계속 나누면서 나머지에 대응되는 값을 ++ 하면 될듯?

(2). 100 자리니까 string 으로 받아와야 함.

(3). TC 1, 3, 5 Wrong Answer
=> 만약에 빈도수가 동일하면 더 큰 숫자가 우선순위

Q. 만약 동일한 자리수의 경우는? (없나봄?)
FIX: 문제 조건에 있었음. 더 큰 수를 출력하라.
*/
int problem_13()
{
    char str[101];
    int arr[10] = {0};
    int i, cur, freq;
    READ_TXT("./resources/input13.txt", "rt", stdin);
    scanf("%s", str);
    // O(N)
    for (i = 0; str[i] != 0; i++) // 굳이 strlen 필요 없음
    {
        cur = str[i] - '0';
        if (cur != 0)
            arr[cur]++;
    }
    freq = 1;
    // O(k)
    for (i = 2; i < 10; i++)
    {
        debug("[problem 13] arr[i]: %d\n", arr[i]);
        if (arr[freq] <= arr[i])
            freq = i;
    }
    printf("%d\n", freq);
    return 0;
}
