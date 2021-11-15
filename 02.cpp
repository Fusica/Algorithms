/**
 * @Author: Max
 * @Time: 9/19/21 19:18
 */


#include <cstdio>
using namespace std;

int num[12],solve[12],d[12],ans[12];
char str[12][25];
bool visted[12];
int h,n,tread,q,minTime;  //minq暂时的解题数，tread为读题时间，minTime为用于比较的最短解题时间

void Dfs(int tn,int ttime,int time)  //ttime为按照规则计算的总耗时(加上惩罚时间)
{
    if(time > h) return;  //如果答题时间超时，返回
    if(tn > q || (tn == q && ttime<minTime))  //minTim为暂时的最优解
    {
        q = tn;
        minTime = ttime;
        for(int i=0;i<tn;i++)
            ans[i] = num[i];
    }
    if(tn >= n) return;
    for(int i=0;i<n;++i)
        if(!visted[i])
        {
            visted[i] = true;
            num[tn] = i;
            Dfs(tn+1,ttime+time+solve[i]+(time+solve[i]-5)/60*(d[i]+20),time+solve[i]+(time+solve[i]-5)/60*d[i]);
            visted[i] = false;
        }
}

int main()
{
    while(scanf("%d",&h)&&h>=0)  //负数为输入的终止条件
    {
        scanf("%d%d",&n,&tread);
        q = 0;
        h = h * 60;  //将hour转化成min
        for(int i=0;i<n;++i)
            scanf("%s%d%d",str[i],&solve[i],&d[i]);
        Dfs(0,0,tread);
        printf("Total Time = %d\n",minTime);
        for(int i=0;i<q;++i)
            printf("%s\n",str[ans[i]]);

    }
    return 0;
}