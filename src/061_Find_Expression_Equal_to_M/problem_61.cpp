#include "problem_61.hpp"

/*
유형: DFS [?]
[풀이 전략]

1. 오름차순 정렬 후 삼진 트리로 해결하기
=> (+a[i], +0, -a[i]) 로 정렬된 원소에 대해 브루트포스 수행
=> O(3^n) 이지만 n<=10 이라서 그냥 해 봤음
=> TC 4,5: Wrong Answer
=> 이 답안이 느리긴 해도 모든 경우의 수를 건드리는거 아닌가? 왜 틀리지?
=> TC 4, 5의 답보다 좀 적게 나온다... 일단 I/O 문제는 아니고 로직 문제인듯
*/
int n, m;
int arr[11] = {0};
int cnt = 0;

void go(int lvl, int sum)
{
    if (lvl > n) // lvl=11 으로 진입할 때가 돼야 sum+arr[10] (n=10)이 되기 때문.
        return;
    if (sum == m) // 완성된 경로이므로 여기에 +,-를 더 해도 되나? 모르겠다 또..
    {
        cnt++;
        return;
    }
    lvl++;
    // 아래의 순서가 중요하진 않다.
    go(lvl, sum + arr[lvl]); // +
    go(lvl, sum);            // +0
    go(lvl, sum - arr[lvl]); // -
}

void problem_61()
{
    int i;
    READ_TXT("./resources/input61.txt", "rt", stdin);
    scanf("%d %d", &n, &m);
    for (i = 1; i <= n; i++)
        scanf("%d", arr + i);
    std::sort(arr + 1, arr + n + 1); // a[1] ~ a[n] 까지 오름차순 정렬 (우측 idx는 +1 해줘야 한다고 함. ㅇㅅㅇ)
    go(0, 0);
    printf("%d\n", cnt == 0 ? -1 : cnt); // -1을 출력하는 TC는 없었던듯
}
