#include "problem_75.hpp"

/*
유형: PQ
[풀이 전략]

*/
using namespace std;

struct Schedule75
{
    int pay, due;

    Schedule75(int pay, int due)
    {
        // this가 포인터로 제공된다는 점이 좀 충격적
        this->pay = pay;
        this->due = due;
    }

    // 오름차순 기준으로 a(this)<b 이면 true otherwise false
    // 그럼 내림차순으로 하려면 return a.x > b.x 겠네
    // [1] 포인터나 레퍼런스나 상관 없는걸까?
    // [2] 꼭 const를 붙여야 할까? 뭐 비교 연산자라서 내용을 바꿀 일은 없겠지만...
    // 참고로 두 번째 const는 상수 멤버 함수라는 뜻으로 멤버 변수를 변경하지 않는 함수임을 의미
    // (음... 함수란 내부 구현을 숨겨야 할진데 이런건 왜 만들었을까...)
    bool operator<(const Schedule75 &b) const
    {
        // 1. due는 오름차순 정렬해야 (즉 a<b 이면 true)
        if (due != b.due)
            return due > b.due; // 뭔 순서인지 모르겠음 ㅎ..
        // 2. pay는 내림차순 정렬해야 (즉 a<b 이면 false)
        return pay < b.pay;
    }
};

void problem_75()
{
    int i, n, pay, due, sum = 0, date = 0;
    priority_queue<Schedule75, vector<Schedule75>> pq; // less가 내림차순인가? greater로 하니 operator> 를 요구하길래 버렸음..
    READ_TXT("./resources/input75.txt", "rt", stdin);
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d %d", &pay, &due);
        pq.push(Schedule75(pay, due));
    }
    while (!pq.empty())
    {
        Schedule75 now = pq.top();
        pq.pop();
        // 아직 시간이 있는 경우
        if (now.due > date)
        {
            sum += now.pay;
            date++;
        }
    }
    printf("%d\n", sum);
}
