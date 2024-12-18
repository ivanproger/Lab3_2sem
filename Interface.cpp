#include "Interface.h"
#include "FunctionalTest.h"
#include "FixHistogram.h"
#include "FloatingHistogram.h"
#include "Person.h"
#include "Criteria.h"
#include "DynamicArray.h"
#include "LoadTest.h"
#include "Display.h"
#include <iostream>
#include <limits>

void runInterface() {
    while (true) {
        std::cout << "Menu:\n";
        std::cout << "1. Run functional tests\n";
        std::cout << "2. Run load tests\n";
        std::cout << "3. Create FixHistogram\n";
        std::cout << "4. Create FloatingHistogram\n";
        std::cout << "5. Exit\n";
        std::cout << "Select: ";

        int choice;
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please try again.\n";
            continue;
        }

        if (choice == 1) {
            func(); // runFunctionalTests
        }
        else if (choice == 2) {
            std::cout << "Running Load Tests...\n";
            runLoadTests();
            std::cout << "Load Tests Completed.\n";
        }
        else if (choice == 3) {
            int minVal, maxVal, rangeCount;
            std::cout << "Enter minVal, maxVal, rangeCount: ";
            std::cin >> minVal >> maxVal >> rangeCount;
            if (std::cin.fail() || minVal >= maxVal || rangeCount <= 0) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid parameters. Please try again.\n";
                continue;
            }
            DynamicArray<int> data;
            std::cout << "Enter number of elements: ";
            int n; std::cin >> n;
            if (std::cin.fail() || n < 0) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid number of elements. Please try again.\n";
                continue;
            }
            std::cout << "Enter " << n << " integers:\n";
            for (int i = 0; i < n; i++) {
                int x; std::cin >> x;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input. Please enter integers only.\n";
                    data.Clear();
                    break;
                }
                data.Append(x);
            }
            if (data.GetLength() != n) {
                std::cout << "Data entry aborted due to invalid input.\n";
                continue;
            }
            FixHistogram<int> fixHist(minVal, maxVal, rangeCount, numericCriterion);
            for (int i = 0; i < data.GetLength(); i++) {
                fixHist.addElement(data.GetElem(i));
            }
            std::cout << "FixHistogram:\n";
            displayFixHistogram(fixHist, std::cout);
            std::cout << "--------------------------------------\n";
        }
        else if (choice == 4) {
            int elementsPerRange;
            std::cout << "Enter elementsPerRange: ";
            std::cin >> elementsPerRange;
            if (std::cin.fail() || elementsPerRange <= 0) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid elementsPerRange. Please try again.\n";
                continue;
            }
            std::cout << "Enter number of elements: ";
            int n; std::cin >> n;
            if (std::cin.fail() || n < 0) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid number of elements. Please try again.\n";
                continue;
            }
            std::cout << "Enter " << n << " integers:\n";
            DynamicArray<int> data;
            for (int i = 0; i < n; i++) {
                int x; std::cin >> x;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input. Please enter integers only.\n";
                    data.Clear();
                    break;
                }
                data.Append(x);
            }
            if (data.GetLength() != n) {
                std::cout << "Data entry aborted due to invalid input.\n";
                continue;
            }
            FloatingHistogram<int> floatHist(data, elementsPerRange, numericCriterion);
            std::cout << "FloatingHistogram:\n";
            displayFloatingHistogram(floatHist, std::cout);
            std::cout << "--------------------------------------\n";
        }
        else if (choice == 5) {
            std::cout << "Exiting...\n";
            break;
        }
        else {
            std::cout << "Invalid choice. Please select from the menu.\n";
        }
    }
}
