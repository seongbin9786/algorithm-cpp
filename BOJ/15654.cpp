#include <iostream>
#include <algorithm>

#include "../include/debugopen.hpp"

using namespace std;

int nums[9] = {0};
int input[9] = {0};
bool used[10001] = {0}; // input[i] <= 10,000
int N, M;

void backtrack(int curIdx)
{
    int j, i, num;
    // 매 자리수마다 후보는 1~N
    for (i = 1; i <= N; i++)
    {
        num = input[i];
        if (used[num])
            continue;

        // 해당 숫자 사용
        used[num] = true;
        nums[curIdx] = num;

        if (curIdx < M)
            backtrack(curIdx + 1);
        else
        {
            for (j = 1; j < M; j++)
                cout << nums[j] << " ";
            cout << nums[j] << "\n";
        }

        // 이번 자리수로 돌아온 경우.
        // 다음 숫자를 쓸 예정이므로 현재 숫자 반납
        used[num] = false;
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