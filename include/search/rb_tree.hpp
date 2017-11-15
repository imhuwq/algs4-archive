//
// Created by john on 11/14/17.
//

#ifndef ALGS4_RB_TREE_HPP
#define ALGS4_RB_TREE_HPP

#include <memory>
#include <vector>
#include <algorithm>

using namespace std;

namespace search {
    template<typename Key, typename Value>
    class RBTree {
    private:
        class Node;

        typedef bool Color;
        const static bool RED = true;
        const static bool BLACK = false;
        typedef shared_ptr<Node> NodePtr;

        class Node {
        public:
            Node(const Key &pKey, const Value &pValue) : key(pKey), value(pValue) {}

            Key key;
            Value value;
            int size = 1;
            NodePtr left = nullptr;
            NodePtr right = nullptr;
            Color color = RED;
        };

        NodePtr root = nullptr;

        int Size(NodePtr &pNode) {
            if (pNode == nullptr) return 0;
            return pNode->size;
        }

        bool Contains(NodePtr &pNode, const Key &pKey) {
            if (pNode == nullptr) return false;
            if (pKey < pNode->key) return Contains(pNode->left, pKey);
            if (pKey > pNode->key) return Contains(pNode->right, pKey);
            return true;
        }

        bool Get(NodePtr &pNode, const Key &pKey, Value &rValue) {
            if (pNode == nullptr) return false;
            if (pKey < pNode->key) return Get(pNode->left, pKey, rValue);
            if (pKey > pNode->key) return Get(pNode->right, pKey, rValue);
            rValue = pNode->value;
            return true;
        }

        bool IsRed(NodePtr &pNode) {
            return pNode != nullptr and pNode->color;
        }

        NodePtr RotateLeft(NodePtr &pNode) {
            if (pNode == nullptr) return pNode;

            NodePtr rNode = pNode->right;
            pNode->right = rNode->left;
            rNode->left = pNode;

            rNode->size = pNode->size;
            pNode->size = Size(pNode->left) + 1 + Size(pNode->right);

            rNode->color = pNode->color;
            pNode->color = RED;
            return rNode;
        }

        NodePtr RotateRight(NodePtr &pNode) {
            if (pNode == nullptr) return pNode;

            NodePtr rNode = pNode->left;
            pNode->left = rNode->right;
            rNode->right = pNode;

            rNode->size = pNode->size;
            pNode->size = Size(pNode->left) + 1 + Size(pNode->right);

            rNode->color = pNode->color;
            pNode->color = RED;
            return rNode;
        }

        NodePtr FlipColors(NodePtr &pNode) {
            pNode->left->color = !pNode->left->color;
            pNode->right->color = !pNode->right->color;
            pNode->color = !pNode->color;
            return pNode;
        }

        NodePtr Balance(NodePtr &pNode) {
            if (pNode == nullptr) return pNode;

            // if (!IsRed(pNode->left) and IsRed(pNode->right))
            if (IsRed(pNode->right)) {
                pNode = RotateLeft(pNode);
            }
            if (IsRed(pNode->left) and IsRed(pNode->left->left)) {
                pNode = RotateRight(pNode);
            }

            if (IsRed(pNode->left) and IsRed(pNode->right)) {
                pNode = FlipColors(pNode);
            }

            pNode->size = Size(pNode->left) + 1 + Size(pNode->right);

            return pNode;
        }

        NodePtr Put(NodePtr &pNode, const Key &pKey, const Value &pValue) {
            if (pNode == nullptr) return make_shared<Node>(pKey, pValue);

            if (pKey == pNode->key) pNode->value = pValue;
            else if (pKey < pNode->key) pNode->left = Put(pNode->left, pKey, pValue);
            else pNode->right = Put(pNode->right, pKey, pValue);

            if (!IsRed(pNode->left) and IsRed(pNode->right)) pNode = RotateLeft(pNode);
            if (IsRed(pNode->left) and IsRed(pNode->left->left)) pNode = RotateRight(pNode);
            if (IsRed(pNode->left) and IsRed(pNode->right)) pNode = FlipColors(pNode);

            int size = Size(pNode->left) + 1 + Size(pNode->right);
            pNode->size = size;
            return pNode;
        }

        NodePtr Max(NodePtr &pNode) {
            if (pNode == nullptr) return pNode;
            if (pNode->right != nullptr) return Max(pNode->right);
            return pNode;
        }

        NodePtr Max() {
            return Max(root);
        }

        NodePtr Min(NodePtr &pNode) {
            if (pNode == nullptr) return pNode;
            if (pNode->left != nullptr) return Min(pNode->left);
            return pNode;
        }

        NodePtr Min() {
            return Min(root);
        }

        void Keys(NodePtr &pNode, const Key &pMinKey, const Key &pMaxKey, vector<Key> &rKeys) {
            if (pNode == nullptr) return;
            if (pMinKey < pNode->key) Keys(pNode->left, pMinKey, pMaxKey, rKeys);
            if (pMinKey <= pNode->key and pNode->key <= pMaxKey) rKeys.emplace_back(pNode->key);
            if (pNode->key < pMaxKey) Keys(pNode->right, pMinKey, pMaxKey, rKeys);
        }

        void Keys(NodePtr &pNode, vector<Key> &rKeys) {
            Key lMin, lMax;
            MinKey(lMin);
            MaxKey(lMax);
            Keys(pNode, lMin, lMax, rKeys);
        }

        void Values(NodePtr &pNode, const Key &pMinKey, const Key &pMaxKey, vector<Value> &rValues) {
            if (pNode == nullptr) return;
            if (pMinKey < pNode->key) Values(pNode->left, pMinKey, pMaxKey, rValues);
            if (pMinKey <= pNode->key and pNode->key <= pMaxKey) rValues.emplace_back(pNode->value);
            if (pNode->key < pMaxKey) Values(pNode->right, pMinKey, pMaxKey, rValues);
        }

        void Values(NodePtr &pNode, vector<Value> &rValues) {
            Key lMin, lMax;
            MinKey(lMin);
            MaxKey(lMax);
            Values(pNode, lMin, lMax, rValues);
        }

        void Items(NodePtr &pNode, const Key &pMinKey, const Key &pMaxKey, vector<pair<Key, Value>> &rItems) {
            if (pNode == nullptr) return;
            if (pMinKey < pNode->key) Items(pNode->left, pMinKey, pMaxKey, rItems);
            if (pMinKey <= pNode->key and pNode->key <= pMaxKey) rItems.emplace_back(pNode->key, pNode->value);
            if (pNode->key < pMaxKey) Items(pNode->right, pMinKey, pMaxKey, rItems);
        }

        void Items(NodePtr &pNode, vector<pair<Key, Value>> &rItems) {
            Key lMin, lMax;
            MinKey(lMin);
            MaxKey(lMax);
            Items(pNode, lMin, lMax, rItems);
        }

        NodePtr MoveRedLeft(NodePtr &pNode) {
            pNode = FlipColors(pNode);
            if (IsRed(pNode->right->left)) {
                pNode->right = RotateRight(pNode->right);
                pNode = RotateLeft(pNode);
                pNode = FlipColors(pNode);
            }
            return pNode;
        }

        NodePtr MoveRedRight(NodePtr &pNode) {
            pNode = FlipColors(pNode);
            if (IsRed(pNode->left->left)) {
                pNode = RotateRight(pNode);
                pNode = FlipColors(pNode);
            }
            return pNode;
        }

        NodePtr DeleteMin(NodePtr &pNode) {
            if (pNode == nullptr) return pNode;
            if (pNode->left == nullptr) return pNode->left;

            if (!IsRed(pNode->left) and !IsRed(pNode->left->left)) {
                pNode = MoveRedLeft(pNode);
            }

            pNode->left = DeleteMin(pNode->left);
            pNode = Balance(pNode);
            return pNode;
        }

        NodePtr DeleteMax(NodePtr &pNode) {
            if (pNode == nullptr) return pNode;

            if (IsRed(pNode->left)) pNode = RotateRight(pNode);
            if (pNode->right == nullptr) return pNode->right;

            if (!IsRed(pNode->right) and !IsRed(pNode->right->left)) {
                pNode = MoveRedRight(pNode);
            }

            pNode->right = DeleteMax(pNode->right);
            pNode = Balance(pNode);
            return pNode;
        }

        NodePtr Delete(NodePtr &pNode, const Key &pKey) {
            if (pNode == nullptr) return pNode;

            if (pKey < pNode->key) {
                if (!IsRed(pNode->left) and !IsRed(pNode->left->left)) pNode = MoveRedLeft(pNode);
                pNode->left = Delete(pNode->left, pKey);
            } else {
                if (IsRed(pNode->left)) pNode = RotateRight(pNode);
                if (pKey == pNode->key and pNode->right == nullptr) return pNode->right;
                if (!IsRed(pNode->right) and !IsRed(pNode->right->left)) pNode = MoveRedRight(pNode);
                if (pKey == pNode->key) {
                    NodePtr &lMinNode = Min(pNode->right);
                    pNode->key = lMinNode->key;
                    pNode->value = lMinNode->value;
                    pNode->right = DeleteMin(pNode->right);
                } else {
                    pNode->right = Delete(pNode->right, pKey);
                }
            }
            pNode = Balance(pNode);
            return pNode;
        }

        int MaxDepth(const NodePtr &pNode) {
            if (pNode == nullptr) return 0;
            return max(MaxDepth(pNode->left), MaxDepth(pNode->right)) + 1;
        }

    public:
        int Size() {
            return Size(root);
        }

        bool Contains(const Key &pKey) {
            return Contains(root, pKey);
        }

        bool Get(const Key &pKey, Value &rvalue) {
            return Get(root, pKey, rvalue);
        }

        void Put(const Key &pKey, const Value &pValue) {
            root = Put(root, pKey, pValue);
            root->color = BLACK;
        }

        bool MaxKey(Key &rKey) {
            NodePtr lNode = Max();
            if (lNode == nullptr) return false;
            rKey = lNode->key;
            return true;
        }

        bool MinKey(Key &rKey) {
            NodePtr lNode = Min();
            if (lNode == nullptr) return false;
            rKey = lNode->key;
            return true;

        }

        bool MaxValue(Value &rValue) {
            NodePtr &lNode = Max();
            if (lNode == nullptr) return false;
            rValue = lNode->value;
            return true;

        }

        bool MinValue(Value &rValue) {
            NodePtr &lNode = Min();
            if (lNode == nullptr) return false;
            rValue = lNode->value;
            return true;

        }

        bool MaxItem(Key &rKey, Value &rValue) {
            NodePtr &lNode = Max();
            if (lNode == nullptr) return false;
            rKey = lNode->key;
            rValue = lNode->value;
            return true;

        }

        bool MinItem(Key &rKey, Value &rValue) {
            NodePtr &lNode = Min();
            if (lNode == nullptr) return false;
            rKey = lNode->key;
            rValue = lNode->value;
            return true;
        }

        bool Keys(vector<Key> &rKeys) {
            Keys(root, rKeys);
        }

        bool Values(vector<Value> &rValues) {
            Values(root, rValues);
        }

        bool Items(vector<pair<Key, Value>> &rItems) {
            Items(root, rItems);
        }

        void DeleteMin() {
            if (root == nullptr) return;
            if (!IsRed(root->left) and !IsRed(root->right)) {
                root->color = RED;
            }
            root = DeleteMin(root);
            if (root != nullptr) root->color = BLACK;
        }

        void DeleteMax() {
            if (root == nullptr) return;
            if (!IsRed(root->left) and !IsRed(root->right)) {
                root->color = RED;
            }
            root = DeleteMax(root);
            if (root != nullptr) root->color = BLACK;
        }

        void Delete(const Key &pKey) {
            if (root == nullptr) return;

            if (!IsRed(root->left) and !IsRed(root->right)) root->color = RED;
            root = Delete(root, pKey);
            if (root != nullptr) root->color = BLACK;
        }

        int MaxDepth() {
            return MaxDepth(root);
        }

    };
}

#endif //ALGS4_RB_TREE_HPP
