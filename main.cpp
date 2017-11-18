#include <string>
#include <vector>
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
    string a = ",1,2,3, 5,,,,,";
    vector<string> b = SplitString(a, ",");
    for (string &s:b) {
        cout << s << endl;
    }
}
