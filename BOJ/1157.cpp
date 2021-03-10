#include <stdio.h>

/*
    [Bronze 1]
    문자열 길이 N <= 1,000,000
    대소문자 무시
    동일 횟수 >= 2 이면 ? 출력
    가장 많이 쓰인 알파벳 출력 (대문자로)
*/
int main()
{
    int i;
    int cnt[26] = {0};
    int max = 0;
    int dup = 0;
    char buf[1000001];
    scanf("%s", buf);
    for (i = 0; buf[i] != 0; i++)
        cnt[buf[i] - (buf[i] >= 'a' ? 'a' : 'A')]++;
    for (i = 1; i < 26; i++)
    {
        if (cnt[max] == cnt[i])
            dup++;
        if (cnt[max] < cnt[i])
        {
            max = i;
            dup = 0;
        }
    }
    printf("%c\n", dup > 0 ? '?' : ('A' + max));
    return 0;
}
