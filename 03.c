/**
 * @Author: Max
 * @Time: 10/3/21 21:57
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 502
#define EXPENSIVE 300001

struct tank
{
    double price;
    double length;
};

int compare(const void *a, const void *b);

int main()
{
    int n , i, index, j, flag, davg;
    double len, current_gas, sum, min_price, cmax, distance;
    struct tank tanks[MAX];

    while(scanf("%lf %lf %d %d", &cmax, &distance, &davg, &n) != EOF)
    {
        //接收输入参数
        for(i = 0; i < n; i ++)
        {
            scanf("%lf %lf", &tanks[i].price, &tanks[i].length);
        }

        //初始化最后一个加油站，也就是终点，作为判定贪心结束的重要标志
        tanks[n].price = 0;
        tanks[n].length = distance;

        //一箱油可以跑多远
        len = cmax * davg;

        //距离排序
        qsort(tanks, n, sizeof(tanks[i]), compare);

        if(tanks[0].length > 0)
        {	//初始油箱为空
            printf("The maximum travel distance = 0.00\n");
            continue;
        }else
        {	//贪心选择
            flag = 1;
            current_gas = sum = 0;

            for(i = 0; i < n;)
            {
                if((tanks[i + 1].length - tanks[i].length > len))
                {	//某两个加油站之间的距离大于汽车油箱装满油的最大行程
                    flag = 0;
                    printf("The maximum travel distance = %.2lf\n", tanks[i].length + len);
                    break;
                }else
                {
                    index = i;
                    min_price = tanks[i].price;
                    //找出当前油箱里的油能到达的所有加油站里，油价最便宜的那个
                    for(j = i + 1; tanks[j].length - tanks[i].length <= current_gas * davg && j <= n; j ++)
                    {
                        if(tanks[j].price < min_price)
                        {
                            index = j;
                            min_price = tanks[j].price;
                        }
                    }

                    if(index != i)
                    {
                        current_gas -= (tanks[index].length - tanks[i].length) / davg;
                        i = index;
                        continue;
                    }

                    //或找不到，则找到最近一个能加油的站，加些油跑到那个最便宜的那个站
                    index = i;
                    for(j = i + 1; tanks[j].length - tanks[i].length <= len && j <= n; j ++)
                    {
                        if(tanks[j].price < min_price)
                        {
                            index = j;
                            break;
                        }
                    }

                    if(index != i)
                    {
                        sum += ((tanks[index].length - tanks[i].length) / davg  - current_gas) * tanks[i].price;
                        current_gas = 0;
                        i = index;
                        continue;
                    }

                    //或找不到比当前站更便宜的站,则在当前站需要加满油，然后跑到能跑到所有站里最便宜的那个
                    index = i;
                    min_price = EXPENSIVE;
                    for(j = i + 1; tanks[j].length - tanks[i].length <= len && j <= n; j ++)
                    {
                        if(tanks[j].price < min_price)
                        {
                            index = j;
                            min_price = tanks[j].price;
                        }
                    }
                    sum += (cmax - current_gas) * tanks[i].price;
                    current_gas = cmax - (tanks[index].length - tanks[i].length) / davg;
                    i = index;
                }
            }
        }
        if(flag)
            printf("%.2lf\n", sum);

    }

    return 0;
}

int compare(const void *a, const void *b) {
    const struct tank *p = a;
    const struct tank *q = b;

    if (p->length > q->length)
        return 1;
    else if (p->length < q->length)
        return -1;
    else
        return 0;
}