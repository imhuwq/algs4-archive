//
// Created by john on 11/8/17.
//

#ifndef ALGS4_GRAPH_COMMON_HPP
#define ALGS4_GRAPH_COMMON_HPP

#include <iostream>

using namespace std;

namespace algs4 {

    class InStream {
    private:
        istream &in;
    public:
        explicit InStream(istream &pIn) : in(pIn) {}

        const int ReadInt() {
            int rInt = INT32_MAX;
            if (in) in >> rInt;
            return rInt;
        }
    };
}

#endif //ALGS4_GRAPH_COMMON_HPP
