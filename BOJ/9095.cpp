#include <stdio.h>
#include "../include/debugopen.hpp"

using namespace std;

/*
    9095
    1, 2, 3 더하기

    1초, 512MB 제한

    정수 n이 주어졌을 때, n을 1, 2, 3의 합으로 나타내는 방법의 수를 구하는 프로그램을 작성하시오.
    0 < n < 11
*/
int main_9095()
{
    int i, currentSum, totalNumberOfTests;
    int cases[11];
    READ_TXT("input.txt", "rt", stdin);
    scanf("%d", &totalNumberOfTests);
    cases[1] = 1;
    cases[2] = 2;
    cases[3] = 4;
    for (i = 4; i < 11; i++)
    {
        cases[i] = cases[i - 1] + cases[i - 2] + cases[i - 3];
    }
    for (i = 0; i < totalNumberOfTests; i++)
    {
        scanf("%d", &currentSum);
        printf("%d\n", cases[currentSum]);
    }
    return 0;
}
