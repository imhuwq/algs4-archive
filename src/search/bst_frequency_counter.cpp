//
// Created by john on 11/11/17.
//

#include <map>
#include <deque>
#include <string>

#include "common.hpp"
#include "search/bst.hpp"
#include "search/utils.hpp"

using namespace std;
using namespace search;

int main(const int argc, const char **argv) {
    pair<string, int> cmd = ParseCommandLine(argc, argv);
    string inputFile = cmd.first;
    int wordLengthLimit = cmd.second;

    BST<string, int> bst;
    InStream input(inputFile);
    while (!input.IsEmpty()) {
        string word = input.ReadString();
        if (word.length() < wordLengthLimit) continue;
        if (!bst.Contains(word)) {
            bst.Put(word, 1);
        } else {
            int wordCount = 0;
            bst.Get(word, wordCount);
            bst.Put(word, wordCount + 1);
        }
    }

    cout << "Input Done. Max Depth of BST is: " << bst.MaxDepth() << endl;

    string max;
    int maxCount = 0;
    int totalCount = 0;

    deque<pair<string, int>> wordInfos;
    bst.Pairs(wordInfos);
    for (pair<string, int> &wordInfo:wordInfos) {
        totalCount += wordInfo.second;
        if (wordInfo.second > maxCount) {
            max = wordInfo.first;
            maxCount = wordInfo.second;
        }
    }

    cout << "File (" << inputFile << ") Contains " << bst.Size() << " Distinct Words which are Longer than " << wordLengthLimit << endl;
    cout << "File (" << inputFile << ") Contains " << totalCount << " Words  which are Longer than " << wordLengthLimit << endl;
    cout << "Word: " << max << ", Count: " << maxCount << endl;
}