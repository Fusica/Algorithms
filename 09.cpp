/**
 * @Author: Max
 * @Time: 10/26/21 20:16
 */

#include <iostream>
#include <string.h>

using namespace std;

const int MAX = 1e6+1;
char main_str[MAX];
long long dp[MAX][4];

int main() {
    cin.getline(main_str+1, MAX);
    int len = strlen(main_str+1);
    dp[0][0] = 1;
    for (int i = 1; i <= len; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (dp[i-1][j] == 0)
                continue;
            if (j+1 <= 3){
                dp[i][j+1] += dp[i-1][j];
            }
            dp[i][j] += dp[i-1][j];
            for (int k = i-1; k >= 1 && i-k <= j; --k) {
                if (main_str[k] == main_str[i]){
                    dp[i][j] -= dp[k-1][j - (i-k)];
                    break;
                }
            }
        }
    }
    cout << dp[len][0] + dp[len][1] + dp[len][2] + dp[len][3];
    return 0;
}
