//
// Created by john on 11/11/17.
//

#include <string>
#include <vector>

#include "graph/utils.hpp"
#include "graph/cycle.hpp"

using namespace std;
using namespace graph;

int main(int argc, const char **argv) {
    pair<string, int> cmd = ParseCommandLine(argc, argv);
    cout << "Test File: " << cmd.first << endl;
    cout << "Source: " << cmd.second << endl;

    InStream input(cmd.first);
    Graph graph(input);

    int source = cmd.second;
    DepthFirstCycle dfc(graph);

    cout << graph.ToString() << endl;

    cout << "Graph ";
    if (!dfc.HasCycle()) cout << "NOT ";
    cout << "Has Cycle" << endl;
}