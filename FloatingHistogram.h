#pragma once
#include "Histogram.h"
#include "BalancedBinaryTree.h"
#include "DynamicArray.h"
#include <algorithm> // Для std::swap

template <typename T>
class FloatingHistogram : public Histogram {
private:
    BalancedBinaryTree<int, int>* tree;
    int elementsPerRange;
    int (*criterion)(const T&);

    // Вспомогательный метод для HeapSort
    void heapify(DynamicArray<int>& arr, int n, int i) const {
        int largest = i; // Инициализация наибольшего элемента как корня
        int l = 2 * i + 1; // левый = 2*i + 1
        int r = 2 * i + 2; // правый = 2*i + 2

        // Если левый дочерний элемент больше корня
        if (l < n && arr.GetElem(l) > arr.GetElem(largest))
            largest = l;

        // Если правый дочерний элемент больше, чем самый большой элемент на данный момент
        if (r < n && arr.GetElem(r) > arr.GetElem(largest))
            largest = r;

        // Если самый большой элемент не корень
        if (largest != i) {
            std::swap(arr.GetElem(i), arr.GetElem(largest));
            // Рекурсивно вызываем heapify для поддерева
            heapify(arr, n, largest);
        }
    }

    // Итеративная реализация HeapSort
    void heapSort(DynamicArray<int>& arr) const {
        int n = arr.GetLength();

        // Построение кучи (перегруппировка массива)
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);

        // Один за другим извлекаем элементы из кучи
        for (int i = n - 1; i > 0; i--) {
            // Перемещаем текущий корень в конец
            std::swap(arr.GetElem(0), arr.GetElem(i));

            // Вызываем heapify на уменьшенной куче
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

        // Сортируем значения с помощью HeapSort
        heapSort(values);

        int totalElements = values.GetLength();
        int index = 0;
        while (index < totalElements) {
            int startVal = values.GetElem(index);
            int count = 0;
            // Подсчитываем количество элементов в диапазоне
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

    // Удаляем вывод отсюда. Теперь вывод осуществляется через Display.h
    void display(std::ostream& os) const override {
        // Пусто
    }

    void getInOrderPairs(DynamicArray<Pair<int, int>>& pairs) const {
        tree->getInOrderPairs(pairs);
    }

    int getElementsPerRange() const { return elementsPerRange; }
};
