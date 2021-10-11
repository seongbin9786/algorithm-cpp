#include <iostream>
#include <string>
#include <map>
#include "../include/debugopen.hpp"

using namespace std;

/*
    [Silver 1] 추월

    터널 전/후의 순위표를 보고 추월한 차들을 출력한다.
*/
int main()
{
    READ_TXT("./input.txt", "rt", stdin);

    int i, j, myOldIdx, myNextIdx, othersOldIdx, othersNextIdx, N, overTakes = 0;
    string car;
    map<string, int> carsEnterStrToInt;
    map<int, string> carsEnterIntToStr;
    map<string, int> carsExitStrToInt;
    map<int, string> carsExitIntToStr;
    cin >> N;
    for (i = 0; i < N; i++)
    {
        cin >> car;
        carsEnterIntToStr[i] = car;
        carsEnterStrToInt[car] = i;
    }
    for (i = 0; i < N; i++)
    {
        cin >> car;
        carsExitStrToInt[car] = i;
        carsExitIntToStr[i] = car;
    }

    for (myOldIdx = 0; myOldIdx < N; myOldIdx++)
    {
        myNextIdx = carsExitStrToInt[carsEnterIntToStr[myOldIdx]];
        // 내 뒤에 있는 차만 체크. 내가 앞지른 것만 체크함. 내가 뒤쳐진건 체크 안 함.
        for (othersNextIdx = myNextIdx + 1; othersNextIdx < N; othersNextIdx++)
        {
            othersOldIdx = carsEnterStrToInt[carsExitIntToStr[othersNextIdx]];
            // 내 뒤의 차 중 원래 Idx가 나보다 앞이었던 경우
            if (myOldIdx > othersOldIdx)
            {
                cout << "I'm " << carsEnterIntToStr[myOldIdx] << endl;
                overTakes++;
                break;
            }
        }
    }
    cout << overTakes << endl;
    return 0;
}
