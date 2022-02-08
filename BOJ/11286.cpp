#include <iostream>
#include <cstdio>
#include <queue>
#include "../include/debugopen.hpp"

using namespace std;

struct cmp_11286
{
    // false: 1번째 인자가 우선 순위 높음
    // true: 2번째 인자가 우선 순위 높음
    // 기본 Max Heap이므로 우선 순위가 높은 순으로 정렬 될 것
    bool operator()(pair<int, int> a, pair<int, int> b)
    {
        if (a.first == b.first)
            return a.second > b.second; // a가 작으면 false (=> Min Heap)
        return a.first > b.first;       // a가 작으면 false (=> Min Heap)
    }
};

int main_11286()
{
    READ_TXT("input.txt", "rt", stdin);

    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp_11286> pq;

    int i, input, N;
    cin >> N;
    for (i = 0; i < N; i++)
    {
        cin >> input;
        if (input == 0) // 0일땐 원소 출력
        {
            if (pq.empty()) // 비어있을 땐 0 출력
            {
                cout << "0\n";
                continue;
            }
            cout << pq.top().second << "\n";
            pq.pop();
        }
        else // 0이 아닐 땐 원소 입력
        {
            pq.push(make_pair(abs(input), input));
        }
    }
    return 0;
}
