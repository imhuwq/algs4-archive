//
// Created by john on 12/20/17.
//

#include <vector>
#include <string>

#include "string/lsd.h"

using namespace std;
using namespace string_algs;

int main(int argc, const char **argv) {
    vector<string> strings = {"abcde", "123de", "abcd1"};
    LSD::Sort(strings, 5);

    for (const string &str:strings) {
        cout << str << endl;
    }
}