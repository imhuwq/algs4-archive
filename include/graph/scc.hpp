//
// Created by john on 11/21/17.
//

#ifndef ALGS4_SCC_HPP
#define ALGS4_SCC_HPP

#include <vector>

#include "graph.hpp"
#include "cycle.hpp"
#include "topology.hpp"

using namespace std;
using namespace graph;

namespace graph {
    class KosarajuSCC {
    private:
        vector<bool> marked;
        vector<int> id;
        int count;

        void DFS(DiGraph &pDiGraph, const int pV) {
            marked[pV] = true;
            id[pV] = count;
            for (int w: pDiGraph.ADJ(pV)) {
                if (!marked[w]) DFS(pDiGraph, w);
            }
        }

    public:
        explicit KosarajuSCC(DiGraph &pDiGraph) : marked(pDiGraph.V(), false), id(pDiGraph.V(), -1) {
            DiGraph rG = pDiGraph.Reverse();
            DepthFirstOrder order(rG);
            for (int s: order.ReversePost()) {
                if (!marked[s]) {
                    DFS(pDiGraph, s);
                    count++;
                }
            }
        }

        bool IsStronglyConnected(const int v, const int w) {
            return id[v] == id[w];
        }

        int Id(const int v) {
            if (v > id.size()) return -1;
            return id[v];
        }

        int Count() {
            return count;
        }
    };
}

#endif //ALGS4_SCC_HPP
