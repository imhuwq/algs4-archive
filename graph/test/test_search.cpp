//
// Created by john on 11/9/17.
//

#include <string>
#include <iostream>

#include "utils.hpp"
#include "search.hpp"

using namespace std;
using namespace algs4;

int main(int argc, const char **argv) {
    pair<string, unsigned long> cmd = ParseCommandLine(argc, argv);
    cout << "Test File: " << cmd.first << endl;
    cout << "Source: " << cmd.second << endl;

    InStream input(cmd.first);
    Graph graph(input);
    DepthFirstSearch dfs(graph, cmd.second);
}
