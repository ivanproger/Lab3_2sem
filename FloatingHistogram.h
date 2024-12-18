#pragma once
#include "Histogram.h"
#include "BalancedBinaryTree.h"
#include "DynamicArray.h"
#include <algorithm> // ��� std::swap

template <typename T>
class FloatingHistogram : public Histogram {
private:
    BalancedBinaryTree<int, int>* tree;
    int elementsPerRange;
    int (*criterion)(const T&);

    // ��������������� ����� ��� HeapSort
    void heapify(DynamicArray<int>& arr, int n, int i) const {
        int largest = i; // ������������� ����������� �������� ��� �����
        int l = 2 * i + 1; // ����� = 2*i + 1
        int r = 2 * i + 2; // ������ = 2*i + 2

        // ���� ����� �������� ������� ������ �����
        if (l < n && arr.GetElem(l) > arr.GetElem(largest))
            largest = l;

        // ���� ������ �������� ������� ������, ��� ����� ������� ������� �� ������ ������
        if (r < n && arr.GetElem(r) > arr.GetElem(largest))
            largest = r;

        // ���� ����� ������� ������� �� ������
        if (largest != i) {
            std::swap(arr.GetElem(i), arr.GetElem(largest));
            // ���������� �������� heapify ��� ���������
            heapify(arr, n, largest);
        }
    }

    // ����������� ���������� HeapSort
    void heapSort(DynamicArray<int>& arr) const {
        int n = arr.GetLength();

        // ���������� ���� (��������������� �������)
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);

        // ���� �� ������ ��������� �������� �� ����
        for (int i = n - 1; i > 0; i--) {
            // ���������� ������� ������ � �����
            std::swap(arr.GetElem(0), arr.GetElem(i));

            // �������� heapify �� ����������� ����
            heapify(arr, i, 0);
        }
    }

public:
    FloatingHistogram(const DynamicArray<T>& data, int elementsPerRange, int (*criterionFunc)(const T&))
        : elementsPerRange(elementsPerRange), criterion(criterionFunc) {
        tree = new BalancedBinaryTree<int, int>();

        DynamicArray<int> values;
        for (int i = 0; i < data.GetLength(); i++) {
            values.Append(criterionFunc(data.GetElem(i)));
        }

        // ��������� �������� � ������� HeapSort
        heapSort(values);

        int totalElements = values.GetLength();
        int index = 0;
        while (index < totalElements) {
            int startVal = values.GetElem(index);
            int count = 0;
            // ������������ ���������� ��������� � ���������
            for (int i = 0; i < elementsPerRange && (index + i) < totalElements; i++) {
                count++;
            }
            tree->insert(startVal, count);
            index += count;
        }
    }

    ~FloatingHistogram() {
        delete tree;
    }

    // ������� ����� ������. ������ ����� �������������� ����� Display.h
    void display(std::ostream& os) const override {
        // �����
    }

    void getInOrderPairs(DynamicArray<Pair<int, int>>& pairs) const {
        tree->getInOrderPairs(pairs);
    }

    int getElementsPerRange() const { return elementsPerRange; }
};
