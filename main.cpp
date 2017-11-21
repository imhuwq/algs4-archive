#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>
#include <iostream>

using namespace std;

class Test {
private:
    int v = 0;

    int PrivateGetV() const {
        return v;
    }

public:
    Test(const int pV) : v(pV) {}

    int GetV() const {
        return PrivateGetV();
    }
};


int main(int argc, const char **argv) {
    queue<int> a;
    a.push(1);
    a.push(2);
    while (!a.empty()) {
        cout << a.front() << endl;
        a.pop();
    }

    stack<int> b;
    b.push(1);
    b.push(2);
    while (!b.empty()) {
        cout << b.top() << endl;
        b.pop();
    }
}
