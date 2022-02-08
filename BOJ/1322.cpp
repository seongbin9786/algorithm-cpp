#include <stdio.h>
#include "../include/debugopen.hpp"

using namespace std;

// 1 1000000000 는 2초안에 안 된다.
int main_1322()
{
    // 2^31 - 1 보다 클 수 있기 때문에 8bytes long을 사용한다.
    long X, K, Y = 0, i = 0, j = 0;
    READ_TXT("input.txt", "rt", stdin);
    scanf("%ld %ld", &X, &K);
    /*
    X는 원본 유지
    K는 점점 Y에 반영되면서 작아지게되고, K=0이 되면 종료되고 Y를 출력한다.
    */
    while ((K >> j) > 0) // K의 MSB를 넘기기 전까지 수행하면 될듯?
    {
        if (((X >> i) & 1) == 0) // X의 i번째 비트가 0이면
        {
            Y |= ((K >> j) & 1) << i; // Y의 i번째 비트에 K의 다음 비트를 삽입
            j++;                      // K의 다음 비트를 가리킴
        }
        i++; // X의 다음 비트를 가리킴
    }
    printf("%ld\n", Y);
    return 0;
}
