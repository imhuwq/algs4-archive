//
// Created by john on 11/11/17.
//

#include <map>
#include <vector>
#include <string>

#include "common.hpp"
#include "search/utils.hpp"
#include "search/rb_tree.hpp"

using namespace std;
using namespace search;

int main(const int argc, const char **argv) {
    pair<string, int> cmd = ParseCommandLine(argc, argv);
    string inputFile = cmd.first;
    int wordLengthLimit = cmd.second;

    RBTree<string, int> rbt;
    InStream input(inputFile);
    while (!input.IsEmpty()) {
        string word = input.ReadString();
        if (word.length() < wordLengthLimit) continue;
        if (!rbt.Contains(word)) {
            rbt.Put(word, 1);
        } else {
            int wordCount = 0;
            rbt.Get(word, wordCount);
            rbt.Put(word, wordCount + 1);
        }
    }

//    File (data/tinyTale.txt) Contains 21 Distinct Words which are Longer than 0
//    File (data/tinyTale.txt) Contains 61 Words  which are Longer than 0
//    Word: it, Count: 10
//    PROFILE: interrupts/evictions/bytes = 0/0/64
//    : 1
//    age: 2
//    belief: 1
//    best: 1
//    darkness: 1
//    despair: 1
//    epoch: 2
//    foolishness: 1
//    hope: 1
//    incredulity: 1
//    it: 10
//    light: 1
//    of: 10
//    season: 2
//    spring: 1
//    the: 10
//    times: 2
//    was: 10
//    winter: 1
//    wisdom: 1
//    worst: 1

    cout << "Input Done. Max Depth of RBT is: " << rbt.MaxDepth() << endl;

    string max;
    int maxCount = 0;
    int totalCount = 0;

    vector<pair<string, int>> wordInfos;
    rbt.Items(wordInfos);
    for (pair<string, int> &wordInfo:wordInfos) {
        totalCount += wordInfo.second;
        if (wordInfo.second > maxCount) {
            max = wordInfo.first;
            maxCount = wordInfo.second;
        }
    }

    cout << "File (" << inputFile << ") Contains " << rbt.Size() << " Distinct Words which are Longer than " << wordLengthLimit << endl;
    cout << "File (" << inputFile << ") Contains " << totalCount << " Words which are Longer than " << wordLengthLimit << endl;
    cout << "Word: " << max << ", Count: " << maxCount << endl;
}