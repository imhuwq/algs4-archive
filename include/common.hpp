//
// Created by john on 11/8/17.
//

#ifndef ALGS4_COMMON_HPP
#define ALGS4_COMMON_HPP

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

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

    const string ReadString() {
        string rStr = "";
        if (input) input >> rStr;
        return rStr;
    }

    bool IsEmpty() {
        if (input) return false;
        return true;
    }

    ~InStream() {
        input.close();
    }
};

#endif //ALGS4_COMMON_HPP
