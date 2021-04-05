#include <iostream>
#include <cassert>
#include "../include/debugopen.hpp"

/*
	[Silver 5]
	숫자 야구

	---규칙---
	맞히는자: 1~9 중 3개 조합
	피시험자: 1~9 중 3개 조합
	=> 같은 위치, 같은 숫자이면 strike
	=> 다른 위치, 같은 숫자이면 ball

	3 strike시 종료
	아니면 다시 시작 (새 숫자)

	---출력---
	주어진 시나리오에 대해, 영수가 생각하고 있을 가능성이 있는 수의 개수를 출력

	----------
	IDEA
	1. 숫자 야구를 그냥 풀어 버리는 방법을 생각했다가 너무 어려워서 포기

	2. 완전 탐색이니까 그런 방식으로 해야겠거니 생각했는데, 계속 (1) 아이디어로 접근하게 됨

	3. 구글링 해 버렸다...
	-> 987 ~ 123 사이 숫자를 탐색
	-> 주어진 N개의 조건에 맞는 경우 candidate++ 하면 된다고 함. (이게 맞나?)
		- 음~ 그렇게 하면 되겠네. test = (num, s, b) => sb

	-----
    실패
    1. 2%에서 틀렸는데 왜 틀렸는지 모르겠음
        => 서로 다른 숫자여야 하거든요..ㅋㅋ
    
    2. 또 틀렸습니다 :)
        => 진짜 모르겠음. 왜 틀렸는지
*/

using namespace std;

bool test(int A, int B, int strike, int ball)
{
    int i, j, cur, d = 1, d2 = 1, s = 0, b = 0;
    // counting strikes
    for (i = 0; i < 3; i++)
    {
        cur = (A / d) % 10;
        if (cur == (B / d) % 10)
            s++;

        //	counting balls
        d2 = 1;
        for (j = 0; j < 3; j++)
        {
            if (i != j && cur == (B / d2) % 10)
                b++;
            d2 *= 10;
        }
        d *= 10;
    }

    if (s == strike && b == ball)
        return true;
    return false;
}

int main()
{
    // 다 되는 걸로 봐선 구현은 완벽하다.
    // assert(test(123, 123, 3, 0));
    // assert(test(123, 132, 1, 2));
    // assert(test(123, 213, 1, 2));
    // assert(test(123, 231, 0, 3));
    // assert(test(123, 312, 0, 3));
    // assert(test(123, 321, 1, 2));
    // assert(test(123, 456, 0, 0));

    // 아니, 이게 왜 안되지?
    // 이건 제대로 작동하지 않아도 됨.
    assert(test(111, 123, 1, 0)); // 1S 2B 이 왜 나오냐고 ㅋㅋ

    // 코드
    int N, i, j, k, cnt = 0, d1, d2, d3;
    bool failed;
    READ_TXT("./input.txt", "rt", stdin);
    cin >> N;
    int num[N], strikes[N], balls[N];
    for (i = 0; i < N; i++)
        cin >> num[i] >> strikes[i] >> balls[i];

    for (i = 123; i <= 987; i++)
    {
        d1 = i / 100;
        d2 = (i / 10) % 10;
        d3 = i % 10;
        if (d1 == d2 || d1 == d3 || d2 == d3)
            continue;

        failed = false;
        for (j = 0; j < N; j++)
        {
            if (!test(i, num[j], strikes[j], balls[j]))
            {
                failed = true;
                break;
            }
        }
        if (!failed)
            cnt++;
    }
    cout << cnt << "\n";
    return 0;
}
