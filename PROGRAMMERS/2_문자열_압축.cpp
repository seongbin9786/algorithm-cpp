#include <string>
#include <vector>
#include <cmath>
#include <cstdio>

using namespace std;

int solution(string s)
{
    int cuttingWidth, i, cnt, len, minLen = 1001; // maxLen=1000
    string prev, cur;

    // 문자열의 길이의 절반까지만 키운다.
    for (cuttingWidth = 1; cuttingWidth <= s.size() / 2; cuttingWidth++)
    {
        cnt = 1;
        len = 0;
        prev = s.substr(0, cuttingWidth);
        // 문자열을 cuttingWidth 만큼 순회한다.
        for (i = cuttingWidth; i < s.size(); i += cuttingWidth)
        {
            cur = s.substr(i, cuttingWidth);
            if (prev == cur)
            {
                cnt++;
            }
            else
            {
                if (cnt != 1) // 연속된 경우에만 앞에 숫자 추가
                {
                    len += trunc(log10(cnt)) + 1; // 정수의 자릿수 계산
                }
                len += cuttingWidth;
                cnt = 1;
            }
            prev = cur;
        }
        // 루프가 끝났을 때 마지막 조각(cur)을 반영해줘야 한다.
        // (ex) aa bb a ccc에서 마지막 c가 반영되지 않는다.
        // ---> 여기서 c를 반영해줘야 3c가 들어가고 끝난다.
        if (cnt != 1)
        {
            len += trunc(log10(cnt)) + 1;
        }
        len += cur.size();

        if (len < minLen)
            minLen = len;
    }

    return s.size() == 1 ? 1 : minLen;
}