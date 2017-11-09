//
// Created by john on 11/10/17.
//

#ifndef ALGS4_GRAPH_UTILS_HPP
#define ALGS4_GRAPH_UTILS_HPP

#include <vector>
#include <string>

using namespace std;

namespace algs4 {
    pair<string, int> ParseCommandLine(int argc, const char **argv) {
        if (argc < 3) {
            cerr << "Usage: executor [test_file_path] [source_vertex]" << endl;
            exit(0);
        }

        string testFile = argv[1];
        long long tempSource = strtoll(argv[2], nullptr, 0);
        if (tempSource < 0) {
            cerr << "source should be greater than 0 (" << tempSource << ")" << endl;
            exit(0);
        }
        int source = strtoul(argv[2], nullptr, 0);

        return {testFile, source};
    };
}

#endif //ALGS4_GRAPH_UTILS_HPP
