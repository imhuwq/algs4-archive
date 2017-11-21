//
// Created by john on 11/11/17.
//

#ifndef ALGS4_CYCLE_HPP
#define ALGS4_CYCLE_HPP

#include <vector>
#include <deque>

#include "graph.hpp"

using namespace std;
using namespace graph;

namespace graph {
    class Cycle {
    private:
        bool hasCycle = false;
        vector<bool> marked;
    public:
        explicit Cycle(Graph &pGraph) : marked(pGraph.V(), false) {
            for (int s = 0; s < pGraph.V(); s++) {
                if (!marked[s]) {
                    DFS(pGraph, s, s);
                }
            }
        }

        bool HasCycle() { return hasCycle; }

        void DFS(Graph &pGraph, const int v, const int w) {
            marked[v] = true;
            for (int s:pGraph.ADJ(v)) {
                if (!marked[s]) DFS(pGraph, s, v);
                else if (s != w) hasCycle = true;
            }
        }
    };


    class DirectedCycle {
    private:
        vector<bool> marked;
        vector<int> edgeTo;
        vector<bool> onStack;
        deque<int> cycle;


        void DFS(DiGraph &pDigraph, const int v) {
            marked[v] = true;
            onStack[v] = true;
            for (int w: pDigraph.ADJ(v)) {
                if (HasCycle()) return;
                else if (!marked[w]) {
                    edgeTo[w] = v;
                    DFS(pDigraph, w);
                } else if (onStack[w]) {
                    for (int x = v; x != w; x = edgeTo[x]) {
                        cycle.push_front(x);
                    }
                    cycle.push_front(w);
                    cycle.push_front(v);
                }
            }

            onStack[v] = false;
        }

    public:
        explicit DirectedCycle(DiGraph &pDigraph) : marked(pDigraph.V()), edgeTo(pDigraph.V()), onStack(pDigraph.V()) {
            for (int v = 0; v < pDigraph.V(); v++) {
                if (!marked[v]) DFS(pDigraph, v);
            }
        }

        bool HasCycle() {
            return cycle.size() != 0;
        }

        vector<int> Cycle() {
            return vector<int>(cycle.begin(), cycle.end());
        }
    };
}

#endif //ALGS4_CYCLE_HPP
