#pragma once
#include <iostream>
#include "FixHistogram.h"
#include "FloatingHistogram.h"
#include "HashTable.h"
#include "BalancedBinaryTree.h"

// Отображение FixHistogram
template <typename T>
void displayFixHistogram(const FixHistogram<T>& hist, std::ostream& os = std::cout) {
    DynamicArray<Pair<int, int>> pairs;
    hist.getInOrderPairs(pairs);
    int rangeSize = hist.getRangeSize();
    for (int i = 0; i < pairs.GetLength(); ++i) {
        int start = pairs.GetElem(i).key;
        int count = pairs.GetElem(i).value;
        int end = start + rangeSize;
        os << "[" << start << ";" << end << ") : " << count;
        if (i < pairs.GetLength() - 1) {
            os << ", ";
        }
    }
    os << "\n";
}

// Отображение FloatingHistogram
template <typename T>
void displayFloatingHistogram(const FloatingHistogram<T>& hist, std::ostream& os = std::cout) {
    DynamicArray<Pair<int, int>> pairs;
    hist.getInOrderPairs(pairs);
    for (int i = 0; i < pairs.GetLength(); i++) {
        int start = pairs.GetElem(i).key;
        int count = pairs.GetElem(i).value;
        int end = start + count - 1;
        os << "[" << start << ";" << end << "]: " << count << "\n";
    }
}

// Отображение HashTable
template <typename Key, typename Value>
void displayHashTable(const HashTable<Key, Value>& ht, std::ostream& os = std::cout) {
    DynamicArray<Pair<Key, Value>> pairs;
    ht.getAllPairs(pairs);
    for (int i = 0; i < pairs.GetLength(); i++) {
        os << "Key: " << pairs.GetElem(i).key << ", Value: " << pairs.GetElem(i).value << "\n";
    }
}

// Отображение BalancedBinaryTree
template <typename Key, typename Value>
void displayBalancedBinaryTree(const BalancedBinaryTree<Key, Value>& tree, std::ostream& os = std::cout) {
    DynamicArray<Pair<Key, Value>> pairs;
    tree.getInOrderPairs(pairs);
    for (int i = 0; i < pairs.GetLength(); i++) {
        os << "Key: " << pairs.GetElem(i).key << ", Value: " << pairs.GetElem(i).value << "\n";
    }
}
