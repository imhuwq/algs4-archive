//
// Created by john on 11/21/17.
//

#include <vector>
#include <string>

#include "graph/utils.hpp"
#include "graph/topology.hpp"

using namespace std;
using namespace graph;

int main(const int argc, const char **argv) {
    pair<string, int> cmd = ParseCommandLine(argc, argv);
    cout << "Test File: " << cmd.first << endl;
    cout << "Source: " << cmd.second << endl;

    InStream input(cmd.first);
    DiGraph graph(input);

    int source = cmd.second;
    Topology topo(graph);

    cout << graph.ToString() << endl;

    cout << "Graph ";
    if (topo.IsDAG()) cout << "NOT ";
    cout << "Has Cycle" << endl;

    if (topo.IsDAG()) {
        for (int v:topo.Order()) {
            cout << v << " ";
        }
    }
    cout << endl;
}