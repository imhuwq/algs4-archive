//
// Created by john on 11/11/17.
//

#include <string>
#include <vector>

#include "graph/utils.hpp"
#include "graph/components.hpp"

using namespace std;
using namespace graph;


int main(int argc, const char **argv) {
    pair<string, int> cmd = ParseCommandLine(argc, argv);
    cout << "Test File: " << cmd.first << endl;
    cout << "Source: " << cmd.second << endl;

    InStream input(cmd.first);
    Graph graph(input);

    int source = cmd.second;
    DepthFirstComponents dfc(graph);

    int lCCount = dfc.Count();
    cout << lCCount << " components" << endl;

    vector<vector<int>> lComponents;
    for (int i = 0; i < lCCount; i++) {
        lComponents.push_back({});
    }

    for (int v = 0; v < graph.V(); v++) {
        lComponents[dfc.Id(v)].push_back(v);
    }

    for (vector<int> component:lComponents) {
        for (int v:component) {
            cout << v << " ";
        }
        cout << endl;
    }
}