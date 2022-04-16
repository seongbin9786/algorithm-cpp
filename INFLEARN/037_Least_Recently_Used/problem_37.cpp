#include "problem_37.hpp"
/*
유형: 정렬

[풀이 전략]
1. cache miss: 그냥 마지막꺼 제거하고 뒤로 순차적으로 옮기면 됨 (순차적으로 옮겨서 분류를 이렇게 한걸까...?)
2. cache hit: 맨 앞으로 가져오는 걸 어떻게 할까? 쉬운데? 이것도 그냥 swap 하면 끝남.
---
1, 2를 한 번에 할 수 있을듯
=> 안 될 듯. 삽입 정렬도 직접 못 짰잖아 ㅋㅋ
=> 못 짜면 코드 이상해질듯. 어떻게든 생각해내야 함.
---
(20:22 다음 기회에)

*/
void problem_37()
{
    int i, j = 0, size = 0, s, n, tmp;
    READ_TXT("./resources/input37.txt", "rt", stdin);
    scanf("%d %d", &s, &n);
    std::vector<int> jobs(n);
    int cache[10] = {0};
    for (i = 0; i < n; i++)
        scanf("%d", &jobs[i]);

    for (i = 0; i < n; i++)
    {
        // 마지막 것부터 바로 앞에걸로 덮어 쓰고 있는중.
        // cache[size-1] == jobs[i] 이면 이 루프는 실행되지 않음.
        // 뒤로 이동 중.
        for (j = size - 1; j > 0 && cache[j] != jobs[i]; j--)
            cache[j] = cache[j - 1];
        // j < 0 인 경우는 실행이 끝난 것.
        // j == 0인 경우 맨 앞 원소여야 하는 것.
        // => 둘 다 루프에서 실행이 안 됨.
        // 중간에 탈출한 경우: cache[j] == tmp
        // 0..j 를 한 칸 씩 뒤로 옮김
        tmp = j;
        for (j = 0; j < tmp; j++)
            cache[j + 1] = cache[j];
        cache[0] = jobs[i];
        if (size < s) // 무조건 추가됨?
            size++;
    }
    for (i = 0; i < size; i++)
        printf("%d ", cache[i]);
}
