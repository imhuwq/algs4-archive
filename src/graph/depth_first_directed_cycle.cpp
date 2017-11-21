//
// Created by john on 11/21/17.
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
    DiGraph graph(input);

    int source = cmd.second;
    DirectedCycle dfc(graph);

    cout << graph.ToString() << endl;

    cout << "Graph ";
    if (!dfc.HasCycle()) cout << "NOT ";
    cout << "Has Cycle" << endl;

    if (dfc.HasCycle()) {
        for (int v:dfc.Cycle()) {
            cout << v << " ";
        }
    }
    cout << endl;
}