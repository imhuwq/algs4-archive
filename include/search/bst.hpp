//
// Created by john on 11/11/17.
//

#ifndef ALGS4_BST_HPP
#define ALGS4_BST_HPP

#include <deque>
#include <memory>

using namespace std;

namespace search {
    template<typename Key, typename Value>
    class BST {
    private:
        class Node;

        typedef shared_ptr<Node> NodePtr;

        class Node {
        public:
            Node(Key pKey, Value pValue) : key(pKey), value(pValue) {}

            Key key;
            Value value;
            int size = 1;
            NodePtr left = nullptr;
            NodePtr right = nullptr;
        };

        NodePtr root = nullptr;

        int Size(NodePtr pNode) {
            if (pNode == nullptr) return 0;
            return Size(pNode->left) + Size(pNode->right) + 1;
        }

        bool Contains(NodePtr pNode, Key pKey) {
            if (pNode == nullptr) return false;
            if (pKey > pNode->key) return Contains(pNode->right, pKey);
            else if (pKey < pNode->key) return Contains(pNode->left, pKey);
            else return true;
        }

        void Get(NodePtr pNode, Key pKey, Value &rValue) {
            if (pNode == nullptr) return;
            if (pKey > pNode->key) Get(pNode->right, pKey, rValue);
            else if (pKey < pNode->key) Get(pNode->left, pKey, rValue);
            else rValue = pNode->value;
        }

        NodePtr Put(NodePtr pNode, Key pKey, Value pValue) {
            if (pNode == nullptr) return make_shared<Node>(pKey, pValue);
            if (pKey > pNode->key) pNode->right = Put(pNode->right, pKey, pValue);
            else if (pKey < pNode->key) pNode->left = Put(pNode->left, pKey, pValue);
            else pNode->value = pValue;
            pNode->size = Size(pNode->left) + Size(pNode->right) + 1;
            return pNode;
        }

        NodePtr Min(NodePtr pNode) {
            if (pNode == nullptr) return nullptr;
            if (pNode->left == nullptr) return pNode;
            return Min(pNode->left);
        }

        NodePtr Min() {
            return Min(root);
        }

        NodePtr Max(NodePtr pNode) {
            if (pNode == nullptr) return nullptr;
            if (pNode->right == nullptr) return pNode;
            return Max(pNode->right);
        }

        NodePtr Max() {
            return Max(root);
        }

        NodePtr Floor(NodePtr pNode, const Key &pKey) {
            if (pNode == nullptr) return nullptr;
            if (pKey < pNode->key) return Floor(pNode->left, pKey);
            else if (pKey == pNode->key) return pNode;

            NodePtr lNode = Floor(pNode->right, pKey);
            if (lNode == nullptr) return pNode;
            return lNode;
        }

        NodePtr Celling(NodePtr pNode, const Key &pKey) {
            if (pNode == nullptr) return nullptr;

            if (pKey > pNode->key) return Celling(pNode->right, pKey);
            if (pKey == pNode->key) return pNode;

            NodePtr lNode = Celling(pNode->left, pKey);
            if (lNode == nullptr) return pNode;
            return lNode;
        }

        void Nodes(NodePtr &pNode, const Key &pMinKey, const Key &pMaxKey, deque<NodePtr> &rNodes) {
            if (pNode == nullptr) return;
            if (pMinKey < pNode->key) Nodes(pNode->left, pMinKey, pMaxKey, rNodes);
            if (pMinKey <= pNode->key and pNode->key <= pMaxKey) rNodes.push_back(pNode);
            if (pNode->key < pMaxKey) Nodes(pNode->right, pMinKey, pMaxKey, rNodes);
        }

        deque<NodePtr> Nodes(NodePtr &pNode, const Key &pMinKey, const Key &pMaxKey) {
            deque<NodePtr> lNodes;
            Nodes(pNode, pMinKey, pMaxKey, lNodes);
            return lNodes;
        }

        NodePtr Select(NodePtr &pNode, const int &pRank) {
            if (pNode == nullptr) return nullptr;
            int lSize = Size(pNode->left);
            if (pRank < lSize) return Select(pNode->left, pRank);
            else if (pRank > lSize) return Select(pNode->right, pRank - lSize - 1);  // -1 to count the pNode itself
            else return pNode;
        }

        int Rank(NodePtr &pNode, const Key &pKey) {
            if (pNode == nullptr) return -1;
            if (pKey < pNode->key) return Rank(pNode->left, pKey);
            else if (pKey > pNode->key) return Size(pNode->left) + 1 + Rank(pNode->right, pKey);
            return Size(pNode->left);
        }

        NodePtr DeleteMin(NodePtr &pNode) {
            if (pNode == nullptr) return nullptr;
            if (pNode->left == nullptr) return pNode->right;
            pNode->left = DeleteMin(pNode->left);
            pNode->size = Size(pNode->left) + 1 + Size(pNode->right);
            return pNode;
        }

        NodePtr DeleteMax(NodePtr &pNode) {
            if (pNode == nullptr) return nullptr;
            if (pNode->right == nullptr) return pNode->left;
            pNode->right = DeleteMax(pNode->right);
            pNode->size = Size(pNode->left) + 1 + Size(pNode->right);
            return pNode;
        }

        NodePtr Delete(NodePtr &pNode, const Key &key) {
            if (pNode == nullptr) return nullptr;
            if (key < pNode->key) pNode->left = Delete(pNode->left, key);
            else if (key > pNode->key) pNode->right = Delete(pNode->right, key);
            else {
                if (pNode->left == nullptr) return pNode->right;
                if (pNode->right == nullptr) return pNode->left;
                NodePtr lTmpNode = pNode;
                pNode = Min(pNode->right);
                pNode->right = DeleteMax(lTmpNode->right);
                pNode->left = lTmpNode->left;
            }
            pNode->size = Size(pNode->left) + 1 + Size(pNode->right);
            return pNode;
        }

        int MaxDepth(NodePtr &pNode) {
            if (pNode == nullptr) return 0;
            return max(MaxDepth(pNode->left), MaxDepth(pNode->right)) + 1;
        }

    public:
        int Size() { return Size(root); }

        bool Contains(Key pKey) {
            return Contains(root, pKey);
        }

        void Get(Key pKey, Value &rValue) {
            Get(root, pKey, rValue);
        }

        void Put(Key pKey, Value pValue) {
            root = Put(root, pKey, pValue);
        }

        void MinKey(Key &rKey) {
            NodePtr lMinNode = Min();
            if (lMinNode != nullptr) rKey = lMinNode->key;
        }

        void MinValue(Value &rValue) {
            NodePtr lMinNode = Min();
            if (lMinNode != nullptr) rValue = lMinNode->value;
        }

        void MaxKey(Key &rKey) {
            NodePtr lMaxNode = Max();
            if (lMaxNode != nullptr) rKey = lMaxNode->key;
        }

        void MaxValue(Value &rValue) {
            NodePtr lMaxNode = Max();
            if (lMaxNode != nullptr) rValue = lMaxNode->value;
        }

        void FloorKey(const Key &pKey, Key &rKey) {
            NodePtr lFloorNode = Floor(root, pKey);
            if (lFloorNode != nullptr) rKey = lFloorNode->key;
        }

        void FloorValue(const Key &pKey, Value &rValue) {
            NodePtr lFloorNode = Floor(root, pKey);
            if (lFloorNode != nullptr) rValue = lFloorNode->value;
        }

        void CellingKey(const Key &pKey, Key &rKey) {
            NodePtr lCellingNode = Celling(root, pKey);
            if (lCellingNode != nullptr) rKey = lCellingNode->key;
        }

        void CellingValue(const Key &pKey, Value &rValue) {
            NodePtr lCellingNode = Celling(root, pKey);
            if (lCellingNode != nullptr) rValue = lCellingNode->value;
        }

        void Keys(deque<Key> &rKeys) {
            deque<pair<Key, Value>> lPairs;
            Pairs(lPairs);
            for (pair<Key, Value> &fPair: lPairs) {
                rKeys.emplace_back(fPair.first);
            }
        }

        void Values(deque<Value> &rValues) {
            deque<pair<Key, Value>> lPairs;
            Pairs(lPairs);
            for (pair<Key, Value> &fPair: lPairs) {
                rValues.emplace_back(fPair.second);
            }
        }

        void Pairs(deque<pair<Key, Value>> &rPairs) {
            if (Size() == 0) return;

            Key lMinKey, lMaxKey;
            MinKey(lMinKey);
            MaxKey(lMaxKey);

            deque<NodePtr> lNodes = Nodes(root, lMinKey, lMaxKey);
            for (NodePtr &fNode: lNodes) {
                rPairs.emplace_back(fNode->key, fNode->value);
            }
        }

        void SelectKey(const int &pRank, Key &rKey) {
            NodePtr lNode = Select(root, pRank);
            if (lNode != nullptr) rKey = lNode->key;
        }

        void SelectValue(const int &pRank, Value &rValue) {
            NodePtr lNode = Select(root, pRank);
            if (lNode != nullptr) rValue = lNode->value;
        }

        void SelectPair(const int &pRank, pair<Key, Value> &rValue) {
            NodePtr lNode = Select(root, pRank);
            if (lNode != nullptr) rValue = {lNode->key, lNode->value};
        }

        int Rank(const Key &pKey) {
            return Rank(root, pKey);
        }

        void DeleteMin() {
            root = DeleteMin(root);
        }

        void DeleteMax() {
            root = DeleteMax(root);
        }

        void Delete(const Key &pKey) {
            root = Delete(root, pKey);
        }

        int MaxDepth() {
            return MaxDepth(root);
        }
    };
}

#endif //ALGS4_BST_HPP
