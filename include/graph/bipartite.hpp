//
// Created by john on 11/11/17.
//

#ifndef ALGS4_BIPARTITE_HPP
#define ALGS4_BIPARTITE_HPP

#include <vector>

#include "graph.hpp"

using namespace std;
using namespace graph;

namespace graph {
    const bool BLACK = false;
    const bool RED = true;

    class BiPartite {
    public:
        BiPartite(Graph &pGraph) : marked(pGraph.V(), false), colors(pGraph.V(), BLACK) {}

    protected:
        vector<bool> marked;
        vector<bool> colors;
        bool isBiPartite = true;
    };

    class DepthFistBipartite : public BiPartite {
    public:
        DepthFistBipartite(Graph &pGraph) : BiPartite(pGraph) {
            for (int s = 0; s < pGraph.V(); s++) {
                if (!marked[s]) DFS(pGraph, s);
            }
        }

        bool IsBiPartite() { return isBiPartite; }

    private:
        void DFS(Graph &pGraph, const int v) {
            marked[v] = true;
            for (int s:pGraph.ADJ(v)) {
                if (!marked[s]) {
                    colors[s] = !colors[v];
                    DFS(pGraph, s);
                } else if (colors[v] == colors[s]) {
                    isBiPartite = false;
                }
            }
        }
    };
}
#endif //ALGS4_BIPARTITE_HPP
