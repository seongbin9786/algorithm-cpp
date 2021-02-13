#include "problem_32.hpp"

/*
유형: 정렬
(N <= 100)
선택 정렬 이론
-------------
가장 작은 수를 왼쪽에 차례로 쌓으면 정렬이 된다.
-----
min = i; 를 빼먹었는데 정렬된 배열에서 23이 중간에 있었다.
왜 그랬을까? + 왜 min = i가 필요할까?
=> 특정 사이클에서 min이 바뀌지 않으면, min은 정렬된 구역 내의 idx가 된다.
=> 이 idx와 비정렬 구역 idx의 값을 바꾸면 무조건 정렬에 실패하게 된다.
=> 따라서 역순으로 정렬된 배열의 경우 min = i가 필요 없겠지만 (항상 min은 정렬 구역 밖이므로)
=> 중간 중간 정렬된 배열인 경우 min = i 가 없으면 (or 뭐 배열의 끝이든 정렬 밖 구역이기만 하면 됨)
=> 정렬에 실패한다.
---
=> 땡! 역순이어도 실패합니다. 중간에 정렬이 다 된 경우이죠. (이러면 다시 윗 case가 되는거죠.)
=> 그러면 정렬이 다 된 경우 멈추면 될까요? 
=> 글쎄요. 정렬이 다 됐다고 판단하는 것도 cost니 그럼 더 이상 선택 정렬이 아니겠죠?
---
결론: min = i 가 가장 깔끔한 해결 방식이다.
*/
void problem_32()
{
    int i, j, n, min = 0, tmp;
    READ_TXT("./resources/input32.txt", "rt", stdin);
    scanf("%d", &n);
    int arr[100] = {0}; // vector나 pointer로 만들면 debugger에서 못 봄;
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    for (i = 0; i < n; i++)
    {
        min = i;
        for (j = i; j < n; j++)
            if (arr[min] > arr[j])
                min = j;
        tmp = arr[min];
        arr[min] = arr[i];
        arr[i] = tmp;
    }
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
}
