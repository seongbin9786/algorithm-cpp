#include <iostream>
#include <algorithm>

#include "../include/debugopen.hpp"

/*
	[Silver 3]
    N과 M(7)

    자연수 N과 M이 주어졌을 때, (N,M<=8)
    - 길이가 M이고,
    
    여기에다가 (7)라서 추가된 조건이,
    - 주어진 N개의 자연수 중 중복 없이 M개를 고른 수열
    - 둘째 줄에 N개의 수가 주어진다. 입력으로 주어지는 수는 10,000보다 작거나 같은 자연수이다.
    - 중복 가능
    - 순열 순서는 사전순 출력
*/
using namespace std;

int nums[9] = {0};
int input[9] = {0};
int N, M;

void backtrack(int curIdx)
{
    int j, i, num;
    for (i = 1; i <= N; i++)
    {
        num = input[i];

        nums[curIdx] = num;

        if (curIdx < M)
            backtrack(curIdx + 1);
        else
        {
            for (j = 1; j < M; j++)
                cout << nums[j] << " ";
            cout << nums[j] << "\n";
        }

        nums[curIdx] = 0;
    }
}

int main()
{
    int i;
    READ_TXT("./input.txt", "rt", stdin);
    cin >> N >> M;
    for (i = 1; i <= N; i++)
        cin >> input[i];
    sort(input + 1, input + N + 1);
    backtrack(1);
}