#include "problem_33.hpp"

/*
유형: 정렬
[풀이 전략]
정렬 후 같은 점수면 continue 하면서 ++ 하다가 i=0 에서 i=2가 된 점수를 출력

---
이 문제가 왜 선택 정렬의 응용 문제인지 모르겠다. 정렬은 뭘로도 그냥 하면 되는건데.
*/
void problem_33()
{
    int i, j, n, max = 0, tmp;
    READ_TXT("./resources/input33.txt", "rt", stdin);
    scanf("%d", &n);
    int arr[100] = {0};
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    // 내림차순 정렬
    std::sort(arr, arr + n, std::greater<int>());
    /*
    쉬운데 몇 번 막혔다. 딱히 배울 건 없는듯. Index 생각 정도?
    */
    j = 1;
    for (i = 0; i < n - 1; i++)
    {
        // 5 != 4 (at 4)
        // 4 != 3 (at 3)
        // 이걸 아래 if 문 밑에 넣을거면 arr[i+1]을 출력해야 한다.
        if (j == 3)
        {
            printf("%d\n", arr[i]);
            return;
        }
        if (arr[i] != arr[i + 1])
            j++;
    }
}
