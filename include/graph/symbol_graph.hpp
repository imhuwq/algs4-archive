//
// Created by john on 11/19/17.
//

#ifndef ALGS4_SYMBOL_GRAPH_HPP
#define ALGS4_SYMBOL_GRAPH_HPP

#include <string>
#include <vector>

#include "graph.hpp"
#include "common.hpp"
#include "search/rb_tree.hpp"


using namespace std;
using namespace search;

namespace graph {
    class SymbolGraph {
    private:
        vector<string> keys;          // from index to symbol
        RBTree<string, int> symbols;  // from symbol to index
        Graph g;                      // underling graph;
    public:
        SymbolGraph(const string &pInFile, const string &pSp) {
            InStream lIn(pInFile);
            while (!lIn.IsEmpty()) {
                vector<string> wKeys;
                if (!lIn.ReadStringsByLine(wKeys, pSp)) continue;
                for (const string &fKey:wKeys) {
                    if (symbols.Contains(fKey)) continue;
                    symbols.Put(fKey, symbols.Size());
                }
            }

            keys.assign(symbols.Size(), "");
            vector<pair<string, int>> lItems;
            symbols.Items(lItems);
            for (const pair<string, int> &fItem:lItems) {
                keys[fItem.second] = fItem.first;
            }

            g = Graph(symbols.Size());
            lIn.Reset();

            string lVStr, lWStr;
            int lV, lW;
            while (!lIn.IsEmpty()) {
                vector<string> wKeys;
                if (!lIn.ReadStringsByLine(wKeys, pSp)) continue;

                lVStr = wKeys[0];
                symbols.Get(lVStr, lV);
                for (int index = 1; index < wKeys.size(); index++) {
                    lWStr = wKeys[index];
                    symbols.Get(lWStr, lW);
                    g.AddEdge(lV, lW);
                }
            }
        }

        bool Contains(const string &pKey) {
            return symbols.Contains(pKey);
        }

        bool Index(const string &pKey, int &rIndex) {
            return (symbols.Get(pKey, rIndex));
        }

        bool Key(const int pIndex, string &rKey) {
            if (pIndex > keys.size()) return false;
            rKey = keys[pIndex];
            return true;
        }

        const vector<string> &Keys() {
            return keys;
        }

        vector<string> ADJ(const string &pKey) {
            vector<string> rKeys;
            int lIndex;
            if (!symbols.Get(pKey, lIndex)) return rKeys;
            for (int w: g.ADJ(lIndex)) {
                rKeys.push_back(keys[w]);
            }
            return rKeys;
        };

        const Graph &GetGraph() {
            return g;
        }
    };
}
#endif //ALGS4_SYMBOL_GRAPH_HPP
