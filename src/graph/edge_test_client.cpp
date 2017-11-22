//
// Created by john on 11/23/17.
//

#include "graph/graph.hpp"

using namespace graph;

int main() {
    Edge e1(1, 2, 0.8);
    Edge e2(2, 3, 0.9);
    Edge e3(3, 4, 0.8);

    if (e1 > e2) cout << "e1 > e2" << endl;
    if (e1 >= e3) cout << "e1 >= e3" << endl;

    shared_ptr<Edge> e4 = make_shared<Edge>(e3);
    cout << e4->ToString() << endl;
    Edge *e5 = e4.get();
    delete e5;
    cout << e4->ToString() << endl;

}