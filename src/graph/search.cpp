//
// Created by john on 11/9/17.
//

#include <string>
#include <iostream>

#include "utils.hpp"
#include "graph/search.hpp"

using namespace std;
using namespace algs4;

int main(int argc, const char **argv) {
    pair<string, int> cmd = ParseCommandLine(argc, argv);
    cout << "Test File: " << cmd.first << endl;
    cout << "Source: " << cmd.second << endl;

    InStream input(cmd.first);
    Graph graph(input);
    DepthFirstSearch dfs(graph, cmd.second);

    for (int v = 0; v < graph.V(); v++) {
        if (dfs.Marked(v)) cout << v << " ";
    }
    cout << endl;

    if (dfs.Count() != graph.V()) cout << "Not ";
    cout << "Connected" << endl;
}
