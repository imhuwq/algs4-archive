//
// Created by john on 11/24/17.
//

#include <string>
#include <sstream>
#include <common.hpp>

#include "sort/heap.hpp"
#include "sort/utils.hpp"

using namespace std;
using namespace sort;

int main(int argc, const char **argv) {
    IndexMinPQ<int> pq(3);

    pq.Insert(0, 1);
    pq.Insert(1, 10);
    pq.Insert(2, 5);

    pq.Delete(2);
//
//    cout << 1<< endl;
    int num1, num2;
    pq.DeleteMin(num1);
    pq.DeleteMin(num2);
    cout << num1 << " " << num2 << endl;
}