//
// Created by john on 11/19/17.
//

#include "graph/utils.hpp"
#include "graph/symbol_graph.hpp"

using namespace graph;

int main(const int argc, const char **argv) {
    pair<string, int> cmd = ParseCommandLine(argc, argv);
    cout << "Test File: " << cmd.first << endl;
    cout << "Source: " << cmd.second << endl;

    SymbolGraph sg(cmd.first, " ");
    for (const string &key:sg.Keys()) {
        cout << key << ": " << endl;
        for (const string &adjKey:sg.ADJ(key)) {
            cout << "  " << adjKey << endl;
        }
    }
}