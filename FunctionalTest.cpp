#include "FunctionalTest.h"
#include "FixHistogram.h"
#include "FloatingHistogram.h"
#include "Person.h"
#include "Criteria.h"
#include "HashTable.h"
#include "BalancedBinaryTree.h"
#include "DynamicArray.h"
#include "Display.h"
#include <iostream>
#include <cassert>

void buildNumericHistograms() {
    // Создание и тестирование FixHistogram
    DynamicArray<int> elements;
    elements.Append(10);
    elements.Append(12);
    elements.Append(13);
    elements.Append(15);
    elements.Append(17);

    FixHistogram<int> fixHist(10, 20, 2, numericCriterion); // Диапазоны: [10;15), [15;20)
    for (int i = 0; i < elements.GetLength(); i++) {
        fixHist.addElement(elements.GetElem(i));
    }

    // Проверка корректности
    DynamicArray<Pair<int, int>> pairs;
    fixHist.getInOrderPairs(pairs);
    assert(pairs.GetLength() == 2);
    assert(pairs.GetElem(0).key == 10);
    assert(pairs.GetElem(0).value == 3); // 10,12,13
    assert(pairs.GetElem(1).key == 15);
    assert(pairs.GetElem(1).value == 2); // 15,17

    // Отображение гистограммы
    std::cout << "Numeric FixHistogram:\n";
    displayFixHistogram(fixHist, std::cout);
    std::cout << "--------------------------------------\n";

    // Создание и тестирование FloatingHistogram
    FloatingHistogram<int> floatHist(elements, 2, numericCriterion); // Группировка по 2 элемента
    // Ожидаемый вывод:
    // [10;11]:2 (10,12)
    // [13;14]:2 (13,15)
    // [17;17]:1 (17)

    // Проверка корректности
    DynamicArray<Pair<int, int>> floatPairs;
    floatHist.getInOrderPairs(floatPairs);
    assert(floatPairs.GetLength() == 3);
    assert(floatPairs.GetElem(0).key == 10);
    assert(floatPairs.GetElem(0).value == 2);
    assert(floatPairs.GetElem(1).key == 13);
    assert(floatPairs.GetElem(1).value == 2);
    assert(floatPairs.GetElem(2).key == 17);
    assert(floatPairs.GetElem(2).value == 1);

    // Отображение гистограммы
    std::cout << "Numeric FloatingHistogram:\n";
    displayFloatingHistogram(floatHist, std::cout);
    std::cout << "--------------------------------------\n";
}

void buildHeightHistograms() {
    // Создание и тестирование FixHistogram для Person
    DynamicArray<Person> people;
    people.Append(Person(1, "Smith", "John", 1990, 180.0, 75.0));
    people.Append(Person(2, "Doe", "Jane", 1985, 165.0, 60.0));
    people.Append(Person(3, "Brown", "Charlie", 2000, 170.0, 68.0));
    people.Append(Person(4, "Davis", "Alice", 1995, 160.0, 55.0));
    people.Append(Person(5, "Wilson", "Bob", 1988, 175.0, 70.0));

    FixHistogram<Person> fixHist(150, 200, 5, heightCriterion); // Диапазоны: [150;160), [160;170), [170;180), [180;190), [190;200)
    for (int i = 0; i < people.GetLength(); i++) {
        fixHist.addElement(people.GetElem(i));
    }

    // Проверка корректности
    DynamicArray<Pair<int, int>> pairs;
    fixHist.getInOrderPairs(pairs);
    assert(pairs.GetLength() == 5);
    // Дополнительные проверки можно добавить здесь

    // Отображение гистограммы
    std::cout << "Height FixHistogram:\n";
    displayFixHistogram(fixHist, std::cout);
    std::cout << "--------------------------------------\n";

    // Создание и тестирование FloatingHistogram для Person
    FloatingHistogram<Person> floatHist(people, 2, heightCriterion); // Группировка по 2 элемента
    // Ожидаемый вывод (на основе высот): [160;165]:2 (160,165), [170;175]:2 (170,175), [180;180]:1 (180)

    // Проверка корректности
    DynamicArray<Pair<int, int>> floatPairs;
    floatHist.getInOrderPairs(floatPairs);
    assert(floatPairs.GetLength() == 3);
    assert(floatPairs.GetElem(0).key == 160);
    assert(floatPairs.GetElem(0).value == 2); // 160,165
    assert(floatPairs.GetElem(1).key == 170);
    assert(floatPairs.GetElem(1).value == 2); // 170,175
    assert(floatPairs.GetElem(2).key == 180);
    assert(floatPairs.GetElem(2).value == 1); // 180

    // Отображение гистограммы
    std::cout << "Height FloatingHistogram:\n";
    displayFloatingHistogram(floatHist, std::cout);
    std::cout << "--------------------------------------\n";
}

void testHashTable() {
    HashTable<int, int> ht(10);
    ht.insert(5, 1);
    ht.insert(15, 1);
    ht.insert(25, 1);
    int val;
    assert(ht.find(5, val) && val == 1);
    assert(ht.find(15, val) && val == 1);
    assert(ht.find(25, val) && val == 1);
    std::cout << "HashTable tests: OK\n";
}

void testBalancedBinaryTree() {
    BalancedBinaryTree<int, int> tree;
    tree.insert(10, 1);
    tree.insert(20, 2);
    tree.insert(5, 3);
    int val;
    assert(tree.find(10, val) && val == 1);
    assert(tree.find(20, val) && val == 2);
    assert(tree.find(5, val) && val == 3);
    std::cout << "BalancedBinaryTree tests: OK\n";
}

void runFunctionalTests() {
    // Тестируем гистограммы
    buildNumericHistograms();
    buildHeightHistograms();

    // Тестируем хеш-таблицу и бинарное дерево
    testHashTable();
    testBalancedBinaryTree();

    std::cout << "All functional tests passed: OK\n";
}

void func() {
    runFunctionalTests();
}
