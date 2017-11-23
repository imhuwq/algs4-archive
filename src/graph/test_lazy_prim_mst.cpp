//
// Created by john on 11/23/17.
//

#include <vector>

#include "common.hpp"
#include "graph/mst.hpp"
#include "graph/utils.hpp"

using namespace std;
using namespace graph;

int main(const int argc, const char **argv) {
    pair<string, int> cmd = ParseCommandLine(argc, argv);
    cout << "Test File: " << cmd.first << endl;
    cout << "Source: " << cmd.second << endl;

    InStream input(cmd.first);
    EdgeWeightedGraph graph(input);

    LazyPrimMST mst(graph);

    for (Edge &e: mst.Edges()) {
        cout << e.ToString() << endl;
    }
    cout << mst.Weight() << endl;
}