/**
 * @Author: Max
 * @Time: 10/29/21 10:59
 */

/**
 * 首先题目要求字典序最小的，娜美如果存在这样的一条食物链，那么球队1一定在第一位
 */

#include <iostream>

using namespace std;


int n, flag = 0;
int result[21];
bool v[21][21], visit[21];

void dfs(int index, int num) {
    if (flag == 1) return;  //找到数组就直接return
    result[index] = num;  //存储找到的食物链的每一位
    if (index == n && v[num][1]) {  //index=n代表已经找到第n各球队，且该球队战胜过1，则将flag置为1，代表已经找到想要的食物链
        flag = 1;
        return;
    }
    if (index == n) return;  //如果遍历到n，无论如何，所有的遍历都已经结束
    bool cut = false;
    for (int i = 1; i <= n; i++) {  //进行剪枝操作，如果没有一支球队战胜过球队1，那么根据第七行题设条件，必然没有这样的一条食物链
        if (!visit[i] && v[i][1])
            cut = true;
    }
    if (!cut) return;
    visit[num] = true;  //开始DFS
    for (int i = 1; i <= n; i++) {
        if (!visit[i] && v[num][i])
            dfs(index + 1, i);
    }
    visit[num] = false;
}
int main() {
    cin >> n;
    char s[21];
    for (int i = 1; i <= n; i++) {
        cin >> (s+1);
        for (int j = 1; j <= n; j++) {
            if (s[j] == 'W')
                v[i][j] = 1;
            if (s[j] == 'L')
                v[j][i] = 1;
        }
    }
    dfs(1, 1);
    if (flag == 1) {
        for (int i = 1; i <= n; i++)
            if(i == 1)
                cout << "" << result[i];
            else
                cout << " " << result[i];

    } else {
        cout << "No Solution";
    }
    return 0;
}