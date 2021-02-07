#include "problem_25.hpp"

/*
유형: 구현
[풀이 전략]
1. O(N): max 찾고 rank를 준다.
2. O(N): 같은 max을 찾고 rank를 준다. num++;
    - char 배열을 하나 선언해 값을 저장한다. (char = 1바이트 = -128 ~ 127 이므로 문제 X)

=> 같은 max을 찾을 때 next_max을 찾는 것도 좋은듯.. 그러나 귀찮.

[강의]
그냥 2중 포문 쓰고 i=1~N, j=1~N 하면 된다.

---
TC 2. exit_code -10 ~~~ 뜨는데 뭘까?
=> char 대신 int를 쓰니 됐음.
=> WSL에서는 char로 돌려도 TC 2 정상 통과함.. (흠..)
다시 빌드해봐도 char은 오류가 남. 나중에 보기로 ㄱㄱ
*/
void problem_25()
{
    int i, j, n, rank = 1, num = 0, max = 0;
    READ_TXT("./resources/input25.txt", "rt", stdin);
    scanf("%d", &n);
    std::vector<int> num_arr(n);
    std::vector<int> rank_arr(n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &num_arr[i]);
        debug("num_arr[%d]: %d\n", i, num_arr[i]);
    }
    for (j = 0; j < n; j++)
    {
        // 최댓값 찾기
        max = 0;
        for (i = 0; i < n; i++)
            if (max < num_arr[i])
                max = num_arr[i];
        debug("min: %d\n", max);
        // 동점자에게 rank 주고 max 찾기에서 배제
        for (i = 0; i < n; i++)
            if (max == num_arr[i])
            {
                rank_arr[i] = rank;
                num_arr[i] = -1; // 점수 구간이 0~100임
                num++;
            }
        // 동점자 처리
        debug("num: %d\n", num);
        rank += num;
        num = 0;
    }
    for (j = 0; j < n; j++)
        printf("%d ", rank_arr[j]);
}
