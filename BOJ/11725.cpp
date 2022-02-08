#include <cstdio>
#include <vector>
#include <queue>
#include "../include/debugopen.hpp"

using namespace std;

queue<int> Q_11725;
vector<int> bidirectionalGraph_11725(100001);
int parents_11725[100001] = {0};
bool visited_11725[100001] = {false};

void BFS()
{
    int i, childId, parentId;
    vector<int> from;
    while (!Q_11725.empty())
    {
        parentId = Q_11725.front();
        visited_11725[parentId] = true;
        Q_11725.pop();
        from = bidirectionalGraph_11725[parentId];
        for (i = 0; i < from.size(); i++)
        {
            childId = from[i];
            if (visited_11725[childId])
                continue;
            parents_11725[childId] = parentId;
            Q_11725.push(childId);
        }
    }
}

int main_11725()
{
    READ_TXT("./input.txt", "rt", stdin);
    int N, i, a, b;
    scanf("%d", &N);
    for (i = 0; i < N - 1; i++) // 무조건 부모가 있으니까 입력도 N-1개가 무조건 들어옴
    {
        scanf("%d %d", &a, &b);
        bidirectionalGraph_11725[a].push_back(b);
        bidirectionalGraph_11725[b].push_back(a);
    }
    Q_11725.push(1);
    BFS();
    for (i = 2; i <= N; i++) // 전체 노드 범위: 1 <= nodeId <= N
        printf("%d\n", parents_11725[i]);
    return 0;
}
