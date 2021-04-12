#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENT 100

typedef struct
{
    int arr[MAX_ELEMENT];
    int length;
} HeapType;

typedef struct Stack
{
    int arr[MAX_ELEMENT];
    int top;
} StackType;

void initHeap(HeapType *heap);
void insertItem(HeapType *heap, int item);
void upHeap(HeapType *heap);
void printHeap(HeapType *heap);

void initStack(StackType *stack);
bool isEmpty(StackType *stack);
void push(StackType *stack, int item);
int pop(StackType *stack);

void binaryExpansion(int idx, StackType *stack);
int findLastNode(HeapType *heap);

void initHeap(HeapType *heap)
{
    heap->length = 0;
}

void insertItem(HeapType *heap, int item)
{
    // arr[1]부터 시작
    heap->length++;
    heap->arr[heap->length] = item;
    upHeap(heap); // 위로 올라가면서 원소 비교
}

// 올라가며 비교하는 형태로 min heap 구성
void upHeap(HeapType *heap)
{
    int child = heap->length;
    int toInsert = heap->arr[child];
    while (child > 1 && heap->arr[child / 2] > toInsert)
    {
        heap->arr[child] = heap->arr[child / 2];
        child /= 2;
    }
    heap->arr[child] = toInsert;
}

void printHeap(HeapType *heap)
{
    int i;
    for (i = 1; i <= heap->length; i++)
        printf("[%d] ", heap->arr[i]);
    printf("\n");
}

void initStack(StackType *stack)
{
    stack->top = -1;
}

bool isEmpty(StackType *stack)
{
    return stack->top == -1;
}

void push(StackType *stack, int item)
{
    // full check 미수행
    stack->arr[++stack->top] = item;
}

int pop(StackType *stack)
{
    if (isEmpty(stack))
    {
        printf("throw StackEmptyException\n");
        return -1;
    }
    return stack->arr[stack->top--];
}

void binaryExpansion(int heapLength, StackType *stack)
{
    while (heapLength > 0)
    {
        push(stack, heapLength % 2);
        heapLength /= 2;
    }
}

int findLastNode(HeapType *heap)
{
    StackType *s = (StackType *)malloc(sizeof(StackType));
    initStack(s);
    binaryExpansion(heap->length, s); // len=8 => 1000 인데 pop해서 000됨
    pop(s);                           // remove highest-order bit
    int bit, idx = 1;
    while (!isEmpty(s))
    {
        bit = pop(s);
        if (bit == 0)
            idx *= 2;
        else
            idx = idx * 2 + 1;
    }
    return heap->arr[idx];
}

int main()
{
    int i;
    HeapType *h = (HeapType *)malloc(sizeof(HeapType));
    initHeap(h);
    srand(time(NULL));

    for (i = 0; i < 8; i++)
        insertItem(h, rand() % 100);
    printHeap(h);

    int lastElem = findLastNode(h);
    printf("lastElem: %d\n", lastElem);

    return 0;
}
