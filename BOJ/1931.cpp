#include <cstdio>
#include <vector>
#include <algorithm>
#include "../include/debugopen.hpp"

using namespace std;

bool cmp_1931(const pair<int, int> &a, pair<int, int> &b)
{
    if (a.second == b.second)
        return (a.second - a.first) > (b.second - b.first); // 짧은 순으로 오름차순
    // return a.first < b.first; // 값의 차이로 오름차순
    return a.second < b.second; // 둘째 수(종료 시각)로 오름차순
}

int main_1931()
{
    int N, i, a, b;
    READ_TXT("input.txt", "rt", stdin);
    scanf("%d", &N);
    pair<int, int> meets[N];
    for (i = 0; i < N; i++)
    {
        scanf("%d %d", &a, &b);
        meets[i].first = a;
        meets[i].second = b;
    }
    sort(&meets[0], &meets[N], cmp_1931);

    // pick
    int cnt = 1, last = meets[0].second;
    for (i = 1; i < N; i++)
    {
        if (last <= meets[i].first)
        {
            last = meets[i].second;
            cnt++;
        }
    }
    printf("%d\n", cnt);
    return 0;
}
