#include <iostream>

#include "../include/debugopen.hpp"

using namespace std;

/*
[Gold 4]
알파벳

세로 R칸, 가로 C칸으로 된 표 모양의 보드가 있다.
- brd[R+1][C+1];
- (1,1)에서 시작
- 칸마다 알파벳 있음
- 상하좌우 탐색

완전 탐색 + DFS + 백트래킹
=> DFS 중 방문 대상이 visited_alpha 이면 방문하지 않는다. (이럼 될 거 같은데요?)

Q. 언제가 경로의 끝인지 판단할 수 있을까?
- 아무 곳도 갈 수 없을 때 ㅇㅇ
- DFS 니까 depth를 재귀로 전송하자.

*/

int R, C;
int max_depth = 0;
char buf[21] = {0};
char brd[21][21]; // 초기화 할 필요 없음!
bool visited[21][21] = {0};
bool visited_alpha[26] = {0}; //0~25 alphabet

//동서남북
const int pos_x[] = {1, -1, 0, 0};
const int pos_y[] = {0, 0, -1, 1};

void dfs(int y, int x, int depth)
{
    int i, ny, nx;
    char na;

    // cout << "visiting: [" << y << "][" << x << "] (" << a << ")\n";

    // 항상 depth 갱신해도 됨. 가장 멀리가는 게 중요
    max_depth = max_depth < depth ? depth : max_depth;

    for (i = 0; i < 4; i++)
    {
        ny = y + pos_y[i];
        nx = x + pos_x[i];
        na = brd[ny][nx];

        if (nx < 1 || ny < 1 || nx > C || ny > R)
            continue;
        if (visited_alpha[na - 'A'])
            continue;
        if (visited[ny][nx])
            continue;

        // 백트래킹
        visited_alpha[na - 'A'] = true;
        visited[y][x] = true;
        dfs(ny, nx, depth + 1);
        visited_alpha[na - 'A'] = false;
        visited[y][x] = false;
    }
}

int main()
{
    int i, j;
    READ_TXT("./input.txt", "rt", stdin);
    cin >> R >> C; // 가로 C칸, 세로 R칸 => CxR 행렬은 맞음 (즉, 2x3 행렬)

    // 행렬 초기화는 정상으로 해야함. 탐색만 [y][x]로 진행함
    for (i = 1; i <= R; i++) // 행의 개수 (세로칸)
    {
        // 행이 입력된다.
        cin >> buf;
        for (j = 1; j <= C; j++) //열의 개수 (가로칸)
            brd[i][j] = buf[j - 1];
    }
    visited_alpha[brd[1][1] - 'A'] = true;
    visited[1][1] = true;
    dfs(1, 1, 1);
    cout << max_depth << "\n";
}
