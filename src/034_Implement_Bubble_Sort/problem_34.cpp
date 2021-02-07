#include "problem_34.hpp"

/*
유형: 정렬
문제: [34. 버블 정렬]

각 원소를 계속 비교하면서, 큰 원소를 뒤쪽 끝으로 보낸다.
O(n^2) 임을 기억하면 구현에 힌트가 될 수 있을 듯하다.
또한 계속 비교하는 것도 힌트가 된다.

*/
void problem_34()
{
    int i, j, n, tmp;
    int arr[100] = {0};
    READ_TXT("./resources/input34.txt", "rt", stdin);
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", arr + i);
    for (i = 0; i < n; i++)
        for (j = 1; j < n - i; j++)
            if (arr[j - 1] > arr[j])
            {
                tmp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = tmp;
            }
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
}
