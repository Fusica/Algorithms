/**
 * @Author: Max
 * @Time: 10/29/21 10:44
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int change(int amount, vector<int>& coins) {
    vector<int> dp(amount+1);
    dp[0] = 1;
    for(int coin : coins){
        for(int i=coin; i<=amount; i++){
            dp[i] += dp[i-coin];
        }
    }
    return dp[amount];
}

int main() {


    return 0;
}