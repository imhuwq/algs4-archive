#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "include/common.hpp"
#include "include/graph.hpp"

using namespace std;
using namespace algs4;

int main(int argc, const char **argv) {
    const string tinyG = "/home/john/git/github/algs4/graph/data/tinyG.txt";
    const string mediumG = "/home/john/git/github/algs4/graph/data/mediumG.txt";
    const string largeG = "/home/john/git/github/algs4/graph/data/largeG.txt";

    InStream in(tinyG);
    Graph graph(in);
    cout << graph.ToString() << endl;
}
