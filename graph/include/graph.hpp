//
// Created by john on 11/8/17.
//

#ifndef ALGS4_GRAPH_GRAPH_HPP
#define ALGS4_GRAPH_GRAPH_HPP

#include <vector>
#include <sstream>
#include <iostream>

#include "common.hpp"

using namespace std;
using namespace algs4;

namespace algs4 {
    class Graph {
    private:
        int v;
        int e;
        vector<vector<int>> adj;

    public:
        explicit Graph(const int &pV) : v(pV), e(0), adj(v) {}

        explicit Graph(InStream &pIn) {
            v = pIn.ReadInt();
            int edge = pIn.ReadInt();
            adj.assign(v, {});
            for (int index = 0; index < edge; index++) {
                int v = pIn.ReadInt();
                int w = pIn.ReadInt();
                AddEdge(v, w);
            }
        }

        int V() { return v; }

        int E() { return e; }

        void AddEdge(int v, int w) {
            adj[v].push_back(w);
            adj[w].push_back(v);
            e++;
        }

        vector<int> ADJ(int v) {
            return adj[v];
        }

        string ToString() {
            ostringstream os;
            os << "Graph: " << v << " vertices, " << e << " edges\n";
            for (int index = 0; index < v; index++) {
                os << index << ": ";
                for (int w:ADJ(index)) {
                    os << w << " ";
                }
                os << "\n";
            }
            return os.str();
        }
    };
}

#endif //ALGS4_GRAPH_GRAPH_HPP
