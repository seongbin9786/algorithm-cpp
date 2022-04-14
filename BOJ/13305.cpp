#include <stdio.h>
#include <stdlib.h>
#include <tuple>
#include <algorithm>
#include "../include/debugopen.hpp"

using namespace std;

/*
    주유소 (Silver 4)
    13305

    상황:
        1. 수평선 위의 N개의 도시
        2. 도시 간 거리가 주어진다.
        3. 1km 이동에 1L를 사용한다.
        4. 이동에 기름을 사용하며, 기름통의 크기는 무한하다.
        5. 각 도시에서 주유할 수 있고, 주유소마다 가격은 다르다.

    입력:
        1. 각 도시의 기름 가격 - 가격 = 10억 이하, 도시의 개수 = 10만개 이하
        2. 각 도시간의 거리 - 거리는 10억 이하

    목표: 최좌측 도시에서 최우측 도시로 이동

    출력: 이동할 때 드는 최소 비용
    - 2초, 512MB

*/
/*
Solution

1. 모든 거리와 가격을 다 알고 있는 상태.

2. Idea:
    - 가장 싼 곳까지 도달한 후, 거기서 남은 거리만큼 충전한다.

    - 이걸 뒤에서부터 반복하면 될 것 같은데?
        (ex)

    [5]--2--[2]--3--[4]--1--[1]

    --> [5]로 2만큼 가고,
        [2]로 4만큼 가는 게 최적

        --> 10 + 8 = 18.

    => 그걸 어떻게 할 수 있을까?

        1. <가격, 순서>로 놓고 가격 -> 순서로 오름차순 정렬한다.
        2. (1)에서 최소 가격인 city를 cities 배열에 넣는다.
        3. 해당 도시의 위치 이전의 도시만 남긴다.
        4. 가장 첫 도시(idx=0)를 고를 때까지 (1~3)을 반복한다.
        5. cities 배열을 뒤집는다.
        6. 아래 코드처럼

            // 뽑힌 도시 순서의 index를 가져옴
            // 첫 도시의 위치(idx) = 0이다.
            for (i = 0; i < cities.length - 1; i++)
            {
                curCost = gasCost[i];
                // 도시 순서의 index 사이의 거리를 활용
                // ex: j=0; j < 10
                for (j = cities[i]; j < cities[i + 1]; j++)
                {
                    cost += distance[j] * curCost;
                }
            }

*/
/*
새로 배운 점:

저장할 변수의 타입이 long long이더라도, int * int의 결과는 int로 캐스팅되는 닷하다.
- (long long)으로 강제 캐스팅해주는 경우 정상적인 결과를 반환한다.

totalCost += (long long)distance[j] * curCost;
*/
/*
TODO:

지금 코드의 개선안이 여러 아이디어가 있었다.

1. pair보다 struct가 필드 이름을 통한 명료함이 압도적으로 좋다.

2. compare 함수에 익숙해져야 한다(암기라도 하자! 매우 자주 쓰일 것으로 예측된다).

3. (알고리즘 화이트보드 테스트를 할 때)
    - 수도 코드대로 코드가 그대로 구현되지 않는 게 당연한 것 같다.
    - 오히려 구체적인 조건문이나, 더 나은 조건문이 계속 도출되는 게 자연스러운 듯하다.

4. 배열 등 포인터의 경우, 덧셈 연산은 단위 크기만큼 자동으로 주소를 계산해준다.
    - 이는 단순 타입 뿐 아니라 pair<T, T>에도 적용이 된다.

5. C/C++에서 특정 코드가 실제로 잘 돌아가는지 확인하기 위해 Unit Test Library가 있으면 좋겠다.

*/
// 10억
const int COST_MAX_13305 = 1000000000;

bool compare_13305(pair<int, int> a, pair<int, int> b)
{
    if (a.first == b.first)
        return a.second < b.second; // 위치 오름차순
    return a.first < b.first;       // 비용 오름차순
}

int main_13305()
{
    READ_TXT("input.txt", "rt", stdin);
    int N, i, j, citiesSize = 0, curCost = 0;
    scanf("%d", &N);
    pair<int, int> costAndIdx[N];
    pair<int, int> cities[N];
    int distance[N];

    // 10억 여러개 하니 음수가 나온다.
    long long totalCost = 0L; // 10억 * 10만 까지는 커버할 수 있어야 하므로 long 활용.
    for (i = 0; i < N - 1; i++)
        scanf("%d", &distance[i]);
    for (i = 0; i < N; i++)
    {
        scanf("%d", &curCost);
        costAndIdx[i].first = curCost;
        costAndIdx[i].second = i;
    }

    sort()

        // do-while로 해야 함. 조건문이 cities인데, cities.length = 0으로 시작하기 때문.
        do
    {
        // 1. (비용, 거리) 순으로 오름차순 정렬
        sort(costAndIdx, costAndIdx + N, compare_13305);

        // 2. 선택된 도시만 cities 배열에 넣는다.
        cities[citiesSize++] = costAndIdx[0];

        // 3-1. 선택된 도시보다 idx가 뒤인 도시는 제거한다.
        for (i = 1; i < N; i++)
        {
            // 제거 대신 뽑힐 대상에서 제외
            if (costAndIdx[0].second <= costAndIdx[i].second)
                costAndIdx[i].first = COST_MAX_13305 + 1;
        }
        // 3-2. 넣은 도시도 제거
        costAndIdx[0].first = COST_MAX_13305 + 1;
    }
    while (cities[citiesSize - 1].second != 0)
        ; // 0번째 도시가 선택되는 경우 충분하다.

    reverse(cities, cities + citiesSize); // reverse ? 신기하다.

    // 첫 도시의 위치(idx) = 0이다.
    for (i = 0; i < citiesSize - 1; i++)
    {
        curCost = cities[i].first;
        // 도시 순서의 index 사이의 거리를 활용
        // ex: j=0; j < 10
        for (j = cities[i].second; j < cities[i + 1].second; j++)
            totalCost += (long long)distance[j] * curCost;
    }

    // cities는 충전할 도시만 고르기 때문에, 마지막 도시의 경우 끝 지점까지 따로 계산한다.
    // 만약 마지막 도시의 위치가 끝인 경우 for문은 돌지 않는다.
    curCost = cities[citiesSize - 1].first;
    for (i = cities[citiesSize - 1].second; i < N - 1; i++)
        totalCost += (long long)distance[i] * curCost;

    printf("%lld\n", totalCost);
    return 0;
}
