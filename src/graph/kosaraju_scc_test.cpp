//
// Created by john on 11/22/17.
//

#include "graph/scc.hpp"
#include "graph/utils.hpp"

using namespace std;
using namespace graph;

int main(const int argc, const char **argv) {
    pair<string, int> cmd = ParseCommandLine(argc, argv);
    cout << "Test File: " << cmd.first << endl;
    cout << "Source: " << cmd.second << endl;

    InStream input(cmd.first);
    DiGraph graph(input);

    KosarajuSCC scc(graph);

    cout << scc.Count() << " Components" << endl;
    for (int id = 0; id < scc.Count(); id ++) {
        for (int v = 0; v < graph.V(); v++) {
            if (scc.Id(v) == id) cout << v << " ";
        }
        cout << endl;
    }
}