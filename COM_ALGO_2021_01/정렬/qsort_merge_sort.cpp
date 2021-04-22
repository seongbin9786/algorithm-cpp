#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

#define MAX_ELEM 8

int sorted[MAX_ELEM];

// 얘는 quicksort임
// qsort는 partition 이후 뭘 하지?
// 그냥 더 작은 부분에 대해 quicksort 함
// switch rule-breaking items btw the pivot, so make sure that every item respects its boundary
int partition_me(int *arr, int l, int r)
{
    // TODO: pivot을 항상 중간으로 잡는게 맞나? nope
    // pivot은 하나씩 교환하면서 만나는 중간 지점을 말한다.
    int low = l, high = r, pivot = (l + r) / 2; // 피벗을 구하는데 O(n)을 사용할 수도 있을까? 모르겠다.
    int tmp;
    while (low < high) //  && low <= r && high >= l <---- l <= low < high <= r 이므로 필요 없다.
    {
        printf("arr[l=%d, r=%d]:\n", l, r);
        for (int i = l; i <= r; i++)
            printf("%d, ", arr[i]);
        printf("\n");

        // r, l까지는 도달 가능하나, r, l인데도 가는건 아니다. <----- 그럼 등호는 넣으면 안되죠;
        while (low < pivot && arr[low] <= arr[pivot]) // pivot과 비교 시 등호가 왜 필요한가?
            low++;
        while (high > pivot && arr[high] >= arr[pivot])
            high--;
        if (low != high)
        {
            // pivot을 서로 안 넘어간 경우
            SWAP(arr[low], arr[high], tmp);
            printf("arr[low]=%d, arr[high]=%d, pivot=%d\n", arr[low], arr[high], arr[pivot]);
        }
        else
        {
            // pivot을 지금 바꿔주면 정렬 끝
            // low를 쓰면 안 되는 이유?
            /*
            3 5 6 7 [3] 1 9 4 2
            [case1]
            low=0 (3 <= 3 인데 진행 y/n ? 진행 안 하면 동일 원소 정렬은 어떻게 함? => 그래서 다음 턴에 low++, high--로 시작함. do-while 쓰거나.)
                => 만약 등호를 넣어주면 무슨 문제가 발생함?
            high=7

            [case2]
            3 3 [3] 3 3
            low=0 ===> 4
            high=4 ====> 0
            1. 한 사이클에 switch하고 종료? yes => 이 경우 pivot이 0이 되는데
            pivot을 3으로 유지하고 싶으면 어떻게 할 수 있을까?
            => 애초에 low, high가 pivot을 못 넘어가게 하고, pivot을 high와 바꾸지 않으면 됨.
            */
            return pivot; // 이렇게 되면 pivot은 무조건 중간이지만, 정렬이 안 될걸? 한 쪽의 개수가 더 많으면 정렬이 될 수가 없음. 그래서 pivot을 left로 잡는거임.
            // pivot을 중간에 고정할 순 없다. 중간 idx의 값을 사용할 순 있겠지만, 어차피 high와 swap해야 함. (low와 swap하던가)
        }
    }
}

// 같은 원소가 있어도 항상 잘 된다.
int partition(int *arr, int l, int r)
{
    int low = l - 1, high = r, pivot = r;
    int tmp;

    do
    {
        // do-while을 쓴 이유는 단순히 다음 step으로 가기 위함임
        do
            low++;
        while (arr[low] < arr[pivot]);

        do
            high--;
        while (arr[high] > arr[pivot]);

        if (low < high)
            SWAP(arr[low], arr[high], tmp);

    } while (low < high);

    /*
    pivot=left 였으면 high와 바꾸고,
    pivot=right 였으면 low와 바꾼다.

    ----
    [왜 저렇게 바꿔야 하나? pivot=left 기준 설명]

    low > high ==> arr[low] < pivot && arr[high] < pivot 이므로,
    pivot < high < low 인 상황인데,
    당장은
    arr[high] < arr[pivot] < arr[low] 상태이므로, 
    정렬을 유지하려면 arr[high] <-> arr[pivot]을 바꾸는 수 밖에 없다.
    그렇게 되면,
    high < pivot < low가 되고,
    arr[pivot] < arr[high] < arr[low] 이므로
    high가 pivot의 역할을 맡아 pivot으로 반환되면 된다.
*/
    SWAP(arr[pivot], arr[low], tmp);
    return low;
}

// 같은 원소가 있어도 항상 잘 된다.
// 잘 안 되는데요
int partition_random_pivot(int *arr, int l, int r, int random_pivot)
{
    int low = l - 1, high = r, pivot = random_pivot;
    int tmp;

    // hide pivot
    SWAP(arr[r], arr[pivot], tmp);

    do
    {
        do
            low++;
        while (arr[low] < arr[r]); // pivot 값을 저장하는 변수 대신 arr[r] 사용

        do
            high--;
        while (arr[high] > arr[r]);

        if (low < high)
            SWAP(arr[low], arr[high], tmp);

    } while (low < high);

    // swap pivot
    SWAP(arr[low], arr[r], tmp);
    return low;
}

void quick_sort(int *arr, int l, int r)
{
    if (l >= r)
        return;
    int pivot = partition(arr, l, r);
    // pivot은 정렬에서 제외된다.
    quick_sort(arr, l, pivot - 1);
    quick_sort(arr, pivot + 1, r);
}

void quick_sort_random_pivot(int *arr, int l, int r)
{
    if (l >= r)
        return;
    int random_pivot = rand() % (r - l + 1) + l;
    int pivot = partition_random_pivot(arr, l, r, random_pivot);
    // pivot은 정렬에서 제외된다.
    quick_sort(arr, l, pivot - 1);
    quick_sort(arr, pivot + 1, r);
}

void merge(int *arr, int l, int m, int r)
{
    // l~r 구간에 대해 정렬하는 중
    int i = l, j = m + 1, k = l;
    while (i <= m && j <= r) // m, r이 길이가 아니라 index여서 포함해야 함.
        sorted[k++] = arr[arr[i] < arr[j] ? i++ : j++];

    while (i <= m)
        sorted[k++] = arr[i++];
    while (j <= r)
        sorted[k++] = arr[j++];

    for (i = l; i <= r; i++)
        arr[i] = sorted[i];
}

void merge_sort(int *arr, int l, int r)
{
    // l-r >=2까진 d&c를 수행해야 함. 1개부터는 의미 없으니 미수행
    if (l >= r) // idx가 같으면 배열의 크기 = 1
        return;
    int m = (l + r) / 2;
    // merge_sort 호출은 그냥 반으로 나뉜 구역에 대해 merge를 호출하는 역할
    merge_sort(arr, l, m);
    merge_sort(arr, m + 1, r);
    merge(arr, l, m, r);
}

// 19:45 퀵정렬 응용문제 보기.
// 정렬 일반 - 9:00 부터 기수정렬 보기.

int main()
{
    int i;
    int arr[MAX_ELEM];
    srand(time(NULL));

    //mergesort
    for (i = 0; i < MAX_ELEM; i++)
        arr[i] = rand() % 100;

    merge_sort(arr, 0, MAX_ELEM - 1);
    for (i = 0; i < MAX_ELEM; i++)
        printf("%d, ", arr[i]);
    printf("\n");

    //quicksort
    for (i = 0; i < MAX_ELEM; i++)
        arr[i] = rand() % 100;

    quick_sort(arr, 0, 10 - 1);
    for (i = 0; i < 10; i++)
        printf("%d, ", arr[i]);
    printf("\n");

    for (i = 0; i < MAX_ELEM; i++)
        arr[i] = rand() % 100;

    quick_sort_random_pivot(arr, 0, MAX_ELEM - 1);
    for (i = 0; i < MAX_ELEM; i++)
        printf("%d, ", arr[i]);
    printf("\n");

    return 0;
}
