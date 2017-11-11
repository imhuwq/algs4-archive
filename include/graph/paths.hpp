//
// Created by john on 11/10/17.
//

#ifndef ALGS4_PATHS_HPP
#define ALGS4_PATHS_HPP

#include <queue>
#include <vector>

#include "graph.hpp"

using namespace std;

namespace graph {
    class Paths {
    public:
        Paths(Graph &pGraph, const int &pSource) : marked(pGraph.V(), false), edgeTo(pGraph.V(), -1), source(pSource) {
            if (pSource > pGraph.V()) {
                cerr << "source " << pSource << " is out of graph range" << endl;
                exit(-1);
            }
        }

        bool HasPathTo(const int &pV) { return marked[pV]; }

        deque<int> PathTo(const int &pV) {
            if (!HasPathTo(pV)) return {};

            deque<int> rVertices;
            for (int x = pV; x != source; x = edgeTo[x]) {
                rVertices.push_front(x);
            }
            rVertices.push_front(source);
            return rVertices;
        }

    protected:
        int source;
        vector<bool> marked;
        vector<int> edgeTo;
    };

    class DepthFirstPaths : public Paths {
    public:
        DepthFirstPaths(Graph &pGraph, const int &pSource) : Paths(pGraph, pSource) {
            DFS(pGraph, source);
        }

    private:
        void DFS(Graph &pGraph, const int &pV) {
            marked[pV] = true;
            for (int w:pGraph.ADJ(pV)) {
                if (!marked[w]) {
                    edgeTo[w] = pV;
                    DFS(pGraph, w);
                }
            }
        }
    };

    class BreadthFirstPaths : public Paths {
    public:
        BreadthFirstPaths(Graph &pGraph, const int &pSource) : Paths(pGraph, pSource) {
            BFS(pGraph, pSource);
        }

    private:
        void BFS(Graph &pGraph, const int &pS) {
            queue<int> vQueue;
            marked[pS] = true;
            vQueue.push(pS);

            while (!vQueue.empty()) {
                int v = vQueue.front();
                vQueue.pop();

                for (int w: pGraph.ADJ(v)) {
                    if (!marked[w]) {
                        marked[w] = true;
                        edgeTo[w] = v;
                        vQueue.push(w);
                    }
                }
            }
        }
    };
}

#endif //ALGS4_PATHS_HPP
