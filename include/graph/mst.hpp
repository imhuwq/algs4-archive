//
// Created by john on 11/23/17.
//

#ifndef ALGS4_MST_HPP
#define ALGS4_MST_HPP

#include <queue>
#include <vector>
#include <memory>

#include "sort/heap.hpp"
#include "graph/graph.hpp"

using namespace std;
using namespace sort;
using namespace graph;

namespace graph {
    class LazyPrimMST {
    private:
        vector<bool> marked;
        vector<Edge> mst;
        MinPQ<Edge> pq;
        double weight;

        void Visit(EdgeWeightedGraph &pG, const int pV) {
            marked[pV] = true;
            for (Edge::EdgePtr &e: pG.ADJ(pV)) {
                pq.Insert(*e);
            }
        }

    public:
        explicit LazyPrimMST(EdgeWeightedGraph &pG) : marked(pG.V()), weight(0.0) {
            Visit(pG, 0);
            Edge edge;
            while (!pq.IsEmpty()) {
                pq.DeleteMin(edge);
                int v = edge.Either(), w = edge.Other(v);
                if (marked[v] and marked[w]) continue;
                mst.push_back(edge);
                weight += edge.Weight();
                if (!marked[v]) Visit(pG, v);
                if (!marked[w]) Visit(pG, w);
            }
        }

        vector<Edge> Edges() {
            return mst;
        }

        double Weight() {
            return weight;
        }
    };
}

#endif //ALGS4_MST_HPP
