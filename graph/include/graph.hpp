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
        unsigned long v = 0;
        unsigned long e = 0;
        vector<vector<unsigned long>> adj;

    public:
        explicit Graph(const unsigned long &pV) : v(pV), e(0), adj(v) {}

        explicit Graph(InStream &pIn) {
            v = pIn.ReadInt();
            unsigned long edge = pIn.ReadInt();
            adj.assign(v, {});
            for (unsigned long index = 0; index < edge; index++) {
                unsigned long v = pIn.ReadInt();
                unsigned long w = pIn.ReadInt();
                AddEdge(v, w);
            }
        }

        unsigned long V() { return v; }

        unsigned long E() { return e; }

        void AddEdge(unsigned long v, unsigned long w) {
            adj[v].push_back(w);
            adj[w].push_back(v);
            e++;
        }

        vector<unsigned long> ADJ(unsigned long v) {
            return adj[v];
        }

        string ToString() {
            ostringstream os;
            os << "Graph: " << v << " vertices, " << e << " edges\n";
            for (unsigned long index = 0; index < v; index++) {
                os << index << ": ";
                for (unsigned long w:ADJ(index)) {
                    os << w << " ";
                }
                os << "\n";
            }
            return os.str();
        }
    };
}

#endif //ALGS4_GRAPH_GRAPH_HPP
