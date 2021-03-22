#include <stdio.h>
#include <stdlib.h>

/*
    생일 케이크(n, k) => last-survive index 반환

    ver.1: 촛불을 제거하지 않고 그냥 세면서 넘어감 (+1씩)
    ver.2: 촛불을 제거함
    ver.3: 촛불을 제거하는데, 연결 리스트 기반으로 함.
*/
int *buildList(int n)
{
    int i;
    int *S = (int *)malloc(sizeof(int) * n);
    for (i = 0; i < n; i++)
        S[i] = i + 1; // 숫자로 초기화 (양초 번호)
    return S;
}

int runSimulation(int *S, int n, int k)
{
    int i, r = 0, len = n; // r 초기화 안 하면 seg fault
    while (n > 1)
    {
        i = 0;
        while (i < k) // k개 만큼 건너뛰기: 그냥 + k 하면 안 되는 게, 꺼진 촛불은 넘기지 않은 것이기 때문
        {
            r = (r + 1) % len;
            if (S[r] != 0)
                i++;
        }
        S[r] = 0;          // 불 끄기만 하기
        n--;               // 양초 개수 줄이기
        r = (r + 1) % len; // 다음 양초에서 시작해서 k개를 건너 뛰므로.
    }
    // 찾기
    while (S[r] == 0) // 꺼진 양초인 경우 한 칸씩 넘어감
        r = (r + 1) % len;
    return S[r];
}

void candle(int n, int k)
{
    int *S = buildList(n);
    printf("n=%d, k=%d 일 때, %d번 째 양초가 마지막까지 남습니다.\n", n, k, runSimulation(S, n, k));
}

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);
    candle(n, k);
    return 0;
}
