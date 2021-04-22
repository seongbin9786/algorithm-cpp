#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 15
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

/*
    선택 정렬,
    삽입 정렬,
    셸 정렬
*/

void selection_sort(int *A, int N)
{
    int i, j, tmp, min;
    for (i = 0; i < N - 1; i++) // N-2는 안 됨
    {
        min = i;
        for (j = i + 1; j < N; j++) // N-1은 안 됨
        {
            if (A[min] > A[j])
                min = j;
        }
        // i가 min과 교체되는데 이 때 뒤로 가면서
        // 기존 원소의 순서가 바뀜
        // 만약 동일 원소들 중 하나가 선택된다면
        // 순서가 바뀌게 되므로 불안정 정렬임.
        SWAP(A[i], A[min], tmp);
    }
}

/*
    IDEA: j= (i-1) ==> 0 으로 가면서 새 원소를 비교함
*/
void insertion_sort(int *A, int N)
{
    int i, j, tmp, key;
    for (i = 1; i < N; i++)
    {
        key = A[i];                                // 저장해야 함. 덮어씌워짐
        for (j = i - 1; j >= 0 && A[j] > key; j--) // j >= 0인 이유? j[1]으로 j[0]을 옮겨야 하니까.
            A[j + 1] = A[j];
        // A[j] <= A[i] 인 상황
        // 근데 지금은 j-- 때문에 A[j] < A[j+1] <= A[i] 인 상황
        // A[j+1] 까지는 앞으로 옮겨졌음
        A[j + 1] = key;
    }
}

void bubble_sort(int *A, int N)
{
    int i, j, tmp;
    bool changed;
    // 큰 걸 뒤로 밀어넣는다고 생각하면 된다.
    for (i = N; i > 0; i--)
    {
        changed = false;
        for (j = 0; j < i; j++)
        {
            if (A[j + 1] < A[j])
            { // 이 성질 때문에 안정 정렬이다.
                changed = true;
                SWAP(A[j + 1], A[j], tmp);
            }
        }
        if (!changed) // 최적화
            break;
    }
}

void inc_insertion_sort(int *A, int first, int last, int gap)
{
    int i, j, key;
    // <= last로 바뀌고,
    for (i = first + gap; i <= last; i += gap) // first,last,gap 활용
    {
        // 이하 +/-i,1 대신 +/-gap으로 치환
        // 0도 first로 치환
        key = A[i];                                           // 저장해야 함. 덮어씌워짐
        for (j = i - gap; j >= first && A[j] > key; j -= gap) // j >= 0인 이유? j[1]으로 j[0]을 옮겨야 하니까.
            A[j + gap] = A[j];
        // A[j] <= A[i] 인 상황
        // 근데 지금은 j-- 때문에 A[j] < A[j+1] <= A[i] 인 상황
        // A[j+1] 까지는 앞으로 옮겨졌음
        A[j + gap] = key;
    }
}

void shell_sort(int *A, int N)
{
    int i, gap;
    for (gap = N / 2; gap > 0; gap /= 2)
    {
        if (gap % 2 == 0)
            gap += 1;
        for (i = 0; i < gap; i++)
            inc_insertion_sort(A, i, N - 1, gap);
    }
}

// digit 상수 = 2
// BUCKET 상수 = 10
#define BUCKET 10
#define DIGIT 2

/*
RADIX SORT 하는 법

1. q를 bucket 개수만큼 준비 (10진수,8진수 등)
- init까지 수행

2. DIGIT 만큼 반복할 것임
- 작은 자리수부터 modulo 해서 자리수에 맞는 큐에 push
- 모두 push 했으면 큐를 오름차순으로 exhaustive pop to 원 배열
- q[A[i] / factor % 10] => factor는 1 ~ *=10 진행
*/
void radix_sort(int *A, int N)
{
    int i, b, d, factor = 1;
    Queue q[BUCKET];

    for (b = 0; b < BUCKET; b++)
        initQ(q[b]);

    for (d = 0; d < DIGIT; d++)
    {
        for (i = 0; i < n; i++)
            enqueue(q[i / factor % 10], A[i]);
        for (b = i = 0; b < BUCKET; b++)
            while (!isEmpty(q[b]))
                A[i++] = dequeue(q[b]);
        factor *= 10;
    }
}

// i < j, j < i 실수 멈춰!
void randArr(int *A)
{
    int i, j;
    for (i = 0; i < MAX_SIZE; i++)
    {
        A[i] = rand() % 100;
        for (j = 0; j < i; j++)
            if (A[j] == A[i])
            {
                i--;
                break;
            }
    }
}

void printArr(int *A)
{
    int i;
    for (i = 0; i < MAX_SIZE; i++)
        printf("%d, ", A[i]);
    printf("\n");
}

int main()
{
    srand(time(NULL));

    int A[MAX_SIZE];

    randArr(A);
    selection_sort(A, MAX_SIZE);
    printArr(A);

    randArr(A);
    insertion_sort(A, MAX_SIZE);
    printArr(A);

    randArr(A);
    bubble_sort(A, MAX_SIZE);
    printArr(A);

    randArr(A);
    shell_sort(A, MAX_SIZE);
    printArr(A);
    return 0;
}