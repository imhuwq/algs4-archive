//
// Created by john on 11/16/17.
//

#include <string>
#include <sstream>
#include <common.hpp>

#include "sort/heap.hpp"
#include "sort/utils.hpp"

using namespace std;
using namespace sort;

int main(int argc, const char **argv) {
    pair<string, int> cmd = ParseCommandLine(argc, argv);
    string inputFile = cmd.first;
    int topNum = cmd.second;

    vector<Transaction> lTs;
    InStream input(inputFile);
    string line;
    while (input.ReadLine(line)) {
        lTs.emplace_back(istringstream(line));
    }

    HeapSort<Transaction>::Sort(lTs);

    for (auto t: lTs) {
        cout << t.ToString() << endl;
    }
}