//
// Created by john on 11/21/17.
//

#ifndef ALGS4_TOPOLOGY_HPP
#define ALGS4_TOPOLOGY_HPP

#include <vector>
#include <deque>

#include "graph.hpp"

using namespace std;
using namespace graph;

namespace graph {
    class DepthFirstOrder {
    private:
        vector<int> marked;
        vector<int> pre;
        vector<int> post;
        deque<int> reversPost;

        void DFS(DiGraph &pDiGraph, const int pV) {
            marked[pV] = true;
            pre.push_back(pV);
            for (int lW:pDiGraph.ADJ(pV)) {
                if (!marked[lW]) DFS(pDiGraph, lW);
            }
            post.push_back(pV);
            reversPost.push_front(pV);
        }

    public:
        DepthFirstOrder(DiGraph &pDiGraph) : marked(pDiGraph.V(), false),
                                             pre(pDiGraph.V()),
                                             post(pDiGraph.V()),
                                             reversPost(pDiGraph.V()) {
            for (int v = 0; v < pDiGraph.V(); v++) {
                if (!marked[v]) DFS(pDiGraph, v);
            }
        }

        vector<int> Pre() {
            return pre;
        }

        vector<int> Post() {
            return post;
        }

        vector<int> ReversePost() {
            return vector<int>(reversPost.begin(), reversPost.end());
        }
    };

    class Topology {
    private:
        bool hasCycle;
        vector<bool> marked;
        deque<int> order;
        vector<int> edgeTo;
        vector<bool> onStack;

        void DFS(DiGraph &pDiGraph, const int pV) {
            marked[pV] = true;
            onStack[pV] = true;

            for (int lW: pDiGraph.ADJ(pV)) {
                if (hasCycle) return;
                if (!marked[lW]) {
                    edgeTo[lW] = pV;
                    DFS(pDiGraph, lW);
                } else if (onStack[lW]) {
                    hasCycle = true;
                    return;
                }
            }

            onStack[pV] = false;
            order.push_front(pV);
        }

    public:
        explicit Topology(DiGraph &pDiGraph) : marked(pDiGraph.V(), false), onStack(pDiGraph.V(), false), edgeTo(pDiGraph.V(), -1), hasCycle(false) {
            for (int v = 0; v < pDiGraph.V(); v++) {
                if (!marked[v]) DFS(pDiGraph, v);
            }

            if (hasCycle) order = deque<int>();
        }

        bool IsDAG() {
            return !hasCycle;
        }

        vector<int> Order() {
            return vector<int>(order.begin(), order.end());
        }

        bool PathTo(const int pTarget, vector<int> &rPath) {
            if (hasCycle) return false;
            deque<int> lDeque;
            for (int x = pTarget; x != -1; x = edgeTo[x]) {
                lDeque.push_front(x);
            }
            rPath = vector<int>(lDeque.begin(), lDeque.end());
            return true;
        }
    };
}
#endif //ALGS4_TOPOLOGY_HPP
