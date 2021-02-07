#include "problem_23.hpp"

/*
유형: 구현
[풀이 전략]
간단한데? 그냥 증가할 때까지 + 하다가 막히면 max와 비교해 저장해놓고,
이후 원소로 continue 하면서 len=0 으로 초기화만 하면 끝인거 같은데

---
예제 데이터에서 틀림
=> 5가 나와야 하는데 4가 나옴.
Q. ++ 개수가 적은가? Yes.
그래서 1부터 시작하기로 함.
*/
void problem_23()
{
    int i, n, max = 0, len = 1;
    READ_TXT("./resources/input23.txt", "rt", stdin);
    scanf("%d", &n);
    std::vector<int> arr(n); // 값이 0으로 초기화 돼있을까? 절대 안 그럴듯ㅋㅋ => 와 뭐지? ㄹㅇ 0인데?
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]); // arr + i 이 안되네? arr. 찍어보니 method가 있네 역시 C++ / &(arr+i)는 될까? 귀찮다...
        debug("arr[%d] = %d\n", i, arr[i]);
    }
    for (i = 0; i < n - 1; i++)
    {
        if (arr[i + 1] >= arr[i])
        {
            len++;
            debug("arr[%d] = %d , arr[%d] = %d, len = %d\n", i + 1, arr[i + 1], i, arr[i], len);
            // 여기서 max를 갱신하면 여러 번 갱신되겠지만 마지막 원소일 때도 따로 체크할 필요 X
            if (len > max)
                max = len;
        }
        else
            len = 1; // len을 1부터 시작해야 할 듯. 13->10으로 넘어갈 때 ++ 되지 않기 때문.
    }
    printf("%d\n", max);
}
