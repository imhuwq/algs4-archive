//
// Created by john on 12/6/17.
//

#include <cmath>
#include <vector>
#include <string>
#include <iostream>

#include "common.hpp"
#include "graph/spt.hpp"
#include "graph/utils.hpp"

using namespace std;
using namespace graph;

int main(int argc, const char **argv) {
    pair<string, int> cmd = ParseCommandLine(argc, argv);
    cout << "Test File: " << cmd.first << endl;
    cout << "Source: " << cmd.second << endl;

    InStream input(cmd.first);
    int lN;
    input.ReadInt(lN);
    EdgeWeightedDigraph lDigraph(lN);

    vector<string> names;
    string name;
    for (int from = 0; from < lN; from++) {
        input.ReadString(name);
        names.push_back(name);

        double rate;
        for (int to = 0; to < lN; to++) {
            input.ReadDouble(rate);
            lDigraph.AddEdge(make_shared<DirectedEdge>(from, to, -log(rate)));
        }
    }

    BellmanFordSP spt(lDigraph, 0);
    if (spt.HasNegativeCircle()) {
        double stake = 1000;
        for (DiEdgePtr &fEdge: spt.NegativeCircle()) {
            cout << stake << " " << names[fEdge->From()] << " = ";
            stake *= exp(-fEdge->Weight());
            cout << stake << " " << names[fEdge->To()] << endl;
        }
    } else {
        cout << "No arbitrage chance" << endl;
    }
}