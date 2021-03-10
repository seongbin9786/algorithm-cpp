#include <stdio.h>

/*
	[Silver 1]
	이항 계수 2
	1 <= N <= 1000

	nCk = (n-1)Ck + (n-1)C(k-1)

	1초 시간 제한이고 혹시 모르니 memo 사용
    ---
    [오답]
    1. 멍청하게 memo 안 했음
    2. (n k)를 10,007으로 나눈 나머지 출력을 마지막에만 하는 줄 알았음
*/
int _arr[1001][1001] = {0};

int nCk(int n, int k)
{
    if (_arr[n][k])
        return _arr[n][k];

    if (n == k || k == 0)
        _arr[n][k] = 1;
    else
        _arr[n][k] = (nCk(n - 1, k) + nCk(n - 1, k - 1)) % 10007;
    return _arr[n][k];
}

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);
    printf("%d\n", nCk(n, k));
    return 0;
}