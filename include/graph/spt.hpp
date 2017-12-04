//
// Created by john on 12/5/17.
//

#ifndef ALGS4_SPT_HPP
#define ALGS4_SPT_HPP

#include <deque>
#include <vector>
#include <limits>

#include "graph.hpp"
#include "sort/heap.hpp"

using namespace std;
using namespace sort;
using namespace graph;

namespace graph {
    const static double INF(numeric_limits<double>::infinity());

    class SPT {
    protected:
        EdgeWeightedDigraph &graph;
        int source;
        vector<double> distTo;
        vector<DiEdgePtr> edgeTo;
    public:
        SPT(EdgeWeightedDigraph &pGraph, const int pS) : graph(pGraph), source(pS),
                                                         distTo((unsigned long)graph.V(), INF),
                                                         edgeTo((unsigned long)pGraph.V(), nullptr) {}

        double DistTo(const int pV) {
            return this->distTo[pV];
        }

        bool HasPathTo(const int pV) {
            return this->distTo[pV] < INF;
        }

        vector<DiEdgePtr> PathTo(const int pV) {
            vector<DiEdgePtr> rEdges;

            deque<DiEdgePtr> lEdges;
            if (HasPathTo(pV)) {
                for (DiEdgePtr fEdge = this->edgeTo[pV]; fEdge != nullptr; fEdge = this->edgeTo[fEdge->From()]) {
                    lEdges.push_front(fEdge);
                }
            }

            rEdges.assign(lEdges.begin(), lEdges.end());
            return rEdges;
        }
    };

    class DijkstraSP : public SPT {
    private:
        IndexMinPQ<double> pq;

        void Relax(EdgeWeightedDigraph &pGraph, const int pV) {
            for (DiEdgePtr fEdge: pGraph.ADJ(pV)) {
                int lW = fEdge->To();
                double t1 = this->distTo[lW];
                double t2 = this->distTo[pV];
                double weight = fEdge->Weight();
                if (this->distTo[lW] > this->distTo[pV] + weight) {
                    this->distTo[lW] = this->distTo[pV] + weight;
                    this->edgeTo[lW] = fEdge;
                    if (pq.Contains(lW)) pq.Change(lW, this->distTo[lW]);
                    else pq.Insert(lW, this->distTo[lW]);
                }
            }
        }

    public:
        DijkstraSP(EdgeWeightedDigraph &pGraph, const int pS) : SPT(pGraph, pS), pq(pGraph.V()) {
            this->distTo[pS] = 0.0;
            pq.Insert(pS, 0.0);
            int lV;
            while (!pq.IsEmpty()) {
                pq.DeleteMinIndex(lV);
                Relax(pGraph, lV);
            }
        }
    };
}


#endif //ALGS4_SPT_HPP
