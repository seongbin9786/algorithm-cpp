#include <stdio.h>
#include <algorithm> //sort
#include <functional>
#include <vector>

/*
	[Bronze 1]
	수 정렬하기 1
	[Silver 5] 
	수 정렬하기 2
	[Silver 5]
	수 정렬하기 3
	* 8MB 제한이 있음 ( how -? )
	* 대신 시간 제한이 2->3초로 늘어남
	=> short 쓰기
	---
	1. int로 그냥 그대로 시도해봄
	int=4Byte
	10,000,000
	=> 40,000,000 Byte
	=> 40,000 KB
	=> 40MB

	2. short로 시도해봄. 될 줄 알았는데 ㅎ 계산해보니 안 되는 게 당연했음
	short=2Byte
	10,000,000
	=> 20MB
	=> vector<short>도 메모리 초과 (vector 안 쓰고 싶었지만 ㅠㅠ)

	3. 8MB 제한이면 전부 저장할 수는 없는 걸로 보임
	=> 
*/
int main()
{
    // short arr[10000000];
    // int i, n;
    // scanf("%d", &n);
    // for (i = 0; i < n; i++)
    // 	scanf("%d", &arr[i]);
    // std::sort(arr, arr + n, std::less<short>());
    // for (i = 0; i < n; i++)
    // 	printf("%d\n", arr[i]);
    // return 0;

    int i, n;
    scanf("%d", &n);
    std::vector<short> arr(n); // 꼭 이렇게 크기를 지정해줘야만 하는걸까..?
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    std::sort(arr.begin(), arr.end(), std::less<short>());
    for (i = 0; i < n; i++)
        printf("%d\n", arr[i]);
    return 0;
}