#include "problem_42.hpp"

/*
유형: 구현
[풀이 전략]
[N] [target]
[elements...]

1. sort them asc
2. print number of search trials
*/
void problem_42()
{
    int m, target, i, n, cnt = 0, lt, rt;
    int k; // debug purpose
    READ_TXT("./resources/input42.txt", "rt", stdin);
    scanf("%d %d", &n, &target);
    //m = n % 2 == 1 ? (n + 1) / 2 : n / 2;
    lt = 0, rt = n - 1;
    std::vector<int> arr(n);
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    std::sort(arr.begin(), arr.end(), std::less<int>()); // Order ASC - ASC 정렬은 기본 값이라 굳이 less 쓸 필요는 없음.
    while (lt <= rt)                                     // 등호가 있어야 lt=rt 일 때의 case 가능 + lt <= rt 로 종료 조건 대체 (Good)
    {
        m = (lt + rt) / 2;
        // debug
        for (k = 0; k < n - 1; k++)
            debug("%d, ", arr[k]);
        debug("%d\n", arr[k]);
        cnt++;
        debug("arr[%d] = %d\n", m, arr[m]);
        if (arr[m] == target)
            break;
        // m을 기준값으로 두고 +1,-1 이므로 범위는 절반씩 줄어듦
        // m+1, m-1로 설정하는 이유 => m은 어차피 아니기 때문에.
        if (arr[m] > target)
            rt = m + 1; // m+1
        else
            lt = m - 1; // m-1
    }
    printf("%d\n", cnt);
}
