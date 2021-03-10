#include <stdio.h>
#include <utility> // pair

using namespace std;

/*
	[Silver 3]
	피보나치 함수

	0.25초 시간제한
	0 <= N <= 40

	---
	[오답]
	1. 시간 초과: memoization 필요한듯
    => pair로 겨우했다. "pair의 배열" 쓰기가 너무 힘들다..
    => memoization만 있으면 되는데 머리로는 아는데 C++로 코딩하기가 너무 어렵다.
    => 아예 책을 하나 사던가 해야 하나? 그냥 일부 문법만 알려니 모르는 게 너무 많았다.

    => pair<int, int> arr[N]; 으로 생성하면 {0,0} 페어가 N개 생성된다는 것을 몰라서 거의 30분을 ㅋㅋ
*/
int z1, o1, z2, o2;
pair<int, int> _arr[41];

pair<int, int> fib(int x)
{
    if (_arr[x].first != 0 || _arr[x].second != 0)
        return _arr[x];
    else
    {
        auto [z1, o1] = fib(x - 1);
        auto [z2, o2] = fib(x - 2);
        _arr[x] = make_pair(z1 + z2, o1 + o2);
        return _arr[x];
    }
}

int main()
{
    int i, n, x;
    scanf("%d", &n);
    _arr[0] = make_pair(1, 0);
    _arr[1] = make_pair(0, 1);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &x);
        auto [zero, one] = fib(x);
        printf("%d %d\n", zero, one);
    }
    return 0;
}
