//
// Created by john on 11/19/17.
//

#include "graph/utils.hpp"
#include "graph/symbol_graph.hpp"

using namespace graph;

int main(const int argc, const char **argv) {
    if (argc < 3) {
        cerr << "Usage: executor [test_file_path] [separator]";
        exit(EXIT_FAILURE);
    }

    string pFile = argv[1];
    string pSeparator = argv[2];

    SymbolGraph sg(pFile, pSeparator);
    for (const string &key:sg.Keys()) {
        cout << key << ": " << endl;
        for (const string &adjKey:sg.ADJ(key)) {
            cout << "  " << adjKey << endl;
        }
    }
}