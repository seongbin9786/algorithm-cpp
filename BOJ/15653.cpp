#include <iostream>

#include "../include/debugopen.hpp"

/*
	[Silver 3]
    N과 M(4)

    자연수 N과 M이 주어졌을 때, (N,M<=7)
    - 길이가 M이고,
    - 1~N까지의 자연수 중 중복 없이 M개를 고른 수열
    
    여기에다가 (4)라서 추가된 조건이,
    - 같은 수를 여러 번 골라도 된다.
    - 비내림차순이어야 한다. (중복 원소가 있는 오름차순이라고 생각하면 됨)
*/
using namespace std;

int nums[9] = {0};
int N, M;

void backtrack(int curIdx, int min)
{
    int i, num;
    // 매 자리수마다 후보는 1~N
    for (num = min; num <= N; num++)
    {
        // 해당 숫자 사용
        nums[curIdx] = num;

        if (curIdx < M)
            backtrack(curIdx + 1, num);
        else
        {
            for (i = 1; i < M; i++)
                cout << nums[i] << " ";
            cout << nums[i] << "\n";
        }

        // 이번 자리수로 돌아온 경우.
        // 다음 숫자를 쓸 예정이므로 현재 숫자 반납
        nums[curIdx] = 0;
    }
}

int main()
{
    int i;
    READ_TXT("./input.txt", "rt", stdin);
    cin >> N >> M;
    backtrack(1, 1);
}