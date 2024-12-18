#include "LoadTest.h"
#include "FixHistogram.h"
#include "FloatingHistogram.h"
#include "Criteria.h"
#include "HashTable.h"
#include "BalancedBinaryTree.h"
#include <chrono>
#include <random>
#include <iostream>
#include <iomanip> // Для форматирования вывода

// Функции генерации случайных чисел
int getRandomUniformInt(int minVal, int maxVal) {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(minVal, maxVal);
    return dist(gen);
}

double getRandomUniformDouble(double minVal, double maxVal) {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<double> dist(minVal, maxVal);
    return dist(gen);
}

double getExponentialRandom(double lambda) {
    static std::mt19937 gen(std::random_device{}());
    std::exponential_distribution<double> dist(lambda);
    return dist(gen);
}

// Генерация последовательности равномерно распределенных целых чисел
DynamicArray<int> generateUniformIntSequence(int size, int minVal, int maxVal) {
    DynamicArray<int> data;
    for (int i = 0; i < size; ++i) {
        data.Append(getRandomUniformInt(minVal, maxVal));
    }
    return data;
}

// Генерация последовательности экспоненциально распределенных целых чисел
DynamicArray<int> generateExponentialIntSequence(int size, double lambda) {
    DynamicArray<int> data;
    for (int i = 0; i < size; ++i) {
        double val = getExponentialRandom(lambda);
        int intVal = static_cast<int>(val);
        data.Append(intVal);
    }
    return data;
}

// Измерение времени для Fixed Histogram с использованием HashTable
double measureTimeHashTableFixed(const DynamicArray<int>& data, int minVal, int maxVal, int rangeCount) {
    auto start = std::chrono::high_resolution_clock::now();
    HashTable<int, int> hashTable(rangeCount * 2);

    int totalRange = maxVal - minVal;
    int rangeSize = totalRange / rangeCount;
    if (totalRange % rangeCount != 0)
        rangeSize += 1;

    for (int i = 0; i < rangeCount; i++) {
        int startVal = minVal + i * rangeSize;
        hashTable.insert(startVal, 0);
    }

    for (int i = 0; i < data.GetLength(); i++) {
        int value = data.GetElem(i);
        if (value < minVal || value >= maxVal) continue;
        int idx = (value - minVal) / rangeSize;
        if (idx >= rangeCount)
            idx = rangeCount - 1;
        int startVal = minVal + idx * rangeSize;

        int currentVal;
        if (hashTable.find(startVal, currentVal)) {
            hashTable.insert(startVal, 1);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(end - start).count();
}

// Измерение времени для Fixed Histogram с использованием BalancedBinaryTree
double measureTimeBinaryTreeFixed(const DynamicArray<int>& data, int minVal, int maxVal, int rangeCount) {
    auto start = std::chrono::high_resolution_clock::now();

    FixHistogram<int> fixHist(minVal, maxVal, rangeCount, numericCriterion);
    for (int i = 0; i < data.GetLength(); i++) {
        fixHist.addElement(data.GetElem(i));
    }

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(end - start).count();
}

// Измерение времени для Floating Histogram с использованием HashTable
double measureTimeHashTableFloating(const DynamicArray<int>& data, int elementsPerRange) {
    auto start = std::chrono::high_resolution_clock::now();

    FloatingHistogram<int> floatHist(data, elementsPerRange, numericCriterion);

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(end - start).count();
}

// Измерение времени для Floating Histogram с использованием BalancedBinaryTree
double measureTimeBinaryTreeFloating(const DynamicArray<int>& data, int elementsPerRange) {
    auto start = std::chrono::high_resolution_clock::now();

    FloatingHistogram<int> floatHist(data, elementsPerRange, numericCriterion);

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(end - start).count();
}

// Запуск нагрузочных тестов для Fixed Histogram
void loadTestFixedHistogram(const DynamicArray<int>& data, int minVal, int maxVal, int rangeCount, double& timeHashTable, double& timeBinaryTree) {
    timeHashTable = measureTimeHashTableFixed(data, minVal, maxVal, rangeCount);
    timeBinaryTree = measureTimeBinaryTreeFixed(data, minVal, maxVal, rangeCount);
}

// Запуск нагрузочных тестов для Floating Histogram
void loadTestFloatingHistogram(const DynamicArray<int>& data, int elementsPerRange, double& timeHashTable, double& timeBinaryTree) {
    timeHashTable = measureTimeHashTableFloating(data, elementsPerRange);
    timeBinaryTree = measureTimeBinaryTreeFloating(data, elementsPerRange);
}

// Печать результатов нагрузочных тестов с улучшенным форматированием таблицы
void printResultsTable(const DynamicArray<int>& elementCounts,
    const DynamicArray<double>& timesHashTableFixed,
    const DynamicArray<double>& timesBinaryTreeFixed,
    const DynamicArray<double>& timesHashTableFloating,
    const DynamicArray<double>& timesBinaryTreeFloating) {
    // Определение ширины столбцов
    const int width1 = 10;
    const int width2 = 18;
    const int width3 = 18;
    const int width4 = 20;
    const int width5 = 20;

    // Печать заголовков с линиями под ними
    std::cout << std::left << std::setw(width1) << "Elements"
        << "| " << std::left << std::setw(width2) << "HashTable Fixed"
        << "| " << std::left << std::setw(width3) << "BinaryTree Fixed"
        << "| " << std::left << std::setw(width4) << "HashTable Floating"
        << "| " << std::left << std::setw(width5) << "BinaryTree Floating"
        << "\n";

    std::cout << std::string(width1, '-') << "-+-"
        << std::string(width2, '-') << "-+-"
        << std::string(width3, '-') << "-+-"
        << std::string(width4, '-') << "-+-"
        << std::string(width5, '-')
        << "\n";

    // Печать строк таблицы
    for (int i = 0; i < elementCounts.GetLength(); i++) {
        std::cout << std::left << std::setw(width1) << elementCounts.GetElem(i)
            << "| " << std::left << std::setw(width2) << std::fixed << std::setprecision(4) << timesHashTableFixed.GetElem(i) << "s"
            << "| " << std::left << std::setw(width3) << std::fixed << std::setprecision(4) << timesBinaryTreeFixed.GetElem(i) << "s"
            << "| " << std::left << std::setw(width4) << std::fixed << std::setprecision(4) << timesHashTableFloating.GetElem(i) << "s"
            << "| " << std::left << std::setw(width5) << std::fixed << std::setprecision(4) << timesBinaryTreeFloating.GetElem(i) << "s"
            << "\n";
    }
}

// Основная функция запуск нагрузочных тестов
void runLoadTests() {
    DynamicArray<int> elementSizes;
    elementSizes.Append(1000);
    elementSizes.Append(5000);
    elementSizes.Append(10000);
    elementSizes.Append(50000);
    elementSizes.Append(100000);
    elementSizes.Append(500000);

    DynamicArray<double> timesHashTableFixed;
    DynamicArray<double> timesBinaryTreeFixed;
    DynamicArray<double> timesHashTableFloating;
    DynamicArray<double> timesBinaryTreeFloating;

    int minVal = 10;
    int maxVal = 100;
    int rangeCount = 10;
    int elementsPerRange = 2; // Соответствует вашему примеру
    double lambda = 1.0;

    for (int i = 0; i < elementSizes.GetLength(); i++) {
        int size = elementSizes.GetElem(i);
        std::cout << "Running tests for " << size << " elements...\n";

        // Генерация данных
        DynamicArray<int> uniformData = generateUniformIntSequence(size, minVal, maxVal);
        DynamicArray<int> exponentialData = generateExponentialIntSequence(size, lambda);

        // Объединение данных
        DynamicArray<int> combinedData;
        for (int j = 0; j < uniformData.GetLength(); j++) {
            combinedData.Append(uniformData.GetElem(j));
        }
        for (int j = 0; j < exponentialData.GetLength(); j++) {
            combinedData.Append(exponentialData.GetElem(j));
        }

        // Запуск тестов для Fixed Histogram
        double timeHTFixed, timeBTFixed;
        loadTestFixedHistogram(combinedData, minVal, maxVal, rangeCount, timeHTFixed, timeBTFixed);
        timesHashTableFixed.Append(timeHTFixed);
        timesBinaryTreeFixed.Append(timeBTFixed);

        // Запуск тестов для Floating Histogram
        double timeHTFloating, timeBTFloating;
        loadTestFloatingHistogram(combinedData, elementsPerRange, timeHTFloating, timeBTFloating);
        timesHashTableFloating.Append(timeHTFloating);
        timesBinaryTreeFloating.Append(timeBTFloating);

        std::cout << "Completed tests for " << size << " elements.\n\n";
    }

    // Печать всех результатов
    printResultsTable(elementSizes, timesHashTableFixed, timesBinaryTreeFixed, timesHashTableFloating, timesBinaryTreeFloating);
}
