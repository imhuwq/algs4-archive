//
// Created by john on 11/11/17.
//

#ifndef ALGS4_CYCLE_HPP
#define ALGS4_CYCLE_HPP

#include <vector>

#include "graph.hpp"

using namespace std;
using namespace algs4;

namespace algs4 {
    class Cycle {
    public:
        Cycle(Graph &pGraph) : marked(pGraph.V(), false) {}

        bool HasCycle() { return hasCycle; }

    protected:
        bool hasCycle = false;
        vector<bool> marked;
    };

    class DepthFirstCycle : public Cycle {
    public:
        DepthFirstCycle(Graph &pGraph) : Cycle(pGraph) {
            for (int s = 0; s < pGraph.V(); s++) {
                if (!marked[s]) {
                    DFS(pGraph, s, s);
                }
            }
        }

    private:
        void DFS(Graph &pGraph, const int v, const int w) {
            marked[v] = true;
            for (int s:pGraph.ADJ(v)) {
                if (!marked[s]) DFS(pGraph, s, v);
                else if (s != w) hasCycle = true;
            }
        }
    };
}

#endif //ALGS4_CYCLE_HPP
