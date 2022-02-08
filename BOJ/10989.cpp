#include <cstdio>
#include "../include/debugopen.hpp"

using namespace std;

/**
 * [Silver 5] 수 정렬하기 3
 * - 예전에 틀렸던 문제
 *
 * 1. 일단 천만 개의 숫자를 입력받으므로 빠른 입력 수단이 필요하다. (cin ---> scanf)
 * 2. 입력값의 범위가 1~10,000의 자연수이므로, 배열의 Key로 중복 원소의 개수를 세면 4MB로 처리 가능!
 */

int main_10989()
{
    READ_TXT("./input.txt", "rt", stdin);
    int N, i, j, cur;
    scanf("%d", &N);
    int arr[10001] = {0};
    for (i = 0; i < N; i++)
    {
        scanf("%d", &cur);
        arr[cur]++;
    }
    for (i = 1; i <= N; i++) // 왜 10,000까지 다 돌려야해? 아? ?? 아~ N까지만 돌리는 게 아님
        for (j = 0; j < arr[i]; j++)
            printf("%d\n", i);
    return 0;
}