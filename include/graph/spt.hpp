//
// Created by john on 12/5/17.
//

#ifndef ALGS4_SPT_HPP
#define ALGS4_SPT_HPP

#include <queue>
#include <deque>
#include <vector>
#include <limits>

#include "graph.hpp"
#include "cycle.hpp"
#include "topology.hpp"
#include "sort/heap.hpp"

using namespace std;
using namespace sort;
using namespace graph;

namespace graph {
    const static double INF(numeric_limits<double>::infinity());

    class SPT {
    public:
        vector<double> distTo;
        vector<DiEdgePtr> edgeTo;

        SPT(EdgeWeightedDigraph &pGraph, const int pS) : distTo((unsigned long) pGraph.V(), INF),
                                                         edgeTo((unsigned long) pGraph.V(), nullptr) {}

        double DistTo(const int pV) {
            return distTo[pV];
        }

        bool HasPathTo(const int pV) {
            return distTo[pV] < INF;
        }

        vector<DiEdgePtr> PathTo(const int pV) {
            vector<DiEdgePtr> rEdges;

            deque<DiEdgePtr> lEdges;
            if (HasPathTo(pV)) {
                for (DiEdgePtr fEdge = edgeTo[pV]; fEdge != nullptr; fEdge = edgeTo[fEdge->From()]) {
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
                if (distTo[lW] > distTo[pV] + weight) {
                    distTo[lW] = distTo[pV] + weight;
                    edgeTo[lW] = fEdge;
                    if (pq.Contains(lW)) pq.Change(lW, distTo[lW]);
                    else pq.Insert(lW, distTo[lW]);
                }
            }
        }

    public:
        DijkstraSP(EdgeWeightedDigraph &pGraph, const int pS) : SPT(pGraph, pS), pq(pGraph.V()) {
            distTo[pS] = 0.0;
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
                double fWeight = distTo[pV] + fEdge->Weight();
                if (distTo[fW] > fWeight) {
                    distTo[fW] = fWeight;
                    edgeTo[fW] = fEdge;
                }
            }
        }

    public:
        AcyclicSP(EdgeWeightedDigraph &pGraph, const int pS) : SPT(pGraph, pS) {
            distTo[pS] = 0;
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
            distTo[pS] = 0;
            Topology<EdgeWeightedDigraph> lTopology(pGraph);
            for (int fV: lTopology.Order()) Relax(pGraph, fV);
        }

        double DistTo(const int pV) {
            return distTo[pV];
        }
    };

    class BellmanFordSP : public SPT {
    private:
        vector<bool> onQ;
        queue<int> qu;
        int cost;
        vector<DiEdgePtr> circle;

        void FindNegativeCircle() {
            EdgeWeightedDigraph lGraph(edgeTo.size());
            for (DiEdgePtr fEdge: edgeTo) {
                if (fEdge != nullptr) lGraph.AddEdge(fEdge);
            }

            DirectedCycle<EdgeWeightedDigraph> lCycle(lGraph);

            circle = lCycle.WightedCycle();
        }

        void Relax(EdgeWeightedDigraph &pGraph, const int pV) {
            for (DiEdgePtr fEdge: pGraph.ADJ(pV)) {
                int fW = fEdge->To();
                double fWeight = distTo[pV] + fEdge->Weight();
                if (distTo[fW] > fWeight) {
                    distTo[fW] = fWeight;
                    edgeTo[fW] = fEdge;

                    if (!onQ[fW]) {
                        qu.push(fW);
                        onQ[fW] = true;
                    }
                }

                if (++cost % pGraph.V() == 0) {
                    FindNegativeCircle();
                }
            }
        }


    public:
        BellmanFordSP(EdgeWeightedDigraph &pGraph, const int pS) : SPT(pGraph, pS), onQ(pGraph.V(), false), cost(0) {
            distTo[pS] = 0;
            qu.push(pS);
            onQ[pS] = true;
            while (!qu.empty() and !HasNegativeCircle()) {
                int fV = qu.front();
                qu.pop();
                onQ[fV] = false;
                Relax(pGraph, fV);
            }
        }

        bool HasNegativeCircle() {
            return !circle.empty();
        }

        vector<DiEdgePtr> NegativeCircle() {
            return circle;
        }
    };
}


#endif //ALGS4_SPT_HPP
