#include "problem_16.hpp"

/*
유형: 구현
[풀이 전략]
입력 받은 문자열 a[101], b[101]에 대해 
<1> a를 순회하면서 a[i]에 해당하는 문자를 b에서 찾고, replace해서 지운다.
=> O(N*M)

<2> a를 순회하면서 a[i]에 해당하는 문자를 b에서 찾고, 맨 뒤 문자와 swap 후 NULL 문자 처리한다.
=> O( N * M/2 ) (처음에는 M, 마지막엔 1)

<3> dictionary를 만들고.. 탈락

<4> 알파벳 순으로 a,b를 정렬한 후 동시에 순회하면서 일치하지 않는 a[i]가 생기면 false, 맞으면 true
=> O( N * log N ) (정렬 복잡도에 의존, merge sort, quick sort) (N>=M 일 때)

이왕하는거 4번으로 갈까? 근데 c에서 quicksort 어케함 => algorithm => std::sort 하나 배웠네
*/
int problem_16()
{
    char a[101];
    char b[101];
    int i;
    READ_TXT("./resources/input16.txt", "rt", stdin);
    scanf("%s", a);
    scanf("%s", b);
    std::sort(a, a + strlen(a));
    std::sort(b, b + strlen(b));
    debug("%s , %s\n", a, b);
    for (i = 0; a[i] != 0; i++)
    {
        if (a[i] != b[i])
        {
            printf("NO");
            return 0;
        }
    }
    printf("YES");
    return 0;
}
