#include "problem_26.hpp"

/*
유형: 구현
[풀이 전략]
best = i+1 - cnt(less than me); // 당연히 동일하면 못 앞지를듯.
*/
void problem_26()
{
    int i, j, n, best;
    READ_TXT("./resources/input26.txt", "rt", stdin);
    scanf("%d", &n);
    std::vector<int> arr(n);
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    for (i = 0; i < n; i++)
    {
        best = i + 1; // 기본 등수 = i+1
        for (j = 0; j < i; j++)
        {
            if (arr[i] > arr[j])
                best--; // 앞에서 나보다 작으면 추월 가능
        }
        printf("%d ", best);
    }
}
