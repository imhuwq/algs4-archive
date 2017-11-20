//
// Created by john on 11/21/17.
//

#ifndef ALGS4_REACHABILITY_HPP
#define ALGS4_REACHABILITY_HPP

#include <vector>
#include <queue>

#include "graph.hpp"

using namespace std;
using namespace graph;

namespace graph {
    class Reachability {
    protected:
        vector<bool> marked;
        int count = 0;

    public:
        Reachability(DiGraph &pDiGraph, const int pSource) : marked(pDiGraph.V(), false), count(0) {
            if (pSource >= pDiGraph.V()) {
                cerr << pSource << " is out of graph" << endl;
                exit(EXIT_FAILURE);
            }
        }

        Reachability(DiGraph &pDiGraph, const vector<int> &pSources) : marked(pDiGraph.V(), false), count(0) {
            for (int lSource:pSources) {
                if (lSource > pDiGraph.V()) {
                    cerr << lSource << " is out of graph" << endl;
                }
            }
        }

        bool Marked(int pV) {
            if (pV >= marked.size()) {
                cerr << pV << " is out of graph" << endl;
                exit(EXIT_FAILURE);
            }
            return marked[pV];
        }

        int Count() { return count; }
    };

    class DepthFirstReachability : public Reachability {
    private:
        void DFS(DiGraph &pDiGraph, const int pSource) {
            if (marked[pSource]) return;
            marked[pSource] = true;
            count++;
            for (int w: pDiGraph.ADJ(pSource)) {
                if (!marked[w]) DFS(pDiGraph, w);
            }
        }

    public:
        DepthFirstReachability(DiGraph &pDiGraph, const int pSource) : Reachability(pDiGraph, pSource) {
            DFS(pDiGraph, pSource);
        }

        DepthFirstReachability(DiGraph &pDiGraph, const vector<int> &pSources) : Reachability(pDiGraph, pSources) {
            for (int lSource:pSources) {
                DFS(pDiGraph, lSource);
            }
        }
    };

    class BreadthFirstReachability : public Reachability {
    private:
        void BFS(DiGraph &pDiGraph, const int pSource) {
            queue<int> lQueue;
            lQueue.push(pSource);
            marked[pSource] = true;

            while (!lQueue.empty()) {
                int lV = lQueue.back();
                lQueue.pop();
                count++;
                for (int fW: pDiGraph.ADJ(lV)) {
                    if (!marked[fW]) {
                        marked[fW] = true;
                        count++;
                        lQueue.push(fW);
                    }
                }
            }
        }

    public:
        BreadthFirstReachability(DiGraph &pDiGraph, const int pSource) : Reachability(pDiGraph, pSource) {
            BFS(pDiGraph, pSource);
        }

        BreadthFirstReachability(DiGraph &pDiGraph, const vector<int> &pSources) : Reachability(pDiGraph, pSources) {
            for (int lSource:pSources) {
                BFS(pDiGraph, lSource);
            }
        }
    };
}

#endif //ALGS4_REACHABILITY_HPP
