/*
reverse를 더 효율적으로 구현하는 방법 (#12 에서도 유사한 논리 사용)
*/
int reverse_teacher(int x)
{
    int res = 0, tmp;
    while (x > 0)
    {
        tmp = x % 10;
        // res * 10이 대박이고, res = 0 때문에 초깃값 0도 대비함;;
        /* 
        (ex) 3700
        x=3700, tmp=0, res=0*10+0=0
        x=370, tmp=0, res=0*10+0=0
        x=37, tmp=7, res=0*10+7=7
        x=3, tmp=3, res=7*10+3=73
        res=73
        */
        res = res * 10 + tmp;
        x /= 10;
    }
    return res;
}
