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

void remove_at(int *S, int pos, int n)
{
    // 삭제 대상 칸 뒤부터 하나씩 앞으로 덮어쓰면 된다.
    while (pos < n - 1)
    {
        S[pos] = S[pos + 1];
        pos++;
    }
}

int runSimulation(int *S, int n, int k)
{
    int r = 0; // r 초기화 안 하면 seg fault
    while (n > 1)
    {
        r = (r + k) % n;
        remove_at(S, r, n);
        n--;
        // r = (r + 1) % n; // 이게 필요 없음. 삭제돼버려서 r++ 된 셈임
    }
    // 찾기
    r = 0;
    while (S[r] == 0) // 꺼진 양초인 경우 한 칸씩 넘어감
        r++;
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
