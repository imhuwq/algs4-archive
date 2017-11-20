//
// Created by john on 11/9/17.
//

#ifndef ALGS4_GRAPH_SEARCH_HPP
#define ALGS4_GRAPH_SEARCH_HPP

#include <vector>
#include <queue>

#include "graph.hpp"

using namespace std;
using namespace graph;

namespace graph {
    class Search {
    public:
        Search(Graph &pGraph, const int &pSource) : marked(pGraph.V(), false) {
            if (pSource >= pGraph.V()) {
                cerr << "source " << pSource << " is out of graph range" << endl;
                exit(-1);
            }
        };

        bool Marked(int pV) {
            if (pV >= marked.size()) {
                cerr << pV << " is out of graph" << endl;
                exit(EXIT_FAILURE);
            }
            return marked[pV];
        }

        int Count() { return count; }

    protected:
        vector<bool> marked;
        int count = 0;
    };

    class DepthFirstSearch : public Search {
    public:
        DepthFirstSearch(Graph &pGraph, const int &pSource) : Search(pGraph, pSource) {
            DFS(pGraph, pSource);
        }

    private:
        void DFS(Graph &pGraph, const int &pSource) {
            if (marked[pSource]) return;
            marked[pSource] = true;
            count++;
            for (int w:pGraph.ADJ(pSource)) {
                if (!marked[w]) DFS(pGraph, w);
            }
        }
    };

    class BreadthFirstSearch : public Search {
    public:
        BreadthFirstSearch(Graph &pGraph, const int &pSource) : Search(pGraph, pSource) {
            BFS(pGraph, pSource);
        }

    private:
        void BFS(Graph &pGraph, const int pSource) {
            queue<int> lQueue;
            marked[pSource] = true;
            lQueue.push(pSource);

            while (!lQueue.empty()) {
                int lV = lQueue.back();
                lQueue.pop();
                for (int fW:pGraph.ADJ(lV)) {
                    if (!marked[fW]) {
                        marked[fW] = true;
                        lQueue.push(fW);
                        count++;
                    }
                }
            }
        }
    };
}

#endif //ALGS4_GRAPH_SEARCH_HPP
