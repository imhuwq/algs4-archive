//
// Created by john on 11/11/17.
//

#include <string>

#include "graph/utils.hpp"
#include "graph/bipartite.hpp"

using namespace std;
using namespace graph;

int main(int argc, const char **argv) {
    pair<string, int> cmd = ParseCommandLine(argc, argv);
    cout << "Test File: " << cmd.first << endl;
    cout << "Source: " << cmd.second << endl;

    InStream input(cmd.first);
    Graph graph(input);

    int source = cmd.second;
    DepthFistBipartite dfc(graph);

    cout << graph.ToString() << endl;

    cout << "Graph is ";
    if (!dfc.IsBiPartite()) cout << "NOT ";
    cout << "Bipartite" << endl;
}