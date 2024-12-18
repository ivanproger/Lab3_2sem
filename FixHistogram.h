#pragma once
#include "Histogram.h"
#include "BalancedBinaryTree.h"
#include "DynamicArray.h"

template <typename T>
class FixHistogram : public Histogram {
private:
    BalancedBinaryTree<int, int>* tree;
    int minVal;
    int maxVal;
    int rangeCount;
    int rangeSize;
    int (*criterion)(const T&);

public:
    FixHistogram(int minVal, int maxVal, int rangeCount, int (*criterionFunc)(const T&))
        : minVal(minVal), maxVal(maxVal), rangeCount(rangeCount), criterion(criterionFunc) {
        tree = new BalancedBinaryTree<int, int>();
        int totalRange = maxVal - minVal;
        rangeSize = totalRange / rangeCount;
        if (totalRange % rangeCount != 0) {
            rangeSize += 1;
        }

        int start = minVal;
        for (int i = 0; i < rangeCount; i++) {
            tree->insert(start, 0);
            start += rangeSize;
        }
    }

    ~FixHistogram() {
        delete tree;
    }

    void addElement(const T& elem) {
        int value = criterion(elem);
        if (value < minVal || value >= maxVal) return;

        int idx = (value - minVal) / rangeSize;
        if (idx >= rangeCount)
            idx = rangeCount - 1;

        int start = minVal + idx * rangeSize;
        tree->insert(start, 1);
    }

    // Удаляем вывод отсюда. Теперь вывод осуществляется через Display.h
    void display(std::ostream& os) const override {
        // Пусто
    }

    void getInOrderPairs(DynamicArray<Pair<int, int>>& pairs) const {
        tree->getInOrderPairs(pairs);
    }

    int getMinVal() const { return minVal; }
    int getRangeSize() const { return rangeSize; }
    int getRangeCount() const { return rangeCount; }
};
