#pragma once
#include "DynamicArray.h"
#include "Person.h"
#include "BalancedBinaryTree.h"
#include "HashTable.h"
#include "FixHistogram.h"
#include "FloatingHistogram.h"
#include "Criteria.h"
#include "HashTable.h"
#include "BalancedBinaryTree.h"
#include <chrono>
#include <random>
#include <iostream>

int getRandomUniformInt(int minVal, int maxVal);
double getRandomUniformDouble(double minVal, double maxVal);
double getExponentialRandom(double lambda);

DynamicArray<int> generateUniformIntSequence(int size, int minVal, int maxVal);
DynamicArray<int> generateExponentialIntSequence(int size, double lambda);

double measureTimeHashTableFixed(const DynamicArray<int>& data, int minVal, int maxVal, int rangeCount);
double measureTimeBinaryTreeFixed(const DynamicArray<int>& data, int minVal, int maxVal, int rangeCount);

double measureTimeHashTableFloating(const DynamicArray<int>& data, int elementsPerRange);
double measureTimeBinaryTreeFloating(const DynamicArray<int>& data, int elementsPerRange);

void loadTestFixedHistogram(const DynamicArray<int>& data, int minVal, int maxVal, int rangeCount, double& timeHashTable, double& timeBinaryTree);
void loadTestFloatingHistogram(const DynamicArray<int>& data, int elementsPerRange, double& timeHashTable, double& timeBinaryTree);

void runLoadTests();

void printResultsTable(const DynamicArray<int>& elementCounts,
    const DynamicArray<double>& timesHashTableFixed,
    const DynamicArray<double>& timesBinaryTreeFixed,
    const DynamicArray<double>& timesHashTableFloating,
    const DynamicArray<double>& timesBinaryTreeFloating);
