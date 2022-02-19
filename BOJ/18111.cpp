#include <stdio.h>
#include "../include/debugopen.hpp"

using namespace std;

/*
    마인크래프트 18111
    Silver 2

    '땅 고르기' = 세로 N, 가로 M 크기의 공간의 땅의 높이를 일정하게 바꾸는 작업

    이를 두 종류의 작업으로 수행해야 함:
        1. 좌표 (i, j)의 가장 위에 있는 블록을 제거하여 인벤토리에 넣기
        2. 인벤토리에서 블록 하나를 꺼내어 좌표 (i, j)의 가장 위에 있는 블록 위에 놓기

    1번 작업은 2초가 걸리며, 2번 작업은 1초가 걸린다.

    <조건>
    지하에 빈 공간은 존재하지 않음.
    시작할 때 주어진 B개의 블록만 사용 가능.
    땅의 높이는 0 <= h <= 256
    첫째 줄에 N, M, B가 주어진다. (1 ≤ M, N ≤ 500, 0 ≤ B ≤ 6.4 × 10^7)

    <출력>
    ‘땅 고르기’ 작업에 걸리는 최소 시간과 그 경우 땅의 높이를 출력

    --문제 풀이--
    1. 특정 문제라기 보단 <그냥 계산만 하면 될 것 같다.>
        - 브루트포스 문제
    2. 목표는 <최소 시간>에 하는 것이다.
    3. Case가 여러 가지로 나뉜다: (잘 모르겠다.)
        (1) 빼면 최소 비용인데 블록이 없는 경우
        (2) 빼면 최소 비용인데 블록이 있는 경우
        (3) 넣으면 최소 비용인데 블록이 없는 경우
        (4) 넣으면 최소 비용인데 블록이 있는 경우
    4. 애매한 경우: Min, Max가 아니라 중간 지점이면 어떡하지?
        => ex: 블록이 부족해서 쌓을 순 없는데, min까지 빼진 않아도 되는 경우.
        => Why? <제거> 작업은 2초가 걸리기 때문에, <제거>를 최소화해야 함.
        => 가장 높은 층을 선택하면 되지 않을까? Max ~ Min 까지해서 [필요로 하는 블록 수]와 [생길 블록 수]를 구하면 될듯.
        => 그 후 [블록이 부족하지 않은 경우]이면 해당 층을 선택하면 된다.

            <예시> ---- max=1이다. [0] -> [1]로 시도해본다: (가능하다.)
            3 4 99
            0 0 0 0
            0 0 0 0
            0 0 0 1
            (출력)
            2 0

            (입력)
            3 4 1
            64 64 64 64
            64 64 64 64
            64 64 64 63
            (출력)
            1 64

            (입력)
            3 4 0
            64 64 64 64
            64 64 64 64
            64 64 64 63
            (출력)
            22 63

        모든 원소를 순회 하면 O(N*M*B) = O(256 * 250,000) = O(64,000,000) 이고,
        단순한 배열 접근 + 뺄셈 연산이므로 충분히 1초안에 돈다.

        => Solution
            => [모든 층에 대해 매번 계산]을 해야 할 것 같다.
                => [가장 빨리 작업 가능] + [가장 높은 층] 으로 해야 함.
            => 즉 [Max, Min]의 층의 범위에 대해 Max 층부터 시작해서 차례로 내려가면서
                [필요로 하는 블록 수 - 생길 블록 수] >= 0 인 층에 대해 [작업 소요 시간]이 더 작을 때만 [최소 시간인 층]을 교체하면 된다.

*/
int main_18111()
{
    READ_TXT("input.txt", "rt", stdin);
    int map[250000] = {0}; // 25만
    int N, M, B, i, minCost, answer, tallest = 0, shortest = 500;
    int curB, curCost, curHeight, curBlockMinusCurHeight;
    scanf("%d %d %d", &N, &M, &B);
    for (i = 0; i < N * M; i++)
    {
        scanf("%d", &map[i]);
        if (map[i] > tallest)
            tallest = map[i];
        if (map[i] < shortest)
            shortest = map[i];
    }

    minCost = N * M * 256; // 발생할 수 있는 최악의 값으로 초기화해야 한다.
    answer = shortest;     // 발생할 수 있는 최악의 값으로 초기화해야 한다.

    for (curHeight = tallest; curHeight >= shortest; curHeight--)
    {
        // 1. 이번 층에서 쓸 수 있는 블럭 개수 계산
        // 2. 이번 층에서 발생하는 비용 계산
        curB = B;
        curCost = 0;
        for (i = 0; i < N * M; i++)
        {
            curBlockMinusCurHeight = map[i] - curHeight;
            curB += curBlockMinusCurHeight;
            if (curBlockMinusCurHeight > 0)
                curCost += curBlockMinusCurHeight * 2;
            else if (curBlockMinusCurHeight < 0)
                curCost += (curBlockMinusCurHeight * -1); // 절댓값
        }

        // 부족하면 미사용
        if (curB < 0)
            continue;

        // 최소값 갱신 시 층도 갱신
        if (curCost < minCost)
        {
            minCost = curCost;
            answer = curHeight;
        }
    }
    printf("%d %d\n", minCost, answer);
    return 0;
}
