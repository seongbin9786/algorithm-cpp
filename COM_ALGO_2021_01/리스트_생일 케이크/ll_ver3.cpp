#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode
{
    int data;
    struct ListNode *link;
} ListNode;

/*
    생일 케이크(n, k) => last-survive index 반환
    ver.3: 촛불을 제거하는데, 연결 리스트 기반으로 함.
*/
ListNode *buildList(int n)
{
    int i;
    ListNode *p, *S = (ListNode *)malloc(sizeof(ListNode));
    S->data = 1;
    S->link = S;
    p = S;
    for (i = 2; i <= n; i++)
    {
        ListNode *next = (ListNode *)malloc(sizeof(ListNode));
        next->data = i;
        p->link = next; // 마지막 노드로 연결
        p = next;       // p는 계속 마지막 노드를 가리킴
    }
    p->link = S; // 마지막 노드의 link를 head가 가리키게.
    return S;
}

int runSimulation(ListNode *S, int n, int k)
{
    int i;
    ListNode *before = S, *toRemove;
    while (before != before->link) // List가 head만 있는 게 아니라면
    {
        for (i = 0; i < k - 1; i++) // 3칸 뛰어야 하는데, 2칸만 뜀
            before = before->link;
        toRemove = before->link;
        before->link = toRemove->link;
        free(toRemove);
        before = before->link;
    }
    return before->data;
}

void candle(int n, int k)
{
    ListNode *S = buildList(n);
    printf("n=%d, k=%d 일 때, %d번 째 양초가 마지막까지 남습니다.\n", n, k, runSimulation(S, n, k));
}

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);
    candle(n, k);
    return 0;
}
