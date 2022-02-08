#include <iostream>
#include "../include/debugopen.hpp"

using namespace std;

/*
    16987
    [Silver 1] 계란으로 계란치기

    계란으로 계란을 치게 될 경우:
        1. 각 계란에는 내구도와 무게가 정해져있다. 
        2. 각 계란의 내구도는 상대 계란의 무게만큼 깎이게 된다. 
        3. 그리고 내구도가 0 이하가 되는 순간 계란은 깨지게 된다. 
    
    예를 들어 
        1. 계란 1의 내구도 = 7, 무게 = 5 
           계란 2의 내구도 = 3, 무게 = 4

        2. 계란 1으로 계란 2를 치게 되면 
           계란 1의 내구도는 4만큼 감소해 3이 되고 
           계란 2의 내구도는 5만큼 감소해 -2가 된다. 

        3. 충돌 결과 계란 1은 아직 깨지지 않았고 계란 2는 깨졌다.

    유현이가 인범이에게 알려준 퍼즐은 일렬로 놓여있는 계란에 대해 
    왼쪽부터 차례로 들어서 한 번씩만 다른 계란을 쳐 최대한 많은 계란을 깨는 문제였다. 
    구체적으로 계란을 치는 과정을 설명하면 아래와 같다.

    1. [가장 왼쪽]의 계란을 든다.

    2. 손에 들고 있는 계란으로 [깨지지 않은] [다른] 계란 중에서 [하나를 친다]. 
        - (대상이 꼭 오른쪽 계란을 칠 필요는 없다. 조건은 오른쪽 계란으로 치라는 것 뿐이다.)
        - 단, 손에 든 계란이 깨졌거나 깨지지 않은 다른 계란이 없으면 치지 않고 넘어간다. 
        - 이후 손에 든 계란을 원래 자리에 내려놓고 3번 과정을 진행한다.

    3. 가장 최근에 든 계란의 [한 칸 오른쪽 계란]을 손에 들고 2번 과정을 다시 진행한다. 
        - 단, 가장 최근에 든 계란이 가장 오른쪽에 위치한 계란일 경우 계란을 치는 과정을 종료한다. (종료 조건)
    
    이 과정을 통해 최대한 많은 계란을 깨는 것이 앞으로 인범이가 매일 아침마다 풀게 될 퍼즐이다. 
    그리고 유현이는 인범이가 찾은 답이 정답이 맞는지 확인해주려고 한다. 
    [일렬로 놓인 계란들의 내구도와 무게]가 차례대로 주어졌을 때 [최대 몇 개의 계란을 깰 수 있는지] 알아맞춰보자.

*/

int weight_16987[10];
int hp_16987[10];
int N_16987;
int maxEggBroken = 0;

// `curIdx`번째 계란으로 부실 것이다.
void breakEgg(int curIdx)
{
    // 1. 계란을 선택한다: curIdx번째 계란
    // 해당 계란은 아직 안 깨졌어야 한다.
    // 깨졌으면 무시한다.
    // 추가: 깨진 경우 return이 아니라, next egg를 호출해야 함.
    if (hp_16987[curIdx] <= 0)
    {
        if (curIdx < N_16987)
            breakEgg(curIdx + 1);
        else
            return; // 이게 작동을 안 하나? ;;
    }

    // 2. 나머지 계란을 순차적으로 내려친다.
    for (int target = 1; target <= N_16987; target++)
    {
        // 2-1. 셀프 킬 불가
        if (curIdx == target)
            continue;

        // 2-2. 당할 계란을 선택한다: target번째 계란
        // 만약 target번째 계란이 깨져있으면 다음 계란을 선택한다.
        if (hp_16987[target] <= 0)
            continue;

        // 왜 인지는 모르겠는데, hp[curIdx] <= 0 인데도 여길 침범할 수 있다. ( 내가 멍청한 것인데... )
        if (hp_16987[curIdx] <= 0)
            continue;

        // 2-3. 서로 내려친다.
        hp_16987[curIdx] -= weight_16987[target];
        hp_16987[target] -= weight_16987[curIdx];
        // cout << "[stage:" << curIdx << "]\n";
        // cout << "[i:" << curIdx << "] ----hits---> [j:" << target << "]\n";
        // cout << "hp:" << hp[curIdx] << " || hp:" << hp[target] << "\n";

        // 깨진 계란의 개수를 계산하고 저장한다.
        // 여기서 계산하는 게 맞음.
        // 때릴 수 있는 모든 경우에서 체크해야 최댓값을 확인할 수 있음.
        int k, curMax = 0;
        // cout << "current hps:\n[";
        for (k = 1; k <= N_16987; k++)
        {
            // cout << hp[k] << ",";
            if (hp_16987[k] <= 0)
                curMax++;
        }

        if (curMax > maxEggBroken)
            maxEggBroken = curMax;
        // cout << "]\ntotal:" << curMax << "\n";
        // cout << "----------------------\n";

        if (curIdx < N_16987)
        {
            // 다음 계란으로 이동한다.
            breakEgg(curIdx + 1);
        }

        // 3. 계란을 복구한다. 애초에 없었던 일로 하는 것이기 때문이다.
        hp_16987[curIdx] += weight_16987[target];
        hp_16987[target] += weight_16987[curIdx];
    }
}

int main_16987()
{
    // 초기화
    int h, w, i;
    READ_TXT("./input.txt", "rt", stdin);
    cin >> N_16987;
    for (i = 1; i <= N_16987; i++) // 1-index
    {
        cin >> h >> w;
        hp_16987[i] = h;
        weight_16987[i] = w;
    }
    breakEgg(1); //1-index
    cout << maxEggBroken << "\n";
    return 0;
}
