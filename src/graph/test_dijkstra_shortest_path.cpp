//
// Created by john on 12/5/17.
//

#include <vector>
#include <string>
#include <iostream>

#include "graph/graph.hpp"
#include "graph/spt.hpp"
#include "graph/utils.hpp"

using namespace std;
using namespace graph;

int main(int argc, const char **argv) {
    pair<string, int> cmd = ParseCommandLine(argc, argv);
    cout << "Test File: " << cmd.first << endl;
    cout << "Source: " << cmd.second << endl;

    InStream input(cmd.first);
    EdgeWeightedDigraph lEWDiGraph(input);

    DijkstraSP dijkstra(lEWDiGraph, cmd.second);

    for (int lDestination = 0; lDestination < lEWDiGraph.V(); lDestination++) {
        double lDistance = 0.0;
        if (dijkstra.HasPathTo(lDestination)) {
            cout << "Path from " << cmd.second << " to " << lDestination << ": ";
            for (DiEdgePtr &fEdge: dijkstra.PathTo(lDestination)) {
                lDistance += fEdge->Weight();
                cout << "[" << fEdge->ToString() << "] ";
            }
            cout << endl << "  Total Distance: " << lDistance << endl << endl;
        }
    }

}