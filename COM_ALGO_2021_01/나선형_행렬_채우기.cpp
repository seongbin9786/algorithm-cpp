#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

#define MAX_ELEM 8

// 5x4 행렬
#define ROW 4 // 행(N)
#define COL 5 // 열(M)

/*
응용 문제: 색 분리 (제자리, O(n))
- 구별 가능한 요소에 색깔을 부여했다고 보는 게 좋을듯
- 힌트 봐버렸다..
    - partition이 O(n)이고, 한 파티션으로 구현 가능하다.
    - left, right 포인터를 잡고 ++,-- 하면서 각각 빨강, 파랑을 찾는다.
    - 찾으면 멈추고, 교환한다.
    - left < right 인 경우 그냥 스왑하면 되는데,
    - left > right 인 경우는?
        - (★)
*/
void Separate_Colors()
{
    int arr[MAX_ELEM] = {0, 1, 1, 1, 0, 1, 0, 1}; // 1=red, 0=blue
    int left = -1, right = 8, tmp;
    while (left < right)
    {
        do
        {
            left++;
        } while (arr[left] == 0);
        do
        {
            right--;
        } while (arr[right] == 1);

        if (left < right)
            SWAP(arr[left], arr[right], tmp);
        else // 끝나는 순간이다.
        {
            for (int i = 0; i < 8; i++)
                printf("%d, ", arr[i]);
            printf("\n");
        }
    }

    for (int i = 0; i < 8; i++)
        printf("%d, ", arr[i]);
    printf("\n");
}

// A[N][M] == A[5][4] == 4x5 행렬 == N=4, M=5
/*
IDEA

1. top, left, right, bottom이 있는데,
- 행렬의 바깥 영역을 의미한다.
- 그래서 한 바퀴 돌면 한 칸씩 shrink한다. (left++,right--,bottom--,top++)
- 바깥 영역을 돌기 때문에, i=top,bottom 이고, j=left,right 이다.
- 돌기 위해선 4방향으로 쭉 달리면 된다.
- 얼만큼 달리느냐? left->right, top->bottom, right->left, bottom->top 인데,
	=> left->right=4,2,0,...
	=> top->bottom=4,2,0
	=> right->left=4,2
	=> bottom->top=2,0 [!]
*/
void Spiral(int A[ROW][COL], int row, int col)
{
    int i, j;
    int num = 1;
    // 열, 행으로 받아서 => right 열 기준, bottom 행 기준
    int left = 0, right = col - 1, top = 0, bottom = row - 1;

    while (left <= right && top <= bottom)
    {
        // 한 칸 남김
        for (j = left; j < right; j++)
            A[top][j] = num++;

        // 첫 칸부터 시작, 한 칸 남김
        for (i = top; i < bottom; i++)
            A[i][right] = num++;

        // 첫 칸부터 시작, 한 칸 남김 (j > left)
        for (j = right; j > left; j--)
            A[bottom][j] = num++;

        // 맨 아랫칸부터 시작, 한 칸 남김 (i > top)
        for (i = bottom; i > top; i--)
            A[i][left] = num++;

        // shrink
        left++;
        top++;
        right--;
        bottom--;
    }
}

int main()
{
    int A[ROW][COL] = {0}; // 4x5 행렬
    Spiral(A, ROW, COL);

    int i, j;
    /*
    열 > 행 순으로 nested 하고 [j][i]로 출력하는 것과
        - 직관적으로 옳음
    행 > 열 순으로 nested 하고 [i][j]로 출력하는 것이.
        - 이건 무슨 원리지?
            - 
    출력은 똑같다.
    */
    for (i = 0; i < ROW; i++) // 행(N=4)
    {
        for (j = 0; j < COL; j++)      // 열(M=5)
            printf("%02d, ", A[i][j]); // 열, 행
        printf("\n");
    }
    Separate_Colors();
    return 0;
}
