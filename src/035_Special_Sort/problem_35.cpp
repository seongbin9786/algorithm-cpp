#include "problem_35.hpp"

/*
유형: 정렬
[풀이 전략]
배열 두 개로 넣고 concat 하는 게 제일 쉬울듯
근데 그럴거면 정렬 응용이라고 왜 했겠음?
아~ 버블 소트에서 크기 비교로 하지 말고
음수 양수 인걸로만 하면 될 듯
case가 4개임

-1 -3
-3 -1
=> stay

-3 5
=> stay

5 -3
=> CHANGE!!!

5 7
7 5
=> stay

*/
void problem_35()
{
    int i, j, n, tmp;
    int arr[100] = {0};
    READ_TXT("./resources/input35.txt", "rt", stdin);
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", arr + i);
    for (i = 0; i < n; i++)
        for (j = 1; j < n - i; j++)
            if (arr[j - 1] > 0 && arr[j] < 0) // MAGIC!
            {
                tmp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = tmp;
            }
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
}
