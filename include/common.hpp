//
// Created by john on 11/8/17.
//

#ifndef ALGS4_COMMON_HPP
#define ALGS4_COMMON_HPP

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

inline
vector<string> SplitString(string pString, const string &pSp) {
    vector<string> rStrings;
    int lCurr = 0;
    int lLast = 0;
    while ((lCurr = pString.find_first_of(pSp, lLast)) != pString.npos) {
        if (lCurr != lLast) {
            string sub = pString.substr(lLast, lCurr - lLast);
            rStrings.push_back(sub);
        }
        lLast = lCurr + 1;
    }
    if (lLast != pString.size()) {
        string sub = pString.substr(lLast, pString.size() - lLast);
        rStrings.push_back(sub);
    }
    return rStrings;
}

class InStream {
private:
    string inputPath = "";
    ifstream input;
public:
    explicit InStream(const string &pFilePath) : inputPath(pFilePath), input(pFilePath) {}

    const int ReadInt() {
        int rInt = INT32_MAX;
        if (input) input >> rInt;
        return rInt;
    }

    const double ReadDouble() {
        double rDouble = INT32_MAX;
        if (input) input >> rDouble;
        return rDouble;
    }

    const string ReadString() {
        string rStr;
        if (input) input >> rStr;
        return rStr;
    }

    bool ReadLine(string &rLine) {
        if (getline(input, rLine)) return true;
        return false;
    }

    bool ReadStringsByLine(vector<string> &rStrings, const string pSp) {
        string tmp;
        if (ReadLine(tmp)) {
            rStrings = SplitString(tmp, pSp);
            return true;
        }
        return false;
    }

    bool IsEmpty() {
        if (input) return false;
        return true;
    }

    void Reset() {
        input.clear();
        input.seekg(0, ios::beg);
    }

    ~InStream() {
        input.close();
    }
};


#endif //ALGS4_COMMON_HPP
