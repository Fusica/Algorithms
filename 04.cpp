/**
 * @Author: Max
 * @Time: 11/15/21 20:44
 */

#include<bits/stdc++.h>
#define Left_node(arr) arr * 2 + 1
#define Right_node(arr) arr * 2 + 2


using namespace std;
int N, Q, len;
long long ans, temp;
pair<int, int> Order[100000];
struct segtree {  //建立线段树，并更新最小值
    vector<long long> values, mins;
    void init(int N) {
        len = 1;
        while (len < N) len *= 2;
        values.assign(2 * len, 0);
        mins.assign(2 * len, 0);
        build(0, 0, len, N);
    }
    void build(int x, int Left_node, int Right_node, int R) {
        if (Right_node - Left_node == 1) {
            if (Left_node < R) {
                cin >> mins[x];
                values[x] = mins[x];
            }
            return;
        }
        int mid = (Left_node + Right_node) / 2;
        build(Left_node(x), Left_node, mid, R);
        build(Right_node(x), mid, Right_node, R);
        mins[x] = min(mins[Left_node(x)], mins[Right_node(x)]) + values[x];
    }

    void update(int l, int r, int v, int x, int Left_node, int Right_node) {
        if (Left_node >= r || Right_node <= l) return;  //递归出口，当左节点已经大于右端或者右节点大于左端是，则一定不会存在
        if (Left_node >= l && Right_node <= r) {  //避免冗余查询，当是子集时，直接打出最小值
            mins[x] += v;
            values[x] += v;
            return;
        }
        int mid = (Left_node + Right_node) / 2;
        update(l, r, v, Left_node(x), Left_node, mid);
        update(l, r, v, Right_node(x), mid, Right_node);
        mins[x] = min(mins[Left_node(x)], mins[Right_node(x)]) + values[x];
        return;
    }

    long long get_min(int l, int r, int x, int Left_node, int Right_node) {
        if (Left_node >= r || Right_node <= l)
            return LLONG_MAX;
        if (Left_node >= l && Right_node <= r)
            return mins[x];
        int mid = (Left_node + Right_node) / 2;
        long long s1 = get_min(l, r, Left_node(x), Left_node, mid);
        long long s2 = get_min(l, r, Right_node(x), mid, Right_node);
        return min(s1, s2) + values[x];
    }
}tree;

/**
 * 定义一个排序方法
 * 按照右端点从小到大的顺序排列，相等的情况下，按照左端点从小到大的顺序排列
 */
bool cmp (const pair<int, int> &arr, const pair<int, int> &Order) {
    if (arr.second != Order.second)
        return arr.second < Order.second;
    return arr.first < Order.first;
}
int main() {
    cin >> N >> Q;
    tree.init(--N);
    for (int i = 0; i < Q; i++) {
        cin >> Order[i].first >> Order[i].second;
        if (Order[i].first > Order[i].second)  //输入订单起止城市，如果序号大的在前则交换顺序，保证右端为大数
            swap(Order[i].first, Order[i].second);
    }
    sort(Order, Order + Q, cmp);
    for (int i = 0; i < Q; i++) {
        temp = tree.get_min(Order[i].first, Order[i].second, 0, 0, len);
        ans += temp;
        tree.update(Order[i].first, Order[i].second, -temp, 0, 0, len);
    }
    cout << ans;
    return 0;
}