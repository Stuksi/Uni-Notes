// Next Greater Element
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

void NGE(vector<int>& v) {
    if(v.size() == 0) return;
    stack<int> s;
    s.push(v[0]);
    for (size_t i = 1; i < v.size(); i++) {
        while (!s.empty() && s.top() < v[i]) {
            cout << "(" << s.top() << " ," << v[i] << ")" << " ";
            s.pop();
        }
        s.push(v[i]);
    }   
    while (!s.empty()) {
        cout << "(" << s.top() << " ," << -1 << ")" << " ";
        s.pop();
    }
}

int main() {

    vector<int> v = { 4, 5, 2, 3, 25 };
    NGE(v);

    return 0;
}