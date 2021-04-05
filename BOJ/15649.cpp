#include <iostream>

#include "../include/debugopen.hpp"

/*
	[Silver 3]
    N과 M(1)

    자연수 N과 M이 주어졌을 때, (N,M<=8)
    - 길이가 M이고,
    - 1~N까지의 자연수 중 중복 없이 M개를 고른 수열

    => 즉 원소가 1~N이고 길이가 M인 순열(중복 없고 순서 있게 모든 가능성을 출력)을 출력하라

    (ex)
    N=3, M=1
    1
    2
    3

    (ex)
    N=5, M=3
    1 2 3
    1 2 4
    1 2 5
    ...
    5 4 3

    근데 이게 백트래킹인가?

    ----
    [IDEA]
    1. M개를 선택해야 한다.
    2. 모든 가능성을 순회해야 한다.
    3. 재귀로 푼다.
    4. for문을 많이 사용하지 않는다.

*/
using namespace std;

bool used[9] = {0};
int nums[9] = {0};
int N, M;

/*
    중복 조합 고르듯 매 자리수마다 숫자를 골라주면 된다.
    이 때 사용된 숫자이면 넘어가는 것만 구현하면 된다.

    출력이 문제인데...

*/
void backtrack(int curIdx)
{
    int i, num;
    // 매 자리수마다 후보는 1~N
    for (num = 1; num <= N; num++)
    {
        // 숫자 사용 불가 시 PASS
        if (used[num])
            continue;

        // 해당 숫자 사용
        used[num] = true;
        nums[curIdx] = num;

        // 출력부: curIdx=M 일 때, 이걸 채우고 나서 출력해야 함
        // 자릿수에 대응되는 숫자를 어떻게 파악할 수 있을까?
        // 그냥 선택하자 마자 출력하는 방법도 있잖아요
        // 근데 그럼 첫 출력은 완벽한데, 두 번째부터는 가지친 숫자들만 출력됨
        // 그냥 배열 하나 더 쓰면 됨 굿

        // 재귀부: 다음 자릿수로 이동
        if (curIdx < M)
            backtrack(curIdx + 1);
        else
        {
            for (i = 1; i < M; i++)
                cout << nums[i] << " ";
            cout << nums[i] << "\n";
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
    backtrack(1);
}