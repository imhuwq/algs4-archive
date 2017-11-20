//
// Created by john on 11/8/17.
//

#ifndef ALGS4_GRAPH_GRAPH_HPP
#define ALGS4_GRAPH_GRAPH_HPP

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
            v = pIn.ReadInt();
            int edge = pIn.ReadInt();
            adj.assign(v, {});
            for (int index = 0; index < edge; index++) {
                int v = pIn.ReadInt();
                int w = pIn.ReadInt();
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
            v = pIn.ReadInt();
            int edge = pIn.ReadInt();
            adj.assign(v, {});
            for (int index = 0; index < edge; index++) {
                int v = pIn.ReadInt();
                int w = pIn.ReadInt();
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
            os << "DiGraph: " << v << " vertices, " << e << "e edges" << endl;
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
            DiGraph rGraph;
            for (int index = 0; index < v; index++) {
                for (int w: ADJ(index)) {
                    rGraph.AddEdge(w, index);
                }
            }
            return rGraph;
        }
    };
}

#endif //ALGS4_GRAPH_GRAPH_HPP
