#include <stdio.h>
#include <stdlib.h>
#include "../include/debugopen.hpp"

using namespace std;

/*
    잃어버린 괄호 (Silver 2)
    1541

    양수, +, -, 괄호
    => 괄호가 제거됨
    => 괄호를 쳐서 식의 합을 최소로 만들기

    1. 값의 범위:
        - 값의 크기: 5자리 이하
        - 합의 최댓값: 5자리 * 10개 => 실질적 6자리인 99999를 10번 더하면 999,999.
            - int로 충분하다.

    2. Minus가 나오면 가장 큰 값을 갖기 위해서 뒤에서 등장하는 +를 다 묶는다.
        => Nope.
        => 그냥 - 뒤에 있는 + 끼리만 계속 묶으면 됨.
        => 중간에 -가 있으면 그냥 걔는 놔두면 됨.
        => 이것이 최적해가 맞음. Why?
            A - B + C ===> A - (B + C)
            A - B - B + 2B ===!===> A - (B - B + 2B)
                           =======> A - B - (B + 2B)

    3. 모든 Plus를 다 묶는 건 어떨까?
        => A + B + C - D + E + F ===> (A+B+C) - (D+E+F)
        => A - B - C - D - E + F ===> A-... - (E+F)

        괜찮은듯?
        그러면 -로 split하고, sum(before) - sum(after) 하면 될듯.

    4. split을 어떻게 구현할까?
        - string stream을 쓸 수 있다는데 이것의 시간 복잡도를 알 수 없는 상황에서 써도 되나?
        - 그렇지 않다면 쉽게 구현할 방법이 있나?
            - split은 string[]을 반환하기 때문에 메모리-비효율적일 수 있음

    5. 그냥 split을 안 쓰는 건?
        - One Path로 구현 가능할듯?
            - How?
                1. 숫자면 마크 후 진행 (시작, 끝 IDX 만)
                2. +, - 면
                    (1) 시작, 끝 idx에 대해 atoi 수행하고 임시 저장(tmpNum)
                    (2) 현재 기호가 + 면 nums[i] += tmpNum;
                    (3) 해당 기호가 - 면 i++;
                        - 처음부터 -가 나와도 nums[i] = 0 이므로 괜찮음.
                            - 처음부터 -가 나올 순 없다고 함(구분 때문에 양수 조건이 그래서 있는듯.)
                3. String이 끝나면
                    (1) sum = nums[0] - nums[i++] 하면 됨.

    ----틀렸습니다----
    Why?
        1. 반례를 찾자
            - 1-1-1-1 = -2 (v)
            - 1-2-3-4 =

        2. 모르겠다. 왜 틀렸는지 모르겠다.
            - 인터넷에서 검색했음
                - 0-100+50-100+50-100 => -400  | 내 코드 => -200
                - [0][150][150][100] => -400 나오는 게 맞는데? 왜 내 코드는 200을 출력할까?

            - 이젠 -400을 출력하는데도 빛의 속도로 틀렸다... Why?

*/
int main_1541()
{
    READ_TXT("input.txt", "rt", stdin);
    char str[51]; // 50자 제한 (+ NULL), 아 나 바본가?
    // 50자 제한 + 숫자당 1글자 할당 => 대충 30개의 숫자까진 나올 수 있음.
    // ex: 1-1-1-1-1-1-1-1-1-1-1-1-1
    int nums[30] = {0};
    int i, k = 0, numBegin = -1, sum = 0;
    scanf("%s", str);
    for (i = 0; str[i] != 0; i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            if (numBegin == -1)
                numBegin = i;
        }
        // <<참고로 아래 코드는 ? 연산자로 한 블록으로 만들 수 있음>>
        // numEnd는 필요 없다. atoi 스펙 상 숫자가 아닌 문자가 나오면 멈추기 때문이다.
        else if (str[i] == '-')
        {
            nums[k++] += atoi(str + numBegin); // 빼기는 나중에 수행한다.
            // 위에서 =이 아니라 +=이 되어야 하는 이유?
            //  -> -가 나오면 앞에껀 +였을 테니 이것을 덮어쓸 게 아니라 여기에 더해줘야 함.
            // 지금의 빼기는 단순히 앞의 덧셈과 이어질 뿐이므로, 현재 칸에 더해준다.
            numBegin = -1;
        }
        else if (str[i] == '+')
        {
            nums[k] += atoi(str + numBegin); // 더할 땐 그냥 더하면 된다.
            // 만약 더하기만 있는 경우, nums[0]에서 끝난다.
            numBegin = -1;
        }
    }
    // 마지막 숫자도 마지막 칸에 더해줘야 함
    // 마지막 기호가 + 였으면 더해주는 게 맞고,
    // 마지막 기호가 - 였어도 더해주는 게 맞음(물론 이 칸의 값=0이었겠지만 이건 상관 없음)
    // k++를 해야 하는 이유는 아래 루프가 i < k로 비교하기 때문임.
    // 내 생각엔 k++을 하지 말고, 루프에서 i <= k로 비교하는 게 맞을듯.
    // 왜냐면 k는 실제로 값이 들어가는 idx이기 때문임. 0부터 k가 시작하기 때문에 i <= k 가 맞음.
    nums[k] += atoi(str + numBegin);

    sum = nums[0];
    for (i = 1; i <= k; i++) // k개의 숫자가 배열에 저장되어 있음.
    {
        sum -= nums[i];
    }
    printf("%d\n", sum);
    return 0;
}
