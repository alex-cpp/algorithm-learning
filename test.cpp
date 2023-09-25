#include <iostream>   /// for IO operations
#include <vector>

#include "algorithm.h"


namespace sorting {
    namespace quick_sort {
        template <typename T>
        extern void show(const std::vector<T>& arr, const int& size);  // need to add the key word "exterrn", or it will call NULL fuction which defined in here

        template <typename T>
        extern void quick_sort(std::vector<T>* arr, const int& low, const int& high);
    } // namespacee quick_sort
}// namespace sorting


/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    int choice = 0;

    char x = 200, y = 300;
    std::cout << "char x = 200, actually it is " << int(x) << " char y = 300, actually it is " << int(y) << "\n";

    while (1) {
        std::cout << "\tAvailable modes\t\n\n";
        std::cout << "0. exit \n1. Self-tests Quick sort mode\n2. Interactive Quick sort mode\n3. test max and second";
        std::cout << "\n4. test FindCommon";
        int choiseMax = 4;

        std::cout << "\nChoose a mode: ";
        std::cin >> choice;
        std::cout << "\n";

        while ((choice < 0) || (choice > choiseMax)) {
            std::cout << "Invalid option. Choose between the valid modes: ";
            std::cin >> choice;
        }

        if (choice == 0) {
            std::cout << "exit, bye! \n";
            return 0;
        }

        if (choice == 1) {
            std::srand(std::time(nullptr));
            // by accident add void before function, it becames a new NULL function define
            testQuickSort();  // run self-test implementations
        }
        else if (choice == 2) {
            int size = 0;
            std::cout << "\nEnter the number of elements: ";

            std::cin >> size;
            std::vector<float> arr(size);

            std::cout
                << "\nEnter the unsorted elements (can be negative/decimal): ";

            for (int i = 0; i < size; ++i) {
                std::cout << "\n";
                std::cin >> arr[i];
            }
            sorting::quick_sort::quick_sort(&arr, 0, size - 1);
            std::cout << "\nSorted array: \n";
            sorting::quick_sort::show(arr, size);
        }
        else if (choice == 3) {
            testMaxandSecond();  // test max and  second
        }
        else if (choice == 4) {
            testFindCommon();  // test max and  second
        }

    }

    return 0;
}