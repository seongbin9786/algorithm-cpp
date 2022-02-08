#include <stdio.h>
#include "../include/debugopen.hpp"

using namespace std;

/*
    숫자야구 2503
    숫자야구를 이기는 남은 횟수를 구하는 게 아니라,
    숫쟈야구의 남은 경우의 수를 출력하는 것이다.

    123 ~ 987
*/
bool hasZeroOrDuplicateNumber_2503(int num)
{
    // 중복되는 숫자가 포함되는 경우 배제
    int n0 = num / 100;
    int n1 = (num / 10) % 10;
    int n2 = num % 10;

    if (n0 == 0 || n1 == 0 || n2 == 0) // 0 제외
        return true;
    if (n0 == n1 || n0 == n2 || n1 == n2) // 동일 숫자 제외
        return true;
    return false;
}

bool isValidQuery_2503(int target, int query, int strikes, int balls)
{
    int i, j;
    int t[3] = {target / 100, (target / 10) % 10, target % 10};
    int q[3] = {query / 100, (query / 10) % 10, query % 10};

    // 같은 자리가 동일하면 strike
    for (i = 0; i < 3; i++)
        if (t[i] == q[i])
            strikes--;

    // t0 ~ t1의 자리를 q0 ~ q2의 다른 자릿수와 비교해 동일하면 ball

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            if (i != j && t[i] == q[j])
                balls--;

    // 계산된 값과 인자와 동일하면 true 반환.
    return strikes == 0 && balls == 0;
}

int main_2503()
{
    int N, i = 0, j = 0, cnt = 0;
    READ_TXT("input.txt", "rt", stdin);
    scanf("%d", &N);
    int nums[N] = {0};
    int strikes[N] = {0};
    int balls[N] = {0};
    bool valid[988];

    for (i = 0; i < N; i++)
        scanf("%d %d %d", &nums[i], &strikes[i], &balls[i]);

    // 조건에 안 맞는 숫자는 미리 valid에서 제외 => 계산에서 제외
    for (i = 123; i < 988; i++)
        if (hasZeroOrDuplicateNumber_2503(i))
            valid[i] = false;
        else
            valid[i] = true;

    // 질의에 맞는 후보 추리기
    for (i = 0; i < N; i++)
        for (j = 123; j < 988; j++)
            if (valid[j])
                valid[j] = isValidQuery_2503(j, nums[i], strikes[i], balls[i]);

    // 정답 후보의 개수 세기
    for (i = 123; i < 988; i++)
        if (valid[i])
            cnt++;

    printf("%d\n", cnt);
    return 0;
}
