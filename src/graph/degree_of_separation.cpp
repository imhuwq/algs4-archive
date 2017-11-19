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
    if (argc < 4) {
        cerr << "Usage: executor [file_path] [separator] [source] [destination]";
        exit(EXIT_FAILURE);
    }

    string pFileName = argv[1];
    string pSeparator = argv[2];
    string pSource = argv[3];
    string pDestination = argv[4];

    SymbolGraph sg(pFileName, pSeparator);

    if (!sg.Contains(pSource)) {
        cerr << "Source: " << pSource << " not in database";
        exit(EXIT_FAILURE);
    }
    int lSourceIndex;
    sg.Index(pSource, lSourceIndex);

    if (!sg.Contains(pDestination)) {
        cerr << "Destination: " << pDestination << " not in database";
        exit(EXIT_FAILURE);
    }
    int lDestinationIndex;
    sg.Index(pDestination, lDestinationIndex);

    Graph g = sg.GetGraph();
    BreadthFirstPaths bfp(g, lSourceIndex);
    if (bfp.HasPathTo(lDestinationIndex)) {
        cout << "From " << pSource << " to " << pDestination << ": " << endl;
        string fVertex;
        for (const int &fVertexIndex:bfp.PathTo(lDestinationIndex)) {
            sg.Key(fVertexIndex, fVertex);
            cout << "  " << fVertex << endl;
        }
    } else {
        cout << "From " << pSource << "to " << pDestination << " Does not Exist" << endl;
    }
}
