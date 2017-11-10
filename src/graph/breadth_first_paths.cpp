//
// Created by john on 11/11/17.
//

#include <string>

#include "utils.hpp"
#include "graph/paths.hpp"

using namespace std;
using namespace algs4;


int main(int argc, const char **argv) {
    pair<string, int> cmd = ParseCommandLine(argc, argv);
    cout << "Test File: " << cmd.first << endl;
    cout << "Source: " << cmd.second << endl;

    InStream input(cmd.first);
    Graph graph(input);

    int source = cmd.second;
    BreadthFirstPaths bfp(graph, source);

    for (int v = 0; v < graph.V(); v++) {
        cout << cmd.second << " to " << v << ": ";
        if (bfp.HasPathTo(v)) {
            for (int x:bfp.PathTo(v)) {
                if (x == source) cout << x;
                else cout << "-" << x;
            }
        }
        cout << endl;
    }
}