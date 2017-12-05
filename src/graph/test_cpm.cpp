//
// Created by john on 12/5/17.
//

#include <vector>
#include <string>
#include <iostream>

#include "common.hpp"
#include "graph/cpm.h"
#include "graph/utils.hpp"

using namespace std;
using namespace graph;

int main(int argc, const char **argv) {
    pair<string, int> cmd = ParseCommandLine(argc, argv);
    cout << "Test File: " << cmd.first << endl;
    cout << "Source: " << cmd.second << endl;

    InStream input(cmd.first);

    CriticalPathMethod cpm(input);

    cout << cpm.ToString() << endl;
}
