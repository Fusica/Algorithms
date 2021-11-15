/**
 * @Author: Max
 * @Time: 11/15/21 16:15
 */

#include <iostream>
#include <vector>
#include <set>

using namespace std;

int N, M, L;
vector<int> statement;
set<int> result;

void DFS(int index, bool &flag){
    if (index == 0 || result.size() == M){
        if (result.size() == M){
            int liar = 0, w_liar = 0;
            for (int i = 1; i <= N; ++i) {
                if ((statement[i]>0) ^ (result.find(abs(statement[i])) == result.end())){
                    ++liar;
                    if (result.find(i) != result.end()){
                        ++w_liar;
                    }
                }
            }
            if (liar == L && w_liar > 0 && w_liar < N)
                flag = true;
        }
        return;
    }
    result.insert(index);
    DFS(index-1, flag);
    if (flag)
        return;
    result.erase(index);
    DFS(index-1, flag);
}

int main() {
    bool flag = false;
    cin >> N >> M >> L;
    statement.resize(N+1);
    for (int i = 1; i < N+1; ++i) {
        cin >> statement[i];
    }
    DFS(N, flag);
    if (flag)
        for (auto i = result.rbegin(); i != result.rend(); ++i) {
            if (i == result.rbegin())
                cout << "" << *i;
            else
                cout << " " << *i;
        }
    else
        cout << "No Solution";
    return 0;
}

