//
// Created by john on 11/9/17.
//

#ifndef ALGS4_GRAPH_SEARCH_HPP
#define ALGS4_GRAPH_SEARCH_HPP

#include <vector>

#include "graph.hpp"

using namespace std;
using namespace algs4;

namespace algs4 {
    class Search {
    public:
        Search(Graph &pGraph, const unsigned long &pSource) : marked(pGraph.V(), false) {};

        bool Marked(unsigned long v) { return marked[v]; }

        unsigned long Count() { return count; }

    protected:
        vector<bool> marked;
        unsigned long count = 0;
    };

    class DepthFirstSearch : public Search {
    public:
        DepthFirstSearch(Graph &pGraph, const unsigned long &pSource) : Search(pGraph, pSource) {
            if (pSource > pGraph.V()) {
                cerr << "source " << pSource << " is out of graph range" << endl;
            }
            DFS(pGraph, pSource);
        }

    private:
        void DFS(Graph &pGraph, const unsigned long &pSource) {

        }
    };
}

#endif //ALGS4_GRAPH_SEARCH_HPP
