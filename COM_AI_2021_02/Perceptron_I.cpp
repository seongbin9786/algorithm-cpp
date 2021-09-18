#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/debugopen.hpp"

/*
    Perceptron I

    [goal]
    1. Implement AND Gate for n*1 input (input data are binary = 0, 1)
      ===> 임의의 w[n]에 대해 AND gate 역할을 수행한다.

    2. Test it with Random Weights n*1
      ===> AND Gate의 결과와 실제 테스트값을 비교해 성공/실패를 판단한다.
      ===> 성공할 때까지 계속 진행한다.

    [requirements]
    1. weight 값을 random으로 초기화
    2. sum += w[i]*x[i] 을 n번 체크함.
       ===> AND Gate의 결과인 [0...0,1]과 일치하면 성공
       ===> [0...0,1]과 일치하지 않는 경우 재시도
    3. 어떤 weight를 주어야 loop에서 빨리 나올 수 있을까?
       ===> 랜덤 가중치에 theta도 포함시킨다. 그리고 x0=-1의 가중치로 입력을 준다.
       ===> 랜덤값을 내림차순으로 정렬해 w0, w1, w2, ... wn 으로 할당한다.
        ===> 이렇게 되면 w0 < sum(w1, ... wn) 인 경우 AND Gate가 성립한다.
       ===> Overflow를 방지하지 위해, 가중치의 최댓값을 INT_MAX / (n+1)으로 놓는다. (n개의 입력을 고려)
       ===> sum >= 0이면 AND가 성립하는 것으로 한다.

    [prototype]
    inputLength = n; // 임의의 n
*/

bool failed = true; // do-while 때문에 true로 초기화

// 중복순열 코드 (중복순열을 이해하는 게 먼저인 거 같은데 ㅋㅋ)
// https://devyul.tistory.com/
void ANDGate(int n, int *wArr, int *xArr, int bucketSize, int k)
{
    int i, lastIndex, smallest, item;
    // 모두 뽑은 경우
    if (k == 0)
    {
        int sum = 0;
        bool isAllInputIsOne = true;
        bool correct = false;
        for (i = 0; i < bucketSize; i++)
        {
            if (xArr[i] == 0)
                isAllInputIsOne = false;
            printf("x%d: %d, ", i, xArr[i]);
            sum += wArr[i] * xArr[i];
        }
        sum += wArr[i] * -1;
        if ((sum >= 0 && isAllInputIsOne) || (sum < 0 && !isAllInputIsOne))
            correct = true;
        printf("sum=%d, %s\n", sum, correct ? "OK" : "FAIL");
        if (!correct)
            failed = true;
        return;
    }

    // 가장 최근에 뽑힌 수가 저장된 위치 index
    lastIndex = bucketSize - k - 1;
    // 매번 전체 아이템에서 뽑기때문에 0.
    // 항상 x1에서 시작해야하므로 1. (이거 실패했음;;)
    smallest = 0;
    for (item = smallest; item < n; item++)
    {
        // smallest에서 n-1까지의 수에서 뽑는 경우
        xArr[lastIndex + 1] = item;
        // (재귀) 1개를 뽑았으므로 k-1개를 뽑는다
        ANDGate(n, wArr, xArr, bucketSize, k - 1);
    }
}

int static ASC(const void *first, const void *second)
{
    if (*(int *)first > *(int *)second)
        return 1;
    else if (*(int *)first < *(int *)second)
        return -1;
    else
        return 0;
}

int main()
{
    int i, sum, inputLen, WEIGHT_MAX, failCnt = 0;
    srand(time(NULL));
    READ_TXT("./input.txt", "rt", stdin);
    scanf("%d", &inputLen);

    int wArr[inputLen + 1] = {0}; // wn도 필요하므로.
    int xArr[inputLen] = {0};

    failCnt = 0;
    do
    {
        // STEP 1: Weight 초기화
        // weight 생성
        WEIGHT_MAX = RAND_MAX / (inputLen + 2);
        for (i = 0; i < inputLen + 1; i++)
            wArr[i] = rand() % WEIGHT_MAX;
        // weight 정렬
        qsort(wArr, inputLen + 1, sizeof(int), ASC);
        for (i = 0; i < inputLen + 1; i++)
            printf("w[%d] = %d\n", i, wArr[i]);

        // STEP 2: 테스트 진행
        failed = false;
        ANDGate(2, wArr, xArr, inputLen, inputLen);
        if (failed)
            failCnt++;
    } while (failed);
    printf("failCnt: %d\n", failCnt);

    return 0;
}

/*
    어떻게 x[n]의 0,1 조합을 모두 출력해볼 수 있지?
    x개수=0 (4C0 ...?)
    0 0 0 0

    x개수=1 (4C1 ...?)
    1 0 0 0
    0 1 0 0
    0 0 1 0
    0 0 0 1

    x개수=2
    1 1 0 0
    1 0 1 0
    1 0 0 1
    0 1 1 0
    0 1 0 1
    0 0 1 1
*/