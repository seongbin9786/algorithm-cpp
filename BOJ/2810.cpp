#include <iostream>

/*
	[Bronze 2]
	컵홀더
	
	이 줄에 사람들이 모두 앉았을 때, 컵홀더에 컵을 꽂을 수 있는 최대 사람의 수를 구하는 프로그램을 작성하시오.
	
	S는 일반 좌석
	L은 커플석 (항상 두개씩)
	컵홀더를 *로 표시하면: *S*LL*LL*S*S*LL*
	=> 위의 예에서 적어도 두 명은 컵홀더를 사용할 수 없다.

	1. 틀렸습니다. 이유 => 바로 깨달음. LL 사이에 자리가 컵홀더가 하나씩 있음;
*/

using namespace std;

int main()
{
    int i, n, cups = 1, res;
    char str[52] = {0}; // str[50]에서 i++로 null 문자를 넘길 경우 대비해 0으로 초기화 하고 배열 크기 52
    cin >> n >> str;

    for (i = 1; str[i] != 0; i++)
    {
        if (str[i - 1] == 'L' && str[i] == 'L')
        {
            cups--; // 컵을 하나씩 못 씀
            i++;    // 다만 LL 마다 하나씩은 있으니까, LL끼리 구분해줘야 해서 이렇게 함
        }
    }
    res = cups > 0 ? n : n + cups; // res <= n
    cout << res << '\n';
    return 0;
}
