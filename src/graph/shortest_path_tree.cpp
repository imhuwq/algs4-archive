//
// Created by john on 12/4/17.
//

#include <vector>
#include <string>
#include <iostream>

#include "graph/graph.hpp"
#include "graph/utils.hpp"

using namespace std;
using namespace graph;

int main(int argc, const char **argv) {
    pair<string, int> cmd = ParseCommandLine(argc, argv);
    cout << "Test File: " << cmd.first << endl;
    cout << "Source: " << cmd.second << endl;

    InStream input(cmd.first);
    EdgeWeightedDigraph lEWDiGraph(input);

    cout << lEWDiGraph.ToString() << endl;
}