#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include "../include/debugopen.hpp"

using namespace std;

/*
    수 찾기 (Silver 4)
    1920

    입력:
        - 모든 정수는 int 범위
        - N개의 정수 A[i], 1 <= i <= N
        - 다음 줄에 N개의 정수
        - 다음 줄에 M개의 정수
        - N, M <= 100,000

    목표: M[j] = A[i]가 있는지 확인 (있으면 1, 없으면 0)

    출력:
        - M개의 정수에 대한 출력을 한 번에 한 줄로.

*/
/*
    99%에서 틀렸습니다.
    Why?

    벡터의 크기를 미리 할당하고 입력을 받는 방법.

    1. init size 명시
        - vector<int>(N); 으로 초기화하면 N개의 0이 포함된 상태로 시작한다.
        - 대신 scanf("%d", &a[i]); 으로 입력받아서 '덮어씌우기'를 해야한다.
            - 포인터 변수인 경우, &v->at(i)이 &v[i]와 동등하다.

    2. init size 없이 reserve하기
        - v.reserve(N); 수행
        - v.push_back(val); 수행
*/
vector<int> *v_1920;

bool compare_1920(int a, int b)
{
    return a < b;
}

int main_1920()
{
    READ_TXT("input.txt", "rt", stdin);
    int N, M, i, target;
    scanf("%d", &N);
    // 벡터 구성
    v_1920 = new vector<int>(N);
    // v->reserve(N);
    for (i = 0; i < N; i++)
        scanf("%d", &v_1920->at(i));
    sort(v_1920->begin(), v_1920->end(), compare_1920);

    // 풀이
    scanf("%d", &M);
    for (i = 0; i < M; i++)
    {
        scanf("%d", &target);
        printf("%d\n", binary_search(v_1920->begin(), v_1920->end(), target, compare_1920) ? 1 : 0);
    }
    return 0;
}
