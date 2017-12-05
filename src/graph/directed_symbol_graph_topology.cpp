//
// Created by john on 11/19/17.
//

#include "graph/utils.hpp"
#include "graph/topology.hpp"
#include "graph/symbol_graph.hpp"

using namespace graph;

int main(const int argc, const char **argv) {
    if (argc < 3) {
        cerr << "Usage: executor [test_file_path] [separator]";
        exit(EXIT_FAILURE);
    }

    string pFile = argv[1];
    string pSeparator = argv[2];

    SymbolGraph<DiGraph> sg(pFile, pSeparator);
    DiGraph g = sg.GetGraph();
    Topology<DiGraph> topo(g);

    if (topo.IsDAG()) {
        string lKey;
        for (int v: topo.Order()) {
            sg.Key(v, lKey);
            cout << lKey << endl;
        }
    }
}