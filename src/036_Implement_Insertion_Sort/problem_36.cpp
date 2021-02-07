#include "problem_36.hpp"

/*
유형: 정렬
N <= 100
- 오름차순

현재 원소를 왼쪽의 정렬된 배열에 넣는다. 이 때 원소가 들어갈 자리는 왼쪽 배열과 비교한다.
(음 생각보다 어렵다.. 구현이 불편하다; )
---
=> 그냥 외웠다. 삽입 정렬이 그렇지 뭐..
*/
void problem_36()
{
    int i, j, key, n;
    int arr[100] = {0};
    READ_TXT("./resources/input36.txt", "rt", stdin);
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", arr + i);
    for (i = 1; i < n; i++)
    {
        key = arr[i]; // 아래 루프에서 arr[i]가 먼저 덮어쓰임
        for (j = i - 1; j >= 0 && arr[j] > key; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = key;
    }
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
}
