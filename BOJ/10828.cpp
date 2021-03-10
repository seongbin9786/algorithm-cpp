#include <stdio.h>
#include <stack>
#include <cstring> // strcmp
#include "../include/debugopen.hpp"

/*
	[Silver 4]
	스택
	
	스택을 구현하기 보단 문자열 다루기인듯,,,
	
*/
using namespace std;

int main()
{
    int i, j, n, res;
    char buf[100] = {0};
    READ_TXT("./input.txt", "rt", stdin);
    scanf("%d", &n);
    stack<int> s;
    for (i = 0; i < n; i++)
    {
        scanf("%s", buf);
        if (strcmp(buf, "top") == 0)
            printf("%d\n", s.empty() ? -1 : s.top());
        else if (strcmp(buf, "size") == 0)
            printf("%d\n", s.size());
        else if (strcmp(buf, "empty") == 0)
            printf("%d\n", s.empty());
        else if (strcmp(buf, "pop") == 0)
        {
            printf("%d\n", s.empty() ? -1 : s.top());
            if (!s.empty())
                s.pop();
        }
        else // push xxx
        {
            // 1. buf+5 ~ \0 까지가 숫자로 된 문자열
            // 2. 이걸 어떻게 바꿀까?
            // res = 0;
            // j = 5;
            // while (buf[j] != 0)
            // 	res = res * 10 + (buf[j++] - '0');
            scanf("%d", &res);
            s.push(res);
        }
    }
    return 0;
}