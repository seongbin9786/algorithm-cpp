#include <cstdio>
#include <vector>
#include <algorithm>
#include "../include/debugopen.hpp"

using namespace std;

int main_11047()
{
    int N, K, i, used = 0;
    int coins[10];
    READ_TXT("input.txt", "rt", stdin);
    scanf("%d %d", &N, &K);
    for (i = 0; i < N; i++)
        scanf("%d", coins + i);
    for (i = N - 1; i >= 0; i--)
    {
        if (K == 0)
            break;
        if (coins[i] > K)
            continue;
        // 가장 큰 코인을 사용한다.
        used += K / coins[i];
        K = K % coins[i];
    }
    printf("%d\n", used);
    return 0;
}
