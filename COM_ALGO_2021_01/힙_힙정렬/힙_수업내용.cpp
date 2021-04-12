#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENT 100

typedef struct
{
    int arr[MAX_ELEMENT]; // 이거 초기화 되나? 근데 초기화가 의미가 있나? 없는듯
    int length;
} HeapType;

void init(HeapType *heap);
void insertItem(HeapType *heap, int item);
void upHeap(HeapType *heap);
int removeMin(HeapType *heap);
void downHeap(HeapType *heap, int idx);
void heapSort(HeapType *heap, int list[]); // heap => list
void inPlaceHeapSort(HeapType *heap);
void buildHeap(HeapType *heap);
void rBuildHeap(HeapType *heap);
void printHeap(HeapType *heap);

void init(HeapType *heap)
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

int removeMin(HeapType *heap)
{
    int root = heap->arr[1];
    heap->arr[1] = heap->arr[heap->length];
    heap->length -= 1;
    // remove에서 굳이 downHeap을 빼낸 이유?
    downHeap(heap, 1); // root 제거 후, 마지막 원소를 올려서 내리는 형태
    return root;
}

void downHeap(HeapType *heap, int idx)
{
    int parent = idx, child = idx * 2;
    int tmp = heap->arr[idx];
    while (child <= heap->length)
    {
        if (child < heap->length && heap->arr[child] > heap->arr[child + 1]) // R이 있는 상태 && L > R
            child++;                                                         // L > R 이므로, root를 R과 바꾸는 게 맞음
        if (tmp <= heap->arr[child])                                         // 부모가 더 작으면 멈춤 **여기서 tmp여야 함
            break;
        heap->arr[parent] = heap->arr[child]; // 부모가 더 크니까 자식값을 부모로 복사 (부모 노드까진 이제 정상이 됨)
        parent = child;
        child *= 2;
    }
    heap->arr[parent] = tmp;
}

void heapSort(HeapType *heap, int list[])
{
    HeapType tmp;
    tmp.length = heap->length;
    int i;
    for (i = 1; i <= heap->length; i++)
        tmp.arr[i] = heap->arr[i];

    for (i = 1; i <= heap->length; i++)
        list[i - 1] = removeMin(&tmp);
}

// removeRoot 하고, length 칸이 비면, 그 칸에 removeRoot한 걸 넣으면 끝
void inPlaceHeapSort(HeapType *heap)
{
    int orgSize = heap->length;
    printf("orgSize: %d\n", orgSize);
    int i;
    for (i = 1; i <= orgSize; i++)
        heap->arr[heap->length] = removeMin(heap); // min heap인 경우 내림차순 정렬이 됨 (min이 뒤로 가니깐)

    for (i = 1; i <= orgSize; i++)
        printf("%d, ", heap->arr[i]);
    printf("\n");
}

void buildHeap(HeapType *heap)
{
    int i;
    // 내부 노드(1~n/2)에 대해 downHeap 수행
    for (i = heap->length / 2; i >= 1; i--)
        downHeap(heap, i);
}

// 사실상 downHeap 호출하는 역할만 수행 - 되긴 하는데 정말 이게 맞나 흠
void rBuildHeap(HeapType *heap, int idx)
{
    if (idx > heap->length)
        return;

    if (idx * 2 <= heap->length)
        rBuildHeap(heap, idx * 2);

    if (idx * 2 + 1 <= heap->length)
        rBuildHeap(heap, idx * 2 + 1);

    downHeap(heap, idx);
}

void printHeap(HeapType *heap)
{
    int i;
    for (i = 1; i <= heap->length; i++)
        printf("[%d] ", heap->arr[i]);
    printf("\n");
}

int main()
{
    int arr[100] = {0};
    int i;
    HeapType minHeap;
    init(&minHeap);
    srand(time(NULL));

    for (i = 0; i < 30; i++)
        insertItem(&minHeap, rand() % 100);
    printHeap(&minHeap);

    for (i = 0; i < 3; i++)
    {
        int removed = removeMin(&minHeap);
        printf("removed: %d\n", removed);
        printHeap(&minHeap);
    }

    heapSort(&minHeap, arr);
    for (i = 0; i < minHeap.length; i++)
        printf("%d, ", arr[i]);
    printf("-----\n");

    inPlaceHeapSort(&minHeap);

    printf("-----\n");

    HeapType bHeap;
    init(&bHeap);
    for (i = 1; i <= 8; i++)
    {
        bHeap.length++;
        bHeap.arr[i] = rand() % 100;
    }
    buildHeap(&bHeap);
    printHeap(&bHeap);
    inPlaceHeapSort(&bHeap);

    printf("-----\n");

    HeapType cHeap;
    init(&cHeap);
    for (i = 1; i <= 8; i++)
    {
        cHeap.length++;
        cHeap.arr[i] = rand() % 100;
    }
    rBuildHeap(&cHeap, 1);
    printHeap(&cHeap);
    inPlaceHeapSort(&cHeap);
    return 0;
}
