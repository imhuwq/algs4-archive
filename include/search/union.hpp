//
// Created by john on 11/25/17.
//

#ifndef ALGS4_UNION_HPP
#define ALGS4_UNION_HPP

#include <vector>

using namespace std;

namespace search {
    class QuickFindUF {
    private:
        vector<int> ids;
        int count = 0;
    public:
        explicit QuickFindUF(const int pC) : count(pC) {
            for (int i = 0; i < count; i++) {
                ids.push_back(i);
            }
        }

        bool Connected(const int pV, const int pW) {
            return Find(pV) == Find(pW);
        }

        int Find(const int pV) { return ids[pV]; }

        void Union(const int pV, const int pW) {
            int idV = Find(pV), idW = Find(pW);
            if (idV == idW) return;
            for (int i = 0; i < ids.size(); i++) {
                if (ids[i] == idV) ids[i] = idW;
            }
            count--;
        }
    };

    class QuickUnionUF {
    private:
        vector<int> parents;
        int count = 0;

    public:
        explicit QuickUnionUF(const int pC) : count(pC) {
            for (int i = 0; i < count; i++) {
                parents.push_back(i);
            }
        }

        int Find(int pV) {
            while (pV != parents[pV]) pV = parents[pV];
            return pV;
        }

        void Union(const int pV, const int pW) {
            int idV = Find(pV), idW = Find(pW);
            if (idV == idW) return;
            parents[idV] = idW;
            count--;
        }

        bool Connected(const int pV, const int pW) {
            return Find(pV) == Find(pW);
        }
    };

    class WeightedQuickUnionUF {
    private:
        vector<int> parents;
        vector<int> sizes;
        int count = 0;

    public:
        explicit WeightedQuickUnionUF(const int pC) : count(pC), sizes(pC, 1) {
            for (int i = 0; i < count; i++) {
                parents.push_back(i);
            }
        }

        int Find(int pV) {
            while (pV != parents[pV]) pV = parents[pV];
            return pV;
        }

        void Union(const int pV, const int pW) {
            int idV = Find(pV), idW = Find(pW);
            if (idV == idW) return;
            if (sizes[pV] < sizes[pW]) {
                sizes[pW] += sizes[pV];
                parents[idV] = idW;
            } else {
                sizes[pV] += sizes[pW];
                parents[pW] = idV;
            }
            count--;
        }

        bool Connected(const int pV, const int pW) {
            return Find(pV) == Find(pW);
        }
    };
}

#endif //ALGS4_UNION_HPP
