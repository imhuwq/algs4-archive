//
// Created by john on 11/11/17.
//

#ifndef ALGS4_COMPONENTS_HPP
#define ALGS4_COMPONENTS_HPP

#include <vector>
#include <iostream>

#include "graph.hpp"

using namespace std;
using namespace algs4;

namespace algs4 {
    class Components {
    public:
        explicit Components(Graph &pGraph) : id(pGraph.V(), -1) {}

        bool IsConnected(const int &v, const int &w) {
            return id[v] == id[w];
        }

        int Id(int v) {
            if (v > id.size() - 1) {
                cout << v << " is not in the graph" << endl;
                return -1;
            }
            return id[v];
        }

        int Count() { return count; }

    protected:
        vector<int> id;
        int count = 0;
    };

    class DepthFirstComponents : public Components {
    public:
        explicit DepthFirstComponents(Graph &pGraph) : Components(pGraph) {
            for (int w = 0; w < pGraph.V(); w++) {
                if (id[w] == -1) {
                    DFS(pGraph, w);
                    count++;
                }
            }
        }

    private:
        void DFS(Graph &pGraph, const int &v) {
            id[v] = count;
            for (int w:pGraph.ADJ(v)) {
                if (id[w] == -1) DFS(pGraph, w);
            }
        }

    };
}


#endif //ALGS4_COMPONENTS_HPP
