#pragma once
#include "IDictionary.h"
#include "Pair.h"
#include "DynamicArray.h"
#include <algorithm>

template <typename Key, typename Value>
struct TreeNode {
    Pair<Key, Value>* pair;
    int height;
    TreeNode* left;
    TreeNode* right;

    TreeNode(Pair<Key, Value>* p)
        : pair(p), height(1), left(nullptr), right(nullptr) {}

    ~TreeNode() { delete pair; }
};

template <typename Key, typename Value>
class BalancedBinaryTree : public IDictionary<Key, Value> {
private:
    TreeNode<Key, Value>* root;

    int heightNode(TreeNode<Key, Value>* node) const {
        return node ? node->height : 0;
    }

    void updateNode(TreeNode<Key, Value>* node) {
        if (node) {
            node->height = 1 + std::max(heightNode(node->left), heightNode(node->right));
        }
    }

    int getBalance(TreeNode<Key, Value>* node) const {
        return node ? heightNode(node->left) - heightNode(node->right) : 0;
    }

    TreeNode<Key, Value>* rightRotate(TreeNode<Key, Value>* y) {
        TreeNode<Key, Value>* x = y->left;
        TreeNode<Key, Value>* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateNode(y);
        updateNode(x);

        return x;
    }

    TreeNode<Key, Value>* leftRotate(TreeNode<Key, Value>* x) {
        TreeNode<Key, Value>* y = x->right;
        TreeNode<Key, Value>* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateNode(x);
        updateNode(y);

        return y;
    }

    Key getNodeKey(TreeNode<Key, Value>* node) const {
        return node->pair->key;
    }

    TreeNode<Key, Value>* insertNode(TreeNode<Key, Value>* node, Pair<Key, Value>* pair) {
        if (!node)
            return new TreeNode<Key, Value>(pair);

        Key key = pair->key;
        Key nodeKey = getNodeKey(node);

        if (key < nodeKey)
            node->left = insertNode(node->left, pair);
        else if (key > nodeKey)
            node->right = insertNode(node->right, pair);
        else {
            node->pair->value += pair->value;
            delete pair;
            return node;
        }

        updateNode(node);

        int balance = getBalance(node);

        if (balance > 1 && key < getNodeKey(node->left))
            return rightRotate(node);

        if (balance < -1 && key > getNodeKey(node->right))
            return leftRotate(node);

        if (balance > 1 && key > getNodeKey(node->left)) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < getNodeKey(node->right)) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    TreeNode<Key, Value>* findNode(TreeNode<Key, Value>* node, const Key& key) const {
        if (!node)
            return nullptr;
        if (key < node->pair->key)
            return findNode(node->left, key);
        else if (key > node->pair->key)
            return findNode(node->right, key);
        else
            return node;
    }

    void collectInOrderPairs(TreeNode<Key, Value>* node, DynamicArray<Pair<Key, Value>>& pairs) const {
        if (!node)
            return;
        collectInOrderPairs(node->left, pairs);
        pairs.Append(*node->pair);
        collectInOrderPairs(node->right, pairs);
    }

    void clearTree(TreeNode<Key, Value>* node) {
        if (!node) return;
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }

public:
    BalancedBinaryTree() : root(nullptr) {}

    ~BalancedBinaryTree() {
        clearTree(root);
    }

    void insert(const Key& key, const Value& value) override {
        Pair<Key, Value>* pair = new Pair<Key, Value>(key, value);
        root = insertNode(root, pair);
    }

    bool find(const Key& key, Value& value) const override {
        TreeNode<Key, Value>* node = findNode(root, key);
        if (node) {
            value = node->pair->value;
            return true;
        }
        return false;
    }

    // Убираем вывод отсюда
    void display(std::ostream& os) const override {
        // Пусто, вывод перенесён в display.h
    }

    void getInOrderPairs(DynamicArray<Pair<Key, Value>>& pairs) const {
        collectInOrderPairs(root, pairs);
    }
};