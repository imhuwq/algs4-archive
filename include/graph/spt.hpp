//
// Created by john on 12/5/17.
//

#ifndef ALGS4_SPT_HPP
#define ALGS4_SPT_HPP

#include <deque>
#include <vector>
#include <limits>

#include "graph.hpp"
#include "topology.hpp"
#include "sort/heap.hpp"

using namespace std;
using namespace sort;
using namespace graph;

namespace graph {
    const static double INF(numeric_limits<double>::infinity());

    class SPT {
    protected:
        vector<double> distTo;
        vector<DiEdgePtr> edgeTo;
    public:
        SPT(EdgeWeightedDigraph &pGraph, const int pS) : distTo((unsigned long) pGraph.V(), INF),
                                                         edgeTo((unsigned long) pGraph.V(), nullptr) {}

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

    class AcyclicSP : public SPT {
    private:
        void Relax(EdgeWeightedDigraph &pGraph, const int pV) {
            for (DiEdgePtr &fEdge: pGraph.ADJ(pV)) {
                const int fW = fEdge->To();
                double fWeight = this->distTo[pV] + fEdge->Weight();
                if (this->distTo[fW] > fWeight) {
                    this->distTo[fW] = fWeight;
                    this->edgeTo[fW] = fEdge;
                }
            }
        }

    public:
        AcyclicSP(EdgeWeightedDigraph &pGraph, const int pS) : SPT(pGraph, pS) {
            this->distTo[pS] = 0;
            Topology<EdgeWeightedDigraph> lTopology(pGraph);
            for (int fV: lTopology.Order()) Relax(pGraph, fV);
        }
    };

    class AcyclicLP {
    private:
        vector<double> distTo;
        vector<DiEdgePtr> edgeTo;

        void Relax(EdgeWeightedDigraph &pGraph, const int pV) {
            for (DiEdgePtr &fEdge: pGraph.ADJ(pV)) {
                const int fW = fEdge->To();
                double fWeight = distTo[pV] + fEdge->Weight();
                if (distTo[fW] < fWeight) {
                    distTo[fW] = fWeight;
                    edgeTo[fW] = fEdge;
                }
            }
        }

    public:
        AcyclicLP(EdgeWeightedDigraph &pGraph, const int pS) : distTo((unsigned long) pGraph.V(), -INF),
                                                               edgeTo((unsigned long) pGraph.V(), nullptr) {
            this->distTo[pS] = 0;
            Topology<EdgeWeightedDigraph> lTopology(pGraph);
            for (int fV: lTopology.Order()) Relax(pGraph, fV);
        }

        double DistTo(const int pV) {
            return distTo[pV];
        }
    };
}


#endif //ALGS4_SPT_HPP
