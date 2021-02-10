#include "problem_60.hpp"

/*
유형: DFS [?]
[풀이 전략]
- N(<=10)개의 자연수 원소 구성 집합 -> 두 부분집합으로 나누었을 때 -> 원소의 합이 서로 같은 case 존재 하면 YES otherwise NO
- (ex) [1,3,5,6,7,10] -> sum([1,3,5,7]) == sum([6, 10])
*/
void problem_60()
{
    int n;
    READ_TXT("./resources/input60.txt", "rt", stdin);
    scanf("%d", &n);
    printf("%d\n", n);
}
