#include <stdio.h>
#include <math.h>
#include "../include/debugopen.hpp"

/*
	[Silver 3][구현]
	B <= 6.4 * 10^7 (= 64,000,000)
	
	1. 가장 낮은 땅과 가장 높은 땅의 차이를 구한다. (음수 포함)
	2. 채우는 방법과 빼는 방법 2개의 cost를 계산한다.
	3. 더 작은 cost가 수반되는 방법을 출력한다. (cost, height)
	4. 만약 같은 cost인 경우 채우는 방법의 경우로 출력한다.

	---
	[오답]
	실패 1: 마지막 예제를 확인하지 않았음 (B 개수 고려 제출)
	실패 2: B 개수를 고려해 제출함
	실패 3: 평균 (round(sum / num))을 계산해 개수를 고려했지만 틀렸음
    ---
	다음 시도: 평균이 아니라 최빈값으로 가야하나? 둘 중 무엇이 더 우월한 지 모르겠음;
    이런 식이면 너무 끊임 없는 것 같은데.. 좀 더 쉽게 최적해를 도출하는 방법이 없을까?

*/
int main()
{
    const int HIGHEST = 257;
    const int LOWEST = -1;
    bool mean_failed = false;
    int i, j, min = HIGHEST, max = LOWEST, mean, mean_b, min_sum = 0, max_sum = 0, mean_sum = 0;
    int N, M, B;
    int arr[500][500]; // N, M <= 500
    READ_TXT("./input.txt", "rt", stdin);
    scanf("%d %d %d", &N, &M, &B);
    // 1. 입력
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            scanf("%d", &arr[i][j]);
    // 2. min, max 확인
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            mean += arr[i][j];
            if (min > arr[i][j])
                min = arr[i][j];
            if (max < arr[i][j])
                max = arr[i][j];
        }
    }
    // 3. 평균값 계산 추가 (반올림 해야 최소 차이일 것으로 보임)
    mean = round(mean / (N * M));
    mean_b = B;
    // 4. 개별적인 차이 계산
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            if (arr[i][j] > mean)
            {
                mean_sum += (arr[i][j] - mean) * 2; // 높이를 낮추는건 cost=2
                mean_b++;
            }
            if (arr[i][j] < mean)
            {
                if (mean_b <= 0)
                    mean_failed = true;
                mean_sum += mean - arr[i][j]; // 퍼 올리는 건 cost=1
                mean_b--;
            }
            min_sum += (arr[i][j] - min) * 2; // 높이를 낮추는건 cost=2
            max_sum += max - arr[i][j];       // 퍼 올리는 건 cost=1
        }
    }
    // mean_sum을 출력하는 경우:
    // 1. mean_sum이 유일하게 우월한 경우
    // 2. mean_sum = min_sum 인 경우
    if (!mean_failed && mean_sum < max_sum && mean_sum <= min_sum)
        printf("%d %d\n", mean_sum, mean);
    // 갖고 있는 블록이 부족해서 쌓기로는 해결할 수 없는 경우
    else if (max_sum > B)
        printf("%d %d\n", min_sum, min);
    // min_sum이 크거나 동일한 개수인 경우 max 출력
    else if (min_sum >= max_sum)
        printf("%d %d\n", max_sum, max);
    else
        printf("%d %d\n", min_sum, min);
    return 0;
}
