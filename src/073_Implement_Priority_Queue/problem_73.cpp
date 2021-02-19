#include "problem_73.hpp"

/*
유형: PQ
[풀이 전략]

1. PQ를 초기화한다.
2. 데이터 개수가 미리 주어지지 않기 때문에 그냥 for문으로 수행한다.

---
Min/Max 전환법:
[1] 생성자 활용: priority_queue<typename, container<typename>, sortFn); 
- container가 front, push_back, pop_back 인터페이스가 있어야 함. ( @c, @e 의 기능은 잘 모르겠음. )

[2] 절댓값 활용: 원래 값을 음수로 만든 후 빼낼 때 다시 양수로 만든다. 기본적으로 min heap이므로 
가장 작은 값이 root로 오므로 이 값을 양수로 만들면 max heap이 된다. (좀 신기하지만 권장되는 방법은 아닌듯.. 굳이 stl이 있는데.)
=> 대신 sort 함수를 지원할 바에 이렇게 하는 게 훨씬 쉬울듯
*/
using namespace std;

void problem_73()
{
    int next;
    priority_queue<int, vector<int>, greater<int>> pq;
    READ_TXT("./resources/input73.txt", "rt", stdin);
    while (true)
    {
        scanf("%d", &next);
        if (next == -1)
            break;
        if (next == 0)
            if (pq.empty())
                printf("-1\n");
            else
            {
                printf("%d\n", -pq.top());
                pq.pop();
            }
        else
            pq.push(-next);
    }
}
