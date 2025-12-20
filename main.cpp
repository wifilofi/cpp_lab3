#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include <nanobench.h>
#include <random>

#include "include/sort.h"

#include <fstream>

void show_int_sort()
{
    std::cout << "=== INT SORT ===\n";

    int arr[] = {3, 7, 2, 8, 6, 5, 3, 1};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Before: ";
    for (size_t i = 0; i < n; i++) std::cout << arr[i] << " ";
    std::cout << "\n";

    sort(arr, arr + n, [](int a, int b) { return a < b; });

    std::cout << "After: ";
    for (size_t i = 0; i < n; i++) std::cout << arr[i] << " ";
    std::cout << "\n\n";
}

void show_string_sort()
{
    std::cout << "=== STRING SORT ===\n";

    std::vector<std::string> strings = {"cat", "dog", "zebra", "dopsa", "psj", "itmo"};

    std::cout << "Before: ";
    for (const auto& f : strings) std::cout << f << " ";
    std::cout << "\n";

    sort(strings.begin(), strings.end());

    std::cout << "After:  ";
    for (const auto& f : strings) std::cout << f << " ";
    std::cout << "\n\n";
}

int main()
{
    show_int_sort();
    show_string_sort();
    //benchmark();

    return 0;
}
