//
// Created by john on 11/23/17.
//

#ifndef ALGS4_MST_HPP
#define ALGS4_MST_HPP

#include <queue>
#include <vector>
#include <memory>
#include <limits>

#include "sort/heap.hpp"
#include "graph/graph.hpp"
#include "search/union.hpp"

using namespace std;
using namespace sort;
using namespace graph;
using namespace search;

const double DBL_MAX(numeric_limits<double>::max());

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

    class PrimMST {
    private:
        vector<Edge> edgeTo;
        vector<double> distTo;
        vector<bool> marked;
        IndexMinPQ<double> pq;
        double weight = -1.0;

        void Visit(EdgeWeightedGraph &pG, const int pV) {
            marked[pV] = true;
            for (Edge::EdgePtr &edge: pG.ADJ(pV)) {
                int lW = edge->Other(pV);
                if (marked[lW]) continue;
                if (edge->Weight() < distTo[lW]) {
                    edgeTo[lW] = *edge;
                    distTo[lW] = edge->Weight();
                    if (pq.Contains(lW)) pq.Change(lW, edge->Weight());
                    else pq.Insert(lW, edge->Weight());
                }
            }
        }

    public:
        explicit PrimMST(EdgeWeightedGraph &pG) : edgeTo(pG.V()), distTo(pG.V(), DBL_MAX), marked(pG.V(), false), pq(pG.V()) {
            pq.Insert(0, 0.0);
            int lV;
            while (!pq.IsEmpty()) {
                pq.DeleteMinIndex(lV);
                Visit(pG, lV);
            }
        }

        vector<Edge> Edges() {
            return edgeTo;
        }

        double Weight() {
            if (weight < 0) {
                double lWeight = 0.0;
                for (auto &edge:edgeTo) {
                    lWeight += edge.Weight();
                }
                weight = lWeight;
            }
            return weight;
        }
    };

    class KruskalMST {
    private:
        MinPQ<Edge> pq;
        WeightedQuickUnionUF uf;
        vector<Edge> edges;
        double weight;

    public:
        explicit KruskalMST(EdgeWeightedGraph &pG) : uf(pG.V()), pq(pG.EdgesObj()) {
            Edge lMinEdge = Edge();
            while (!pq.IsEmpty() and edges.size() < pG.V() - 1) {
                pq.DeleteMin(lMinEdge);
                int lV = lMinEdge.Either();
                int lW = lMinEdge.Other(lV);
                if (uf.Connected(lV, lW)) continue;
                uf.Union(lV, lW);
                edges.push_back(lMinEdge);
                weight += lMinEdge.Weight();
            }
        }

        vector<Edge> Edges() { return edges; }

        double Weight() { return weight; }
    };
}

#endif //ALGS4_MST_HPP
