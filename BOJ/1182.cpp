#include <iostream>

#include "../include/debugopen.hpp"

/*
	[Silver 2]
    부분수열의 합 

    - N개의 정수로 이루어진 수열 (N <= 20)
    - 크기가 양수인 부분수열

    ---입력---
    N S
    N of integers...

    ---출력---
    부분수열의 합이 S인 경우의 개수

    -----
    [IDEA]

    1. 각 원소를 T/F로 선택해서 모든 T/F 경우의 수를 다 해보기
    bool pick[21] = {0};

    ----
    틀렸습니다.

    1. 크기가 양수인 이게 문젠가? 즉 0 0 이런식으로 주어지면 
    => 맞네
    
*/
using namespace std;

int input[21] = {0};
bool used[21] = {0};
int N, S, cost = 0;

void backtrack(int curIdx)
{
    if (curIdx > N)
    {
        int i, sum = 0;

        for (i = 1; i <= N; i++)
            if (used[i])
                sum += input[i];
        if (S == sum)
            cost++;
        return;
    }
    // 아래는 <= N 일때만 수행된다.
    // 왜 틀렸지?
    used[curIdx] = true;
    backtrack(curIdx + 1);
    used[curIdx] = false;
    backtrack(curIdx + 1);
}

int main()
{
    int i;
    READ_TXT("./input.txt", "rt", stdin);
    cin >> N >> S;
    for (i = 1; i <= N; i++)
        cin >> input[i];
    backtrack(1);
    // 모든 원소 미선택 시 0이 무조건 나오는데 이걸 빼준다.
    cout << (S == 0 ? cost - 1 : cost) << "\n";
}
