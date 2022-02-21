#include <stdio.h>
#include <algorithm>
#include "../include/debugopen.hpp"

using namespace std;

/*
    ATM (Silver 3)
    11399

    1~N명이 줄을 서 있고, 인출 소요 시간이 각 사람 별로 주어진다.
    각 사람의 인출 시간 = sum[...앞사람의 인출시간] + 본인의 인출시간
    총 인출 시간의 최소가 되는 배열 => [인출 시간의 합의 최소값]

    5
    3 1 4 3 2
    => 1 2 3 3 4 분이 걸리게 한다면
    => 1+3+6+9+13=32

    [Sol]
    오름차순 정렬을 해서 앞에 위치한 사람들의 소요 시간을 최소화하면 된다.
    앞 사람의 대기 시간은 뒷 사람 순번의 배만큼 영향을 주기 때문이다.

    1. 앞 사람까지의 대기 시간의 합을 담는 변수와
    2. 앞 사람의 대기 시간(1) + 내 대기시간을 담는 변수와
    3. (2)를 계속 더해나가는 변수가 필요하다.
    4. answer=(3)이다.

*/
// 오름차순 코드.
bool comp_11399(int a, int b)
{
    return a < b;
}

int main_11399()
{
    READ_TXT("input.txt", "rt", stdin);
    int N, i, delay = 0, total = 0;
    scanf("%d", &N);
    int nums[N];
    for (i = 0; i < N; i++)
    {
        scanf("%d", &nums[i]);
    }
    sort(&nums[0], &nums[N], comp_11399);
    for (i = 0; i < N; i++)
    {
        nums[i] += delay;
        delay = nums[i];
        total += nums[i];
    }
    printf("%d\n", total);
    return 0;
}
