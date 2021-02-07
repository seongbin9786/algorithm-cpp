#include "problem_22.hpp"

/*
유형: 구현
[풀이 전략]
일단 음수가 있는 걸 확인했음
size=2 이면 [0],[1] 더하고
그 후에 [0]을 빼고 [2]을 더하면 되는게 어렵나?

그냥 그렇게 하면 될 거 같은데
아니면 배열을 쓰면 훨씬 쉬울듯?
배열 ㄱㄱ

일단 n < size 인 경우 체크 X

---
1. Wrong Answer
4, 5. Time Limit Exceeded 

=> 일단 알고리즘 최적화 필요 ( window )

---
1. Wrong Answer는 뭘 틀린걸까?
=> 봤는데 별 거 없었음
=> 얘는 내 가정의 오류라기 보단 잘못 짰음. 논리 오류.
=> i < n-size 이므로, i는 n-size-1까지 감
=> i + size - 1 의 최댓값은 n-2 였음.
=> 앞으론 인덱스 생각을 정확히 하자. 역시 반복문은 idx 계산이 젤 어려움.
+ 이런건 edge case를 생각하는 예제들을 많이 학습해야 할 듯. 그냥 가만히 생각해선 떠올릴 수 없는듯 (=> 창조 불가)
*/
void problem_22()
{
    int i, n, size, cur = 0, max = -99999; // 음수 합일수도 있으니까.
    READ_TXT("./resources/input22.txt", "rt", stdin);
    scanf("%d %d", &n, &size);
    int *arr = new int[n];
    for (i = 0; i < n; i++)
        scanf("%d", arr + i);
    // 초기 cur값 계산
    for (i = 0; i < size; i++)
        cur += arr[i];
    // 초깃값이 계산돼있으므로 i=1부터 시작해야 함.
    for (i = 1; i <= n - size; i++)
    {
        cur -= arr[i - 1];
        cur += arr[i + size - 1];
        // n-size + size-1 => n-1 까지 가는거니까 맞는거라고 생각했는데
        // <= 까지 줬어야 했음. 왜? (모르겠다.)
        if (cur > max)
            max = cur;
    }
    printf("%d\n", max);
    return;
}
