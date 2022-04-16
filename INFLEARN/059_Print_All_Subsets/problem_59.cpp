#include "problem_59.hpp"

/*
유형: 이진 트리, 재귀, DFS(그냥 재귀를 통한 완전 탐색 용도)
[풀이 전략]
- (ex) 3 -> [1 2 3], [1 2], [1 3], [1], [2 3], [2], [3]
- 모르겠어서 강의 봤음.
- 포화 이진 트리에서 정점이 아니라 간선을 주요하게 활용
- 문제의 출력 내용을 보고 이진 트리를 활용할 거라고 예상하기는 쉽지 않았을 것 같음. (그냥 응용 문제)
- 풀이 방법은 트리를 사용하는 게 아니어도 될 것 같은데 잘 모르겠다.

1. 몇 번의 시행 착오 끝에 코드는 강의와 동일한 것으로 재현해낼 수 있었다.
*/
void visit(int n, int *buf, int lvl)
{
    // 종료 조건
    if (lvl > n)
    {
        for (int i = 1; i <= n; i++)
            if (buf[i])
                printf("%d ", i);
        printf("\n"); // 이거 출력해도 출력 예제랑 동일함.
        return;
    }
    // 처음에는 buf[lvl] = left ? 1 : 0; 이거였는데,
    // 재귀여서 right 탐색 시에 buf[lvl] = 0 이 호출될 일이 없어서
    // 이진 트리 밖에 못 쓰겠지만 직접 1 할당하고 visit 하고 0 할당하고 visit 하는 형태로 결정함
    buf[lvl] = 1;
    visit(n, buf, lvl + 1); // left
    buf[lvl] = 0;
    visit(n, buf, lvl + 1); // right
}

void problem_59()
{
    int n;
    int buf[11] = {0};
    scanf("%d", &n);
    visit(n, buf, 1);
}
