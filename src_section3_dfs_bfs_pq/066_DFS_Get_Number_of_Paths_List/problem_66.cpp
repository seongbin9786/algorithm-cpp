#include "problem_66.hpp"

/*
유형: DFS
[풀이 전략]
방향 그래프를 Vector로 구현하는 내용을 그대로 따라치고 이해한다.
*/
using namespace std;
int cnt66 = 0, n66;
bool visited66[21] = {false};
vector<int> matrix66[21]; // 크기가 없는 vector를 30개 배열로 선언함.

void dfs66(int from)
{
    if (from == n66)
    {
        cnt66++;
        return;
    }
    // 인접 리스트이기 때문에 리스트가 끊기기 전까지 순회
    // Linked List면 ->link(); 와 같이 접근했겠지만
    // Vector 이므로 .size() 까지 그냥 for문으로 i++로 순회
    //
    for (int i = 0; i < (int)matrix66[from].size(); i++)
    {
        int to = matrix66[from][i];
        // 배열처럼 모두 순회하면서 matrix[from][i]=true일 때만
        // 접근하는 게 아니라, 여기 들어온 순간 이미 true 인거임 ㅇㅅㅇ
        if (!visited66[to])
        {
            visited66[to] = true;
            dfs66(to);
            visited66[to] = false;
        }
    }
}

void problem_66()
{
    int m, i, a, b;
    // 64랑 문제가 같아서 input64 활용
    READ_TXT("./resources/input64.txt", "rt", stdin);
    scanf("%d %d", &n66, &m);
    // push_back은 Dynamic Array로 사용한다는 것
    // push_back 덕분에 Linked List처럼 이어짐
    // Linked List나 Dynamic Array나 거기서 거기인듯 읽기만 하는 입장에선
    for (i = 1; i <= m; i++)
    {
        scanf("%d %d", &a, &b);
        matrix66[a].push_back(b);
    }
    visited66[1] = 1;
    dfs66(1);
    printf("%d\n", cnt66);
}
