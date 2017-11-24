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

    template<typename Key>
    class IndexMinPQ {
    private:
        vector<int> data;
        vector<int> indices;
        vector<Key> keys;
        int size = 0;

        void Exchange(const int pIndexInData1, const int pIndexInData2) {
            int tmpIndex = data[pIndexInData1];
            data[pIndexInData1] = data[pIndexInData2];
            data[pIndexInData2] = tmpIndex;

            indices[data[pIndexInData1]] = pIndexInData1;
            indices[data[pIndexInData2]] = pIndexInData2;
        }

        bool Less(const int pIndexInData1, const int pIndexInData2) {
            return keys[data[pIndexInData1]] < keys[data[pIndexInData2]];
        }

        bool More(const int pIndexInData1, const int pIndexInData2) {
            return !Less(pIndexInData1, pIndexInData2);
        }

        void Swim(int pIndexInData) {
            while (pIndexInData > 1 and Less(pIndexInData, pIndexInData / 2)) {
                int lParentIndex = pIndexInData / 2;
                Exchange(pIndexInData, pIndexInData / 2);
                pIndexInData = pIndexInData / 2;
            }
        }

        void Sink(int pIndexInData) {
            while (pIndexInData * 2 <= size) {
                int lChildIndex = pIndexInData * 2;
                if (lChildIndex < size and More(lChildIndex, lChildIndex + 1)) lChildIndex++;
                if (Less(pIndexInData, lChildIndex)) break;
                Exchange(pIndexInData, lChildIndex);
                pIndexInData = lChildIndex;
            }
        }

    public:
        explicit IndexMinPQ(const int pCap) : data(pCap + 1, -1), indices(pCap + 1, -1), keys(pCap, Key()), size(0) {}

        bool IsEmpty() {
            return size == 0;
        }

        int Size() {
            return size;
        }

        void Insert(const int pIndex, const Key &pKey) {
            size++;
            indices[pIndex] = size;
            data[size] = pIndex;
            keys[pIndex] = pKey;
            Swim(size);
        }

        bool DeleteMin(Key &rKey) {
            if (size == 0) return false;
            rKey = keys[data[1]];
            return DeleteMin();
        }

        bool DeleteMinIndex(int &rIndex) {
            if (size == 0) return false;
            rIndex = data[1];
            return DeleteMin();
        }

        bool DeleteMin() {
            if (size == 0) return false;
            Exchange(1, size--);
            Sink(1);
            keys[data[size + 1]] = Key();
            indices[data[size + 1]] = -1;
            return true;
        }

        bool Contains(const int pIndex) {
            return pIndex < size and indices[pIndex] != -1;
        }

        void Change(const int pIndex, const Key &pKey) {
            keys[pIndex] = pKey;
            Swim(indices[pIndex]);
            Sink(indices[pIndex]);
        }

        void Delete(const int pIndex) {
            if (!Contains(pIndex)) return;
            Exchange(indices[pIndex], size--);
            Swim(indices[pIndex]);
            Sink(indices[pIndex]);
            keys[data[size + 1]] = Key();
            indices[data[size + 1]] = -1;
        }
    };
}

#endif //ALGS4_HEAP_HPP
