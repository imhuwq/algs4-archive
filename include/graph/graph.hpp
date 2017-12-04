//
// Created by john on 11/8/17.
//

#ifndef ALGS4_GRAPH_GRAPH_HPP
#define ALGS4_GRAPH_GRAPH_HPP

#include <memory>
#include <vector>
#include <sstream>
#include <iostream>

#include "common.hpp"

using namespace std;

namespace graph {
    class Graph {
    private:
        int v = 0;
        int e = 0;
        vector<vector<int>> adj;

    public:
        Graph() = default;

        explicit Graph(const int &pV) : v(pV), e(0), adj(v) {}

        explicit Graph(InStream &pIn) {
            pIn.ReadInt(v);
            int edge;
            pIn.ReadInt(edge);
            adj.assign(v, {});

            int v, w;
            for (int index = 0; index < edge; index++) {
                pIn.ReadInt(v);
                pIn.ReadInt(w);
                AddEdge(v, w);
            }
        }

        int V() { return v; }

        int E() { return e; }

        void AddEdge(int v, int w) {
            adj[v].push_back(w);
            adj[w].push_back(v);
            e++;
        }

        vector<int> ADJ(int pV) {
            if (pV > v) {
                cerr << pV << " is out of the digraph" << endl;
                exit(EXIT_FAILURE);
            }
            return adj[pV];
        }

        string ToString() {
            ostringstream os;
            os << "Graph: " << v << " vertices, " << e << " edges\n";
            for (int index = 0; index < v; index++) {
                os << index << ": ";
                for (int w:ADJ(index)) {
                    os << w << " ";
                }
                os << "\n";
            }
            return os.str();
        }
    };

    class DiGraph {
    private:
        int v = 0;
        int e = 0;
        vector<vector<int>> adj;

    public:
        DiGraph() = default;

        explicit DiGraph(const int pV) : v(pV), e(0), adj(pV) {}

        explicit DiGraph(InStream &pIn) {
            pIn.ReadInt(v);
            int edge;
            pIn.ReadInt(edge);
            adj.assign(v, {});

            int v, w;
            for (int index = 0; index < edge; index++) {
                pIn.ReadInt(v);
                pIn.ReadInt(w);
                AddEdge(v, w);
            }
        }

        int V() { return v; }

        int E() { return e; }

        void AddEdge(const int pV, const int pW) {
            adj[pV].push_back(pW);
            e++;
        }

        vector<int> ADJ(const int pV) {
            if (pV > v) {
                cerr << pV << " is out of the digraph" << endl;
                exit(EXIT_FAILURE);
            }
            return adj[pV];
        }

        string ToString() {
            ostringstream os;
            os << "DiGraph: " << v << " vertices, " << e << " edges" << endl;
            for (int index = 0; index < v; index++) {
                os << index << ": ";
                for (int w:ADJ(index)) {
                    os << w << " ";
                }
                os << "\n";
            }
            return os.str();
        }

        DiGraph Reverse() {
            DiGraph rGraph(v);
            for (int index = 0; index < v; index++) {
                for (int w: ADJ(index)) {
                    rGraph.AddEdge(w, index);
                }
            }
            return rGraph;
        }
    };

    class Edge {
    private:
        int v;
        int w;
        double weight;

    public:
        typedef shared_ptr<Edge> EdgePtr;

        Edge() : v(0), w(0), weight(0.0) {};

        Edge(const int pV, const int pW, const double pWeight) : v(pV), w(pW), weight(pWeight) {}

        int Either() { return v; }

        int Other(const int pV) {
            if (pV == v) return w;
            else if (pV == w) return v;
            throw runtime_error("vertex is not on the edge");
        }

        double Weight() { return weight; }

        string ToString() {
            ostringstream rStr;
            rStr << "[" << v << "-" << w << "," << weight << "]";
            return rStr.str();
        }

        bool operator==(const Edge &pEdge) {
            return this->weight == pEdge.weight;
        }

        bool operator!=(const Edge &pEdge) {
            return !(*this == pEdge);
        }

        bool operator>(const Edge &pEdge) {
            return this->weight > pEdge.weight;
        }

        bool operator<(const Edge &pEdge) {
            return !(*this > pEdge);
        }

        bool operator>=(const Edge &pEdge) {
            return (*this > pEdge) or (*this == pEdge);
        }

        bool operator<=(const Edge &pEdge) {
            return (*this < pEdge) or (*this == pEdge);
        }
    };

    class EdgeWeightedGraph {
        using EdgePtr = Edge::EdgePtr;
    private:
        int v = 0;
        int e = 0;
        vector<vector<EdgePtr>> adj;

    public:
        explicit EdgeWeightedGraph(const int pV) : v(pV), e(0), adj(0) {}

        explicit EdgeWeightedGraph(InStream &pIn) {
            pIn.ReadInt(v);
            e = 0;
            int edge;
            pIn.ReadInt(edge);
            adj.assign(v, {});

            int v, w;
            double weight;
            for (int index = 0; index < edge; index++) {
                pIn.ReadInt(v);
                pIn.ReadInt(w);
                pIn.ReadDouble(weight);
                AddEdge(v, w, weight);
            }
        }

        void AddEdge(const int pV, const int pW, const double pWeight) {
            EdgePtr lEdge = make_shared<Edge>(pV, pW, pWeight);
            adj[pV].push_back(lEdge);
            adj[pW].push_back(lEdge);
            e++;
        }

        void AddEdge(const EdgePtr &pEdge) {
            int lV = pEdge->Either();
            int lW = pEdge->Other(lV);
            adj[lV].push_back(pEdge);
            adj[lW].push_back(pEdge);
            e++;
        }

        int V() {
            return v;
        }

        int E() {
            return e;
        }

        vector<EdgePtr> ADJ(const int pV) {
            return adj[pV];
        }

        vector<EdgePtr> Edges() {
            vector<EdgePtr> rEdges;
            for (int fV = 0; fV < v; fV++) {
                for (EdgePtr &edge:ADJ(fV)) {
                    if (edge->Other(fV) > fV) rEdges.push_back(edge);
                }
            }
            return rEdges;
        }

        vector<Edge> EdgesObj() {
            vector<Edge> rEdges;
            for (int fV = 0; fV < v; fV++) {
                for (EdgePtr &edge:ADJ(fV)) {
                    if (edge->Other(fV) > fV) rEdges.push_back(*edge);
                }
            }
            return rEdges;
        }
    };

    class DirectedEdge {
    private:
        int from;
        int to;
        double weight;
    public:
        DirectedEdge(const int pFrom, const int pTo, const double pWeight) : from(pFrom), to(pTo), weight(pWeight) {}

        int From() { return from; }

        int To() { return to; }

        double Weight() { return weight; }

        string ToString() {
            ostringstream str;
            str << from << "->" << to << " " << weight << endl;
            return str.str();
        }
    };

    typedef shared_ptr<DirectedEdge> DiEdgePtr;

    class EdgeWeightedDigraph {
    private:
        int v = 0;
        int e = 0;
        vector<vector<DiEdgePtr>> adj;
    public:
        explicit EdgeWeightedDigraph(int pV) : v(pV), e(0) {
            adj.assign(v, {});
        }

        explicit EdgeWeightedDigraph(InStream& pIn) {
            pIn.ReadInt(v);
            pIn.ReadInt(e);
            adj.assign(e, {});

            int from, to;
            double weight;
            for (int index = 0; index < e; index++) {
                pIn.ReadInt(from);
                pIn.ReadInt(to);
                pIn.ReadDouble(weight);
                DiEdgePtr lEdge = make_shared<DirectedEdge>(from, to, weight);
                adj[from].push_back(lEdge);
            }
        }

        int V() { return v; }

        int E() { return e; }

        void AddEdge(const DiEdgePtr &pEdge) {
            adj[pEdge->From()].push_back(pEdge);
        }

        vector<DiEdgePtr> ADJ(const int pV) {
            return adj[pV];
        }

        vector<DiEdgePtr> Edges() {
            vector<DiEdgePtr> rEdges;
            for (int i = 0; i < v; i++) {
                for (DiEdgePtr fEdge: ADJ(i)) {
                    rEdges.push_back(fEdge);
                }
            }
            return rEdges;
        }

        string ToString() {
            ostringstream rStr;
            rStr << v << "Vertices, " << e << " Edges" << endl;
            for (int i = 0; i < v; i++) {
                rStr << i << ": ";
                for (DiEdgePtr fEdge: ADJ(i)) {
                    rStr << "[" << fEdge->To() << ", " << fEdge->Weight() << "]  ";
                }
                rStr << endl;
            }
            return rStr.str();
        }
    };
}

#endif //ALGS4_GRAPH_GRAPH_HPP
