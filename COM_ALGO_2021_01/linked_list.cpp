#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode
{
    int data;
    struct ListNode *link;
} ListNode;

typedef struct LinkedListType
{
    ListNode *head;
} LinkedListType;

void init(LinkedListType *L)
{
    L->head = NULL;
}

// 이하의 함수는 head != NULL을 가정한다. head->link = NULL 가능
void addFirst(LinkedListType *L, int item)
{
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    node->data = item;
    node->link = L->head;
    L->head = node;
}

void add(LinkedListType *L, int pos, int item)
{
    if (L->head == NULL)
    {
        addFirst(L, item);
        return;
    }
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    ListNode *before = L->head;
    for (int i = 0; i < pos - 1; i++) // pos-1만 까지만 가는 이유: pos-1의 link가 필요하므로. idx=0부터 시작하는 것에 주의
        before = before->link;
    node->data = item;
    node->link = before->link; // 중간 삽입
    before->link = node;       // 중간 삽입
}

int removeAt(LinkedListType *L, int pos)
{
    if (L->head == NULL)
    {
        printf("emptyListException\n");
        return -1;
    }
    ListNode *before = L->head;
    for (int i = 0; i < pos - 1; i++)
        before = before->link;
    ListNode *removed_node = before->link;
    int removed_data = removed_node->data;
    before->link = removed_node->link;
    free(removed_node);
    return removed_data;
}

int removeFirst(LinkedListType *L)
{
    ListNode *removed_node;
    int removed_data;
    if (L->head == NULL)
    {
        printf("emptyListException\n");
        return -1;
    }
    removed_node = L->head;
    removed_data = removed_node->data;
    L->head = removed_node->link;
    free(removed_node);
    return removed_data;
}

int removeLast(LinkedListType *L)
{
    ListNode *removed_node;
    int removed_data;
    if (L->head == NULL)
    {
        printf("emptyListException\n");
        return -1;
    }
    else if (L->head->link == NULL)
    {
        removed_node = L->head;
        removed_data = L->head->data;
    }
    else
    {
        ListNode *before = L->head;
        // before와 last가 있어야 하므로, 계속 탐색하려면 현재를 포함해 3개는 있어야 함
        while (before != NULL && before->link != NULL && before->link->link != NULL)
            before = before->link;
        removed_node = before->link;
        removed_data = removed_node->data;
        before->link = NULL;
    }
    free(removed_node);
    return removed_data;
}

int get(LinkedListType *L, int pos)
{
    if (L->head == NULL)
    {
        printf("emptyListException\n");
        return -1;
    }
    ListNode *it = L->head;
    for (int i = 0; i < pos; i++)
        it = it->link;
    return it->data;
}

void set(LinkedListType *L, int pos, int item)
{
    if (L->head == NULL)
    {
        printf("emptyListException\n");
        return -1;
    }
    ListNode *it = L->head;
    for (int i = 0; i < pos; i++)
        it = it->link;
    it->data = item;
}

void printList(LinkedListType *L)
{
    if (L->head == NULL)
    {
        printf("emptyListException\n");
        return -1;
    }
    // head에도 저장
    for (ListNode *it = L->head; it != NULL; it = it->link)
        printf("[%d] -> ", it->data);
    printf("NULL\n");
}

int main_circular_linked_list()
{
    int i, removed;
    LinkedListType *list = (LinkedListType *)malloc(sizeof(LinkedListType));
    init(list);

    addFirst(list, 10);
    printList(list);

    for (i = 1; i <= 5; i++)
        add(list, i, (i + 1) * 10);
    printList(list);

    removed = removeFirst(list);
    printf("removed: %d\n", removed);
    printList(list);

    removed = removeLast(list);
    printf("removed: %d\n", removed);
    printList(list);

    removed = removeAt(list, 1); // 앞에서 2번째 원소 제거
    printf("removed: %d\n", removed);
    printList(list);

    return 0;
}