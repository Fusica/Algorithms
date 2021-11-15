/**
 * @Author: Max
 * @Time: 10/6/21 19:57
 */

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
int N,M;
int tmp=0;
int List[10001];
bool isFind=false;
bool IsSearched[10001];
void find(int i)
{
    if (i == N)
        return;

    if (tmp > M)
        return;

    tmp += List[i];
    IsSearched[i] = true;

    if(isFind)
        return;

    if(tmp == M)
    {
        for(int j=0; j<N; j++)
        {
            if(IsSearched[j])
            {
                if(!isFind)
                {
                    cout<<List[j];
                    isFind = true;
                }
                else
                {
                    cout<<" "<<List[j];
                }
            }
        }
    }
    else
    {
        find(i+1);
    }

    tmp -= List[i];
    IsSearched[i] = false;

    find(i+1);
    return;
}
int main()
{
    int sum = 0;
    memset(IsSearched,0,sizeof(IsSearched));
    cin>>N>>M;
    for(int i=0; i<N; i++)
    {
        cin>>List[i];
        sum += List[i];
    }
    if(sum < M)
    {
        cout<<"No Solution";
    }
    else
    {
        sort(List,List+N);
        find(0);
        if(!isFind)
            cout<<"No Solution";
    }
    return 0;
}
