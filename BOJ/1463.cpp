#include <stdio.h>
#include <algorithm>
#include "../include/debugopen.hpp"

using namespace std;

/*
    1463
    1로 만들기

    ( 1 < X <= 10^6 )
    정수 X를 아래의 연산을 사용해 1로 만드는 최소 횟수를 출력하라
    - 3으로 나누어 떨어진다면 3으로 나누기
    - 2로 나누어 떨어지면 2로 나누기
    - 1을 빼기

    [DP 문제]
    - 피보나치는 재귀이다.
    - 따라서 재귀로 풀어야 할 것 같다.

    재귀이긴 한데 이런 식이면..?

    아, DP는 memo를 해야 한다.

    128MB 제한에 int 100만개를 넣을 수 있을까?
    1,000,000 * 4byte = 1,000 * 4KB = 4,000KB
    된다

    근데 지금 코드에서 값을 저장할 수 있나?
    애초에 가장 작은 case가 마지막에 계산되는 형태 아닌가?
*/

int memo_1463[1000001] = {0};

/*

    [ Step 1: 처음 생각한 방식 ]

    (예제 정답)
    10
    -> 3

    (재귀 버전 1)
    (무지성으로 나눠지는 걸로 하는 경우 - greedy처럼..)
    (재귀로 생각 중)
    10
    -> 5 [1]
    -> 4 [2]
    -> 2 [3]
    -> 1 [4]

    ==> ??? 정답이 안나오네

    어떻게 2로 안나누고 배길 수 있지?
    ==> min 으로 해버리면 될듯? ( 그리디 탈출, 재귀 버전 2 )
    ==> 근데 이거 저장하는 걸로는 못 풀 거 같은데? ( 그리디 사고방식은 탈출했으나 DP 생각은 못하는 중 )

    [ Step 2: DP처럼 생각해보자 ]

    저장한 값으로 풀려면, DP의 풀이법이라면,
    memo[1] ~ 쭉 쌓아 올리는 게 맞다 ( DP스러운 생각으로 전환 )
    쌓아 올릴 때는 memo[x] = min( memo[x/3], memo[x/2], memo[x-1] ); 로 짜면 되겠다

    -끝-
*/
// 재귀 버전(2)으로 생각 중
int dp_1463(int x)
{
    if (x == 1)
        return 1;
    else if (x % 3 == 0 && x % 2 == 0)
        return min(min(dp_1463(x / 3), dp_1463(x / 2)), dp_1463(x - 1)) + 1;
    else if (x % 3 == 0)
        return min(dp_1463(x / 3), dp_1463(x - 1)) + 1;
    else if (x % 2 == 0)
        return min(dp_1463(x / 2), dp_1463(x - 1)) + 1;
    else
        return dp_1463(x - 1) + 1;
}

// DP 버전
int findMinimumTries(int x)
{
    for (int i = 2; i <= x; i++)
    {
        if (i % 3 == 0 && i % 2 == 0)
            memo_1463[i] = min(min(memo_1463[i / 3], memo_1463[i / 2]), memo_1463[i - 1]) + 1;
        else if (i % 3 == 0)
            memo_1463[i] = min(memo_1463[i / 3], memo_1463[i - 1]) + 1;
        else if (i % 2 == 0)
            memo_1463[i] = min(memo_1463[i / 2], memo_1463[i - 1]) + 1;
        else
            memo_1463[i] = memo_1463[i - 1] + 1;
    }
    return memo_1463[x];
}

int main_1463()
{
    int X;
    READ_TXT("input.txt", "rt", stdin);
    scanf("%d", &X);
    memo_1463[1] = 0;
    printf("%d\n", findMinimumTries(X));
    return 0;
}