#include "problem_64.hpp"

/*
유형: DFS
[풀이 전략]
1에서 출발해서 5에서 끝나는 DFS
일반적인 DFS는 하나의 경로만 반환하고 말지만 계속 반복시키면서
중복을 피하기 위해 
visited[to]=true;
dfs(to);
visited[to]=false; 

이런 로직에 당도했는데 이게 well-knwon 인지 잘 모르겠다.
일단 없으면 안 되는건 확인했음.

정답을 보자
---
오 놀랍다.. 내거랑 똑같네; 굳굳
*/
bool matrix[21][21] = {false}; // Space: O(N^2) (N <= 20)
bool visited[21] = {false};
// 전역변수 충돌 .. 하..ㅋㅋ
// 전역 변수를 안 쓸 수도 없고. 어떻게 해야 되지? class 써야 되나?
int _cnt = 0;
int _n;

void dfs64(int from)
{
    if (from == _n)
    {
        _cnt++;
        return;
    }
    for (int to = 1; to <= _n; to++)
        // 이렇게 hack 느낌으로 true->false 만 안 해줘도 정답처럼 보일텐데 아쉽다.
        if (matrix[from][to] && !visited[to])
        {
            visited[to] = true;
            dfs64(to);
            visited[to] = false;
        }
}

void problem_64()
{
    int i, m, x, y;
    READ_TXT("./resources/input64.txt", "rt", stdin);
    scanf("%d %d", &_n, &m);
    for (i = 0; i < m; i++)
    {
        scanf("%d %d", &x, &y);
        matrix[x][y] = true;
    }
    // 일단 입력은 OK
    visited[1] = true;
    dfs64(1);
    printf("%d\n", _cnt);
}
