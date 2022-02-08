#include <iostream>
#include <stack>
#include "../include/debugopen.hpp"

using namespace std;

/*
    9663
    [Gold 4] N-Queen

    N-Queen 문제는 크기가 N × N인 체스판 위에 퀸 N개를 서로 공격할 수 없게 놓는 문제이다.
    N이 주어졌을 때, 퀸을 놓는 방법의 수를 구하는 프로그램을 작성하시오. (N < 15)

    [sol]
    ( ex: N=4, 행렬 편의상 1-index )
    1. 어떻게 백트래킹으로 풀 수 있을까? 일단 N이 작으므로 백트래킹과 같은 완전 탐색으로 풀 수 있다.
    2. N*N 격자판을 만들고, 위부터 아래로 하나씩 배치하면서 둘 수 있는 칸을 지워버리면 되지 않을까?
        - 예를 들어, [1,1]에 놓으면, 1행과 1열은 둘 수 없고, 대각선도 처리해줘야 한다.(how?)
            - 대각선 처리 방법:
                - [i, j]를 둘 모두 1씩 증가시켜 하나가 N에 도달할 때까지
                    ====> 이건 0부터 시작할 필요가 없다.
                          WHY? 이미 지나온 행들은 어차피 못 두기 때문에? YES
                            ===> 반례는 없을까?
                - 둘 모두 1씩 빼서 하나가 1에 도달할 때까지 마킹
                - [i+1, j-1]을 수행해 i 혹은 j가 1 혹은 N에 도달할 때까지 마킹
                - [i-1, j+1]을 ~ (동일)
        - 백트래킹으로 계속 1행을 탐색하지만 놓을 수 있는 자리는 없으므로 2행으로 이동한다.
        - [2,1],[2,2]은 못 놓는데, [2,3]는 놓을 수 있으니 놓는다. 이제 2행과 3열에는 놓을 수 없고, 대각선도 처리해줘야 한다.
        - 이제 3행으로 이동한다. 놓을 수 있는 곳이 없다 (그려보면 안다).
        - 4행으로 간다. [4,2]에 놓을 수 있다. 마찬가지로 4행, 2열을 지우고 대각선도 처리한다.
        - 4행을 탐색한다. 놓을 수 있는 곳이 없다. 종료한다.

    2-1. 이제 [1,2]에 놓고 시작한다. [1,3],[1,4]에 놓고 시작한다.[2,1]에 놓고 시작한다.
        - 이런 식으로 하는 건 백트래킹이 아니라 진짜 완전 탐색인데, 이렇게는 안 될 것 같다.
        - 백트래킹을 활용하려면 역시 쌓인 상태를 활용해야 하고, 끝에서부터 돌아와야 일종의
          캐시 형태로 효율적으로 계산량을 줄일 수 있다.
        - how?
            일반적인 백트래킹 논리로 풀 수 있을 것 같다.
            (1). queen을 놓는다. 이 때 for 문으로 각 행의 열(N) 만큼 순회한다.
                - 이렇게 되면 각 백트래킹 함수는 하나의 행에 대한 단위가 된다.
                - 한 행에 대해 착점하고, 돌아오면 그 다음 칸에 착점해 완전 탐색을 하는 역할이다.
            (2). 못 두는 자리를 지정한다.
            (3). 다음 백트래킹을 호출한다. - 이 경우 아마 다음 행으로 이동하는 듯하다.
                - 무조건 다음 행으로 이동 해야 되나? yes 왜냐면 queen 이니까.
                - 그렇게 되면 코드가 일반적인 백트래킹이 된다.
            (4). 못 두는 자리를 해제한다.
            (5). queen을 뺀다.

    2-2. 언제 경우의 수를 세는 게 좋을까?
        - N개가 착점 됐을 때 세면 된다.

    3. 격자판에서 마킹하는 방법을 바꿔야 한다.
        - 낮은 N에서 해보니까 숫자가 틀리거나, 안 돼야 하는데 되는 경우가 있었는데,
          마킹이 중첩될 때 이를 구분할 수 있어야 한다.
          쉬운 방법은 매 백트래킹 호출 때마다 새로운 map을 쓰는 방법이 있다.
          stack<pair<int, int>>에 지운 슬롯을 저장하는 방법도 있다.
          그러면 stack이 빌 때까지 쭉 복구하면 된다.
            - 안 된다. 이전 백트래킹 함수에서도 push 했을 것이기 때문.
                - 이 문제는 해결이 안 되네.
                    - 겹쳤던 슬롯이든, 마킹한 슬롯이든, 이전 함수에서 push한 게 잔류한다.
                    - 따라서 구분자 역할을 수행할 item을 써야 된다.

            - 차자리 지금처럼 복구한 후, '겹쳤던 슬롯'만 기록한다면
            - 해당 슬롯은 다시 못 쓰는 칸으로 지정하면 된다.

          스택이 나을듯. 매번 새 map을 어떻게 copy할지도 모르겠고.
*/

int N_9663;
bool map_9663[16][16] = {{false}}; // 15x15를 1-index로 지원하기 위함. 이렇게 초기화 하면 all-false 이다. (0으로 해도 all-false일까?)
int total_9663 = 0;
int cnt_9663 = 0;
stack<pair<int, int>> prevMarked_9663; // 스택 ㅎ... 시간 초과 날 것 같긴 하다. 10초나 주는데 넘칠까? 다 짜고 나서 테스트해보면 되지.

void switchSingleSlot(int r, int c, bool marking)
{
    // 이미 마킹돼있는 경우 스택에 넣는다. 지금 마킹하는 것들을 뺐을 때도 보존돼야 하는 칸이므로
    if (marking && map_9663[r][c])
    {
        cout << "PUSH [" << r << "," << c << "]\n";
        prevMarked_9663.push(make_pair(r, c));
    }
    map_9663[r][c] = marking;
}

void switchAvailableSlots(int r, int c, bool marking)
{
    // cnt도 여기서 증감
    if (marking)
    {
        cout << "TRY - [" << r << "," << c << "]\n";
        cnt_9663++;
    }
    else
    {
        cout << "FAIL - [" << r << "," << c << "] cnt:[" << cnt_9663 << "]\n";
        cnt_9663--;
    }

    // 나를 넣기
    switchSingleSlot(r, c, marking);

    int i;
    // 같은 행
    for (i = 1; i <= N_9663; i++)
        if (i != c)
            switchSingleSlot(r, i, marking);

    // 같은 열
    for (i = 1; i <= N_9663; i++)
        if (i != r)
            switchSingleSlot(i, c, marking);

    // ++
    for (i = 1; i <= N_9663; i++)
    {
        if (r + i > N_9663 || c + i > N_9663)
            break;
        switchSingleSlot(r + i, c + i, marking);
    }

    // --
    for (i = 1; i <= N_9663; i++)
    {
        if (r - i < 1 || c - i < 1)
            break;
        switchSingleSlot(r - i, c - i, marking);
    }

    // +-
    for (i = 1; i <= N_9663; i++)
    {
        if (r + i > N_9663 || c - i < 1)
            break;
        switchSingleSlot(r + i, c - i, marking);
    }

    // -+
    for (i = 1; i <= N_9663; i++)
    {
        if (r - i < 1 || c + i > N_9663)
            break;
        switchSingleSlot(r - i, c + i, marking);
    }

    if (marking)
    {
        prevMarked_9663.push(make_pair(-1, -1)); // 이번 마킹 데이터의 끝을 알리는 (-1, -1) 쌍
        cout << "------\n";
    }
    else
    {
        // 마킹을 해제할 때 기존에 마크됐던 건 해제했으면 안되므로 복구해줌
        prevMarked_9663.pop(); // (-1,-1)은 무조건 있음 (-1,-1)을 제거
        pair<int, int> cur;
        while (!prevMarked_9663.empty()) // empty를 만나는 경우: 1행의 착점을 바꿀 때
        {
            cur = prevMarked_9663.top();
            if (cur.first == -1 && cur.second == -1) // 새로운 (-1, -1)이 나오면 끝!
                return;
            map_9663[cur.first][cur.second] = true; // 다시 마킹해줌
            cout << "POP [" << cur.first << "," << cur.second << "]\n";
            prevMarked_9663.pop();
        }
    }
}

void tryPuttingQueen(int r)
{
    bool visitedNextRow = false;
    for (int c = 1; c <= N_9663; c++)
    {
        /*
        (1). queen을 놓는다. 이 때 for 문으로 각 행의 열(N) 만큼 순회한다.
            - 이렇게 되면 각 백트래킹 함수는 하나의 행에 대한 단위가 된다.
            - 한 행에 대해 착점하고, 돌아오면 그 다음 칸에 착점해 완전 탐색을 하는 역할이다.
        (2). 못 두는 자리를 지정한다.
        (3). 다음 백트래킹을 호출한다.
            - 이 경우 아마 다음 행으로 이동하는 듯하다.
            - 무조건 다음 행으로 이동 해야 되나? yes 왜냐면 queen 이니까.
            - 그렇게 되면 코드가 일반적인 백트래킹이 된다.
        (4). 못 두는 자리를 해제한다.
        (5). queen을 뺀다.
        */

        // 1. 놓을 수 없으면 Pass. 착점은 아래 코드로도 적용되므로 둘 수 있는지 체크만 하면 됨.
        // 1-1. 놓을 수 없는 행이 중간에 있으면 어떻게 함?
        //      - 이건 분명히 N이 조금만 커져도 자주 나온다. 아래와 같은 조건문으론 제대로 셀 수 없다.
        // 모든 for문을 돌았을 때에도 체크를 해줘야 할까?
        // 그러면 왔다 갔다 하면서 엄청 왔다 갔다 할 것 같은데? 어쩔 수 없음. 되긴 할듯.
        if (map_9663[r][c])
        {
            // cout << "XXX [" << r << "," << c << "]\n";
            continue;
        }

        // 마지막 착점이므로 현재 백트래킹은 뒤로 간다?
        if (cnt_9663 == N_9663)
        {
            total_9663++;
            return;
        }

        // 여기까지 왔는데 포인트 못 모았으면 return 해야됨
        // 어차피 slot 봉쇄하면 다음 꺼 못 놓고 뒤로가게 돼있음.
        // (4,2)에서 여기 왔는데,
        if (r == N_9663)
            return;

        // 2. 못 두는 자리: 같은 행, 같은 열, 대각선 4종류 처리
        switchAvailableSlots(r, c, true);

        // 3. 다음 백트래킹 호출
        // 무조건 마지막 행에 착점이 가능하다면, 착점할 수 있을 때만 total++ 하면 된다.
        tryPuttingQueen(r + 1);

        // 4. 못 두는 자리 해제
        // 여기서 (4,2)는 빠지면 안 되는데 그쵸?
        switchAvailableSlots(r, c, false);
        // 놓을 수 있음
        visitedNextRow = true;
    }
    if (r < N_9663 && !visitedNextRow) // 마지막 행이 아니고, 한 행이 통채로 못 놓는 곳일 때 이동시켜 줘야 함.
    {
        // 마지막 착점이므로 현재 백트래킹은 뒤로 간다?
        if (cnt_9663 == N_9663)
        {
            total_9663++;
            return;
        }

        // 3. 다음 백트래킹 호출
        tryPuttingQueen(r + 1);
    }
}

int main_nqeen()
{
    // 초기화
    READ_TXT("./input.txt", "rt", stdin);
    cin >> N_9663;
    tryPuttingQueen(1);
    cout << total_9663 << "\n";
    return 0;
}
