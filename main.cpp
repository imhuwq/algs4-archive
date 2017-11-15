#include <string>
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
    Test t(12);
    cout << t.GetV() << endl;

    const Test t2(22);
    cout << t2.GetV() << endl;
}
