/**
 * @Author: Max
 * @Time: 10/27/21 22:41
 */

#include<bits/stdc++.h>
using namespace std;
const int MAX=1e6+5;
typedef long long ll;
char s[MAX];
ll d[MAX][4];
int main() {
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    d[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= 3; j++) {
            if (d[i - 1][j] == 0)continue;
            if (j < 3)d[i][j + 1] += d[i - 1][j];
            d[i][j] += d[i - 1][j];
            for (int k = i - 1; k >= 1 && i - k <= j; k--)//往前找到第一个k使得s[k]=s[i]
            {
                if (s[k] == s[i]) {
                    d[i][j] -= d[k - 1][j - (i - k)];
                    break;
                }
            }
        }
    }
    printf("%lld\n", d[n][0] + d[n][1] + d[n][2] + d[n][3]);
    return 0;
}