//
// Created by john on 11/11/17.
//

//
// Created by john on 11/11/17.
//

#include <map>

#include "common.hpp"
#include "search/utils.hpp"

using namespace std;
using namespace search;

int main(const int argc, const char **argv) {
    pair<string, int> cmd = ParseCommandLine(argc, argv);
    string inputFile = cmd.first;
    int wordLengthLimit = cmd.second;

    map<string, int> wordMap;

    InStream input(inputFile);
    while (!input.IsEmpty()) {
        string word = input.ReadString();
        if (word.length() < wordLengthLimit) continue;
        if (wordMap.find(word) == wordMap.end()) {
            wordMap[word] = 1;
        } else {
            wordMap[word] = wordMap[word] + 1;
        }
    }


    string max;
    int maxCount = 0;
    int totalCount = 0;


    for (auto& wordInfo:wordMap) {
        totalCount += wordInfo.second;
        if (wordInfo.second > maxCount) {
            max = wordInfo.first;
            maxCount = wordInfo.second;
        }
    }

    cout << "File (" << inputFile << ") Contains " << wordMap.size() << " Distinct Words which are Longer than " << wordLengthLimit << endl;
    cout << "File (" << inputFile << ") Contains " << totalCount << " Words  which are Longer than " << wordLengthLimit << endl;
    cout << "Word: " << max << ", Count: " << maxCount << endl;
}