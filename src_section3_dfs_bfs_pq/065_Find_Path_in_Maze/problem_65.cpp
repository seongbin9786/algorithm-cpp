#include "problem_65.hpp"

/*
유형: DFS
[풀이 전략]

*/
int cnt65 = 0;

// Up Down Left Right
int py[] = {1, -1, 0, 0};
int px[] = {0, 0, -1, 1};
bool visited65[7][7] = {false};
int map[7][7]; // read bool not possible

void dfs65(int y, int x)
{
    // 어차피 마지막 위치이므로 어디 갈 곳이 없음
    if (x == 6 && y == 6)
    {
        cnt65++;
        debug("GOAL!\n");
    }
    for (int i = 0; i < 4; i++)
    {
        int ny = y + py[i];
        int nx = x + px[i];
        if (ny > 6 || nx > 6) // ArrayOutOfBounds
            continue;
        if (ny < 0 || nx < 0) // ArrayOutOfBounds
            continue;
        if (map[ny][nx] == 0 && !visited65[ny][nx]) // Can visit
        {
            debug("visit map[%d][%d] - from map[%d][%d]\n", ny, nx, y, x);
            visited65[ny][nx] = true;
            dfs65(ny, nx);
            visited65[ny][nx] = false;
            // 현재 뭔가 경로 중복 오류가 있는 것 같음.
            // DFS를 직접 다시 타봐야 이해를 할 수 있을듯?
        }
    }
}

void problem_65()
{
    int i, j;
    READ_TXT("./resources/input65.txt", "rt", stdin);
    // n차원 배열은 사실 1차원 배열이다.
    // 애초에 메모리 구조가 1차원이고 SW 적으로 따로 차원을 관리하진 않기 때문이다.
    // 뭐 좀 더 managed면 관리하겠지만
    // => 옛날엔 잘 썼던 거 같은데 하다가 예상대로 안 돼서 그냥 2차원으로 바꿈... C++ 컴파일러라서 그런가...
    for (i = 0; i < 7; i++)
        for (j = 0; j < 7; j++)
            scanf("%d", &map[i][j]);
    visited65[0][0] = true;
    dfs65(0, 0);
    printf("%d\n", cnt65);
}
