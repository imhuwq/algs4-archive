//
// Created by john on 12/20/17.
//

#ifndef ALGS4_LSD_H
#define ALGS4_LSD_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;

namespace string_algs {
    class LSD {
    public:
        void static Sort(vector<string> &pStrings, const int w) {
            size_t mN = pStrings.size();
            size_t mR = 256;
            vector<string> mAux(mN, "");

            for (int d = w - 1; d >= 0; d--) {
                vector<int> count(mR + 1, 0);

                // count
                for (int i = 0; i < mN; i++) {
                    count[(int) pStrings[i][d] + 1]++;
                }

                // count to indices
                for (int i = 0; i < mR; i++) {
                    count[i + 1] += count[i];
                }

                // distribute by indices
                for (int i = 0; i < mN; i++) {
                    mAux[count[(int) pStrings[i][d]]++] = pStrings[i];
                }

                // store the sorted result
                pStrings = mAux;
            }
        }
    };
}

#endif //ALGS4_LSD_H
