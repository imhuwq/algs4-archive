#include <string>
#include <fstream>
#include <iostream>

#include "graph/common.hpp"
#include "include/graph/graph.hpp"

using namespace std;
using namespace graph;

int main(int argc, const char **argv) {
    const string tinyG = "/home/john/git/github/algs4/data/tinyG.txt";
    const string mediumG = "/home/john/git/github/algs4/data/mediumG.txt";
    const string largeG = "/home/john/git/github/algs4/data/largeG.txt";

    InStream in(tinyG);
    Graph graph(in);
    cout << graph.ToString() << endl;
}
