//
// Created by john on 11/19/17.
//

#include <string>

#include "common.hpp"
#include "graph/paths.hpp"
#include "graph/symbol_graph.hpp"

using namespace std;
using namespace graph;

int main(const int argc, const char **argv) {
    if (argc < 3) {
        cerr << "Usage: executor [file_path] [separator] [source]";
        exit(EXIT_FAILURE);
    }

    string pFileName = argv[1];
    string pSeparator = argv[2];
    string pSource = argv[3];

    SymbolGraph sg(pFileName, pSeparator);

    if (!sg.Contains(pSource)) {
        cerr << "Source: " << pSource << " not in database";
        exit(EXIT_FAILURE);
    }

    int lSourceIndex;
    sg.Index(pSource, lSourceIndex);
    Graph g = sg.GetGraph();
    BreadthFirstPaths bfp(g, lSourceIndex);

    vector<string> lDestinations = sg.Keys();
    int lDestinationIndex;
    for (const string &fDestination:lDestinations) {
        if (fDestination == pSource) continue;
        sg.Index(fDestination, lDestinationIndex);
        if (bfp.HasPathTo(lDestinationIndex)) {
            cout << "From " << pSource << " to " << fDestination << ": " << endl;
            string fVertex;
            for (const int &fVertexIndex:bfp.PathTo(lDestinationIndex)) {
                sg.Key(fVertexIndex, fVertex);
                cout << "  " << fVertex << endl;
            }
        } else {
            cout << "From " << pSource << "to " << fDestination << " Does not Exist" << endl;
        }
    }
}
