//
// Created by john on 11/10/17.
//

#ifndef ALGS4_PATHS_HPP
#define ALGS4_PATHS_HPP

#include <deque>
#include <vector>

#include "graph.hpp"

using namespace std;

namespace algs4 {
    class Paths {
    public:
        Paths(Graph &pGraph, const int &pSource) : marked(pGraph.V(), false), edgeTo(pGraph.V(), -1), source(pSource) {

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
            if (pSource > pGraph.V()) {
                cerr << "source " << pSource << " is out of graph range" << endl;
                exit(-1);
            }
            DFS(pGraph, source);
        }

    private:
        void DFS(Graph &pGraph, const int &pSource) {
            marked[pSource] = true;
            for (int w:pGraph.ADJ(pSource)) {
                if (!marked[w]) {
                    edgeTo[w] = pSource;
                    DFS(pGraph, w);
                }
            }
        }
    };
}

#endif //ALGS4_PATHS_HPP
