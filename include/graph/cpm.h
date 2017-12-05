//
// Created by john on 12/5/17.
//

#ifndef ALGS4_CPM_H
#define ALGS4_CPM_H

#include <vector>
#include <string>

#include "common.hpp"
#include "graph/spt.hpp"
#include "graph/graph.hpp"
#include "graph/utils.hpp"

using namespace std;
using namespace graph;

namespace graph {
    class CriticalPathMethod {
    private:
        shared_ptr<EdgeWeightedDigraph> graph = nullptr;
        shared_ptr<AcyclicLP> acyclicLP = nullptr;

    public:
        explicit CriticalPathMethod(InStream &pIn) {
            int lN;
            pIn.ReadInt(lN);
            graph = make_shared<EdgeWeightedDigraph>(2 * lN + 2);

            int lS = 2 * lN, lT = 2 * lN + 1;

            vector<string> lStrs;
            pIn.ToNextLine();
            for (int fV = 0; fV < lN; fV++) {
                pIn.ReadStringsByLine(lStrs, "  ");
                double fDuration = pIn.ParseNumber<double>(lStrs[0]);
                graph->AddEdge(make_shared<DirectedEdge>(fV, fV + lN, fDuration));
                graph->AddEdge(make_shared<DirectedEdge>(lS, fV, 0.0));
                graph->AddEdge(make_shared<DirectedEdge>(fV + lN, lT, 0.0));

                for (int index = 1; index < lStrs.size(); index++) {
                    int fSuccessor = pIn.ParseNumber<int>(lStrs[index]);
                    graph->AddEdge(make_shared<DirectedEdge>(fV + lN, fSuccessor, 0.0));
                }
            }

            acyclicLP = make_shared<AcyclicLP>(*graph, lS);
        }

        string ToString() {
            ostringstream rStr;
            rStr << "Start Times:" << endl;
            int lN = graph->V() / 2 - 1;
            int lT = graph->V() - 1;
            for (int fV = 0; fV < lN; fV++) {
                rStr << "  " << fV << ": " << acyclicLP->DistTo(fV) << endl;
            }
            rStr << "Finish Time: " << acyclicLP->DistTo(lT) << endl;
            return rStr.str();
        }
    };
}

#endif //ALGS4_CPM_H
