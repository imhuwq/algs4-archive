//
// Created by john on 11/16/17.
//

#ifndef ALGS4_HEAP_HPP
#define ALGS4_HEAP_HPP

#include <vector>

using namespace std;

namespace sort {
    template<typename Key>
    class PQ {
    protected:
        vector<Key> data = {Key()};
        int size = 0;

        void Exchange(const int pIndex1, const int pIndex2) {
//            data[pIndex1], data[pIndex2] = data[pIndex2], data[pIndex1];
            Key tmp = data[pIndex1];
            data[pIndex1] = data[pIndex2];
            data[pIndex2] = tmp;
        }

        bool Less(const int pIndex1, const int pIndex2) {
            return data[pIndex1] < data[pIndex2];
        }

        bool More(const int pIndex1, const int pIndex2) {
            return !Less(pIndex1, pIndex2);
        }

    public:
        bool IsEmpty() {
            return size == 0;
        }

        int Size() {
            return size;
        }

        virtual vector<Key> Keys() = 0;
    };

    template<typename Key>
    class MaxPQ : public PQ<Key> {
    private:
        void Swim(int pIndex) {
            while (pIndex > 1 and this->More(pIndex, pIndex / 2)) {
                int lParentIndex = pIndex / 2;
                this->Exchange(pIndex, lParentIndex);
                pIndex = lParentIndex;
            }
        }

        void Sink(int pIndex) {
            while (pIndex * 2 <= this->size) {
                int lChildIndex = pIndex * 2;
                if (lChildIndex < this->size and this->Less(lChildIndex, lChildIndex + 1)) lChildIndex++;
                if (this->More(pIndex, lChildIndex)) break;
                this->Exchange(pIndex, lChildIndex);
                pIndex = lChildIndex;
            }
        }

    public:
        MaxPQ() = default;

        explicit MaxPQ(const vector<Key> &pKeys) {
            for (Key &key:pKeys) {
                Insert(key);
            }
        }

        void Insert(const Key &rKey) {
            this->data.push_back(rKey);
            this->size++;
            Swim(this->size);
        }

        bool Max(Key &rKey) {
            if (this->IsEmpty()) return false;
            rKey = this->data[1];
            return true;
        }

        bool DeleteMax(Key &rKey) {
            if (this->size == 0) return false;
            rKey = this->data[1];
            return DeleteMax();
        }

        bool DeleteMax() {
            if (this->size == 0) return false;
            this->data[1] = this->data[this->size];
            this->data.erase(this->data.begin() + this->size, this->data.end());
            this->size--;
            Sink(1);
            return true;
        }

        vector<Key> Keys() {

        }
    };

    template<typename Key>
    class MinPQ : public PQ<Key> {
    private:
        void Swim(int pIndex) {
            while (pIndex > 1 and this->Less(pIndex, pIndex / 2)) {
                int lParentIndex = pIndex / 2;
                this->Exchange(pIndex, pIndex / 2);
                pIndex = pIndex / 2;
            }
        }

        void Sink(int pIndex) {
            while (pIndex * 2 <= this->size) {
                int lChildIndex = pIndex * 2;
                if (lChildIndex < this->size and this->More(lChildIndex, lChildIndex + 1)) lChildIndex++;
                if (this->Less(pIndex, lChildIndex)) break;
                this->Exchange(pIndex, lChildIndex);
                pIndex = lChildIndex;
            }
        }

    public:
        MinPQ() = default;

        explicit MinPQ(const vector<Key> &pKeys) {
            for (const Key &key:pKeys) {
                Insert(key);
            }
        }

        void Insert(const Key &pKey) {
            this->data.push_back(pKey);
            this->size++;
            Swim(this->size);
        }

        bool DeleteMin(Key &pKey) {
            if (this->size == 0) return false;
            pKey = this->data[1];
            return DeleteMin();
        }

        bool DeleteMin() {
            if (this->size == 0) return false;
            this->data[1] = this->data[this->size];
            this->data.erase(this->data.begin() + this->size, this->data.end());
            this->size--;
            Sink(1);
            return true;
        }

        vector<Key> Keys() {

        }
    };

    template<typename Key>
    class HeapSort {
    private:
        static bool More(vector<Key> &pKeys, const int pIndex1, const int pIndex2) {
            return pKeys[pIndex1] > pKeys[pIndex2];
        }

        static bool Less(vector<Key> &pKeys, const int pIndex1, const int pIndex2) {
            return !More(pKeys, pIndex1, pIndex2);
        }

        static void Exchange(vector<Key> &pKeys, int pIndex1, int pIndex2) {
            Key tmp = pKeys[pIndex1];
            pKeys[pIndex1] = pKeys[pIndex2];
            pKeys[pIndex2] = tmp;
        }

        static void Sink(vector<Key> &pKeys, int pIndex, int pEnd) {
            while (pIndex * 2 <= pEnd) {
                int lChildIndex = pIndex * 2;
                if (lChildIndex < pEnd and Less(pKeys, lChildIndex, lChildIndex + 1)) lChildIndex++;
                if (More(pKeys, pIndex, lChildIndex)) break;
                Exchange(pKeys, pIndex, lChildIndex);
                pIndex = lChildIndex;
            }
        }

    public:
        static void Sort(vector<Key> &pKeys) {
            pKeys.insert(pKeys.begin(), Key());
            int size = (int) pKeys.size() - 1;
            for (int index = size / 2; index >= 1; index--) {
                Sink(pKeys, index, size);
            }

            while (size >= 1) {
                Exchange(pKeys, 1, size--);
                Sink(pKeys, 1, size);
            }

            pKeys.erase(pKeys.begin(), pKeys.begin() + 1);
        }
    };
}

#endif //ALGS4_HEAP_HPP
