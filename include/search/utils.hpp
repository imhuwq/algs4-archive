//
// Created by john on 11/11/17.
//

#ifndef ALGS4_UTILS_HPP_H
#define ALGS4_UTILS_HPP_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace search {
    pair<string, int> ParseCommandLine(int argc, const char **argv) {
        if (argc < 3) {
            cerr << "Usage: executor [test_file_path] [length_limitation]" << endl;
            exit(0);
        }

        string testFile = argv[1];
        int source = strtoul(argv[2], nullptr, 0);

        return {testFile, source};
    };
}
#endif //ALGS4_UTILS_HPP_H
