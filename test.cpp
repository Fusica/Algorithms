#include <stdio.h>
#include <vector>
#include <set>

using namespace std;

int main(){
    vector<int> v;
    for (int i = 0; i < 10; i++){
        v.push_back(i);
        v.push_back(i);
    }

    set<int> s;
    s.insert(v.begin(), v.end());
    set<int>::iterator it;
    for (it = s.begin(); it != s.end(); it++){
        printf("%d\t", *it);
    }
    printf("\n");

    printf("%d\n", s.count(9));
    printf("%d\n", *(s.find(9)));
    return 0;
}