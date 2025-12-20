#include "gtest/gtest.h"
#include <algorithm>
#include <random>
#include <vector>
#include <string>
#include <cstdint>

#include "include/sort.h"

TEST(SortingAlgorithm, HandlesEmptyContainers) {
    std::vector<int> empty_vec;
    sort(empty_vec.begin(), empty_vec.end(), std::less<int>());
    EXPECT_TRUE(empty_vec.empty());
    
    int* null_array = nullptr;
    quick_sort(null_array, null_array, std::less<int>());
    SUCCEED();
}

TEST(SortingAlgorithm, HandlesSingleElement) {
    std::vector<int> single = {42};
    std::vector<int> expected = single;
    
    sort(single.begin(), single.end(), std::less<int>());
    
    EXPECT_EQ(single.size(), 1);
    EXPECT_EQ(single[0], 42);
    EXPECT_TRUE(std::is_sorted(single.begin(), single.end()));
}

TEST(SortingAlgorithm, PreservesSortedOrder) {
    std::vector<int> sorted = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> expected = sorted;
    
    sort(sorted.begin(), sorted.end(), std::less<int>());
    
    EXPECT_EQ(sorted, expected);
    EXPECT_TRUE(std::is_sorted(sorted.begin(), sorted.end()));
}

TEST(SortingAlgorithm, SortsReverseOrder) {
    std::vector<int> reversed = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    sort(reversed.begin(), reversed.end(), std::less<int>());
    
    EXPECT_EQ(reversed, expected);
    EXPECT_TRUE(std::is_sorted(reversed.begin(), reversed.end()));
}

TEST(SortingAlgorithm, HandlesDuplicateElements) {
    std::vector<int> duplicates(100, 7);
    std::vector<int> expected = duplicates;
    
    sort(duplicates.begin(), duplicates.end(), std::less<int>());
    
    EXPECT_EQ(duplicates, expected);
    EXPECT_TRUE(std::is_sorted(duplicates.begin(), duplicates.end()));
}

TEST(SortingAlgorithm, SortsRandomIntegers) {
    const int NUM_ELEMENTS = 1000;
    std::vector<int> random_data(NUM_ELEMENTS);
    
    std::mt19937 generator(42);
    std::uniform_int_distribution<int> distribution(-10000, 10000);
    
    for (int& value : random_data) {
        value = distribution(generator);
    }
    
    std::vector<int> reference = random_data;
    std::sort(reference.begin(), reference.end());
    
    sort(random_data.begin(), random_data.end(), std::less<int>());
    
    EXPECT_EQ(random_data, reference);
    EXPECT_TRUE(std::is_sorted(random_data.begin(), random_data.end()));
}


TEST(SortingAlgorithm, SortsWithCustomComparator) {
    std::vector<int> data = {1, 5, 3, 9, 2, 8, 4, 7, 6, 0};
    std::vector<int> expected_descending = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    auto descending_comparator = [](int a, int b) { return a > b; };
    sort(data.begin(), data.end(), descending_comparator);
    
    EXPECT_EQ(data, expected_descending);
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end(), descending_comparator));
}


TEST(SortingAlgorithm, SortsStringData) {
    std::vector<std::string> words = {
        "itmo", "cpp", "balatro", "cat", "aphex twin", "alchemy"
    };
    
    std::vector<std::string> expected = words;
    std::sort(expected.begin(), expected.end());
    
    sort(words.begin(), words.end(), std::less<std::string>());
    
    EXPECT_EQ(words, expected);
    EXPECT_TRUE(std::is_sorted(words.begin(), words.end()));
}

TEST(SortingAlgorithm, SortsStringsByLength) {
    std::vector<std::string> words = {"elephant", "cat", "mouse", "dog", "hippopotamus"};
    std::vector<std::string> expected = {"cat", "dog", "mouse", "elephant", "hippopotamus"};
    
    auto length_comparator = [](const std::string& a, const std::string& b) {
        return a.length() < b.length();
    };
    
    sort(words.begin(), words.end(), length_comparator);
    
    EXPECT_EQ(words, expected);
    EXPECT_TRUE(std::is_sorted(words.begin(), words.end(), length_comparator));
}

TEST(SortingAlgorithm, HandlesLargeDataSet) {
    const int LARGE_SIZE = 10000;
    std::vector<int> large_data(LARGE_SIZE);
    
    std::mt19937 rng(12345);
    std::uniform_int_distribution<int> dist(1, 1000000);
    
    for (int& val : large_data) {
        val = dist(rng);
    }
    
    std::vector<int> reference = large_data;
    std::sort(reference.begin(), reference.end());
    
    sort(large_data.begin(), large_data.end(), std::less<int>());
    
    EXPECT_EQ(large_data, reference);
    EXPECT_TRUE(std::is_sorted(large_data.begin(), large_data.end()));
}

TEST(SortingAlgorithm, HandlesMixedSignNumbers) {
    std::vector<int> mixed = {-5, 10, -3, 0, 7, -8, 2, -1, 4, -6};
    std::vector<int> expected = {-8, -6, -5, -3, -1, 0, 2, 4, 7, 10};
    
    sort(mixed.begin(), mixed.end(), std::less<int>());
    
    EXPECT_EQ(mixed, expected);
    EXPECT_TRUE(std::is_sorted(mixed.begin(), mixed.end()));
}

TEST(SortingAlgorithm, HandlesPartiallySortedData) {
    // Данные, где первые 5 элементов отсортированы, остальные - нет
    std::vector<int> partially_sorted = {1, 2, 3, 4, 5, 9, 8, 7, 6, 0};
    std::vector<int> expected = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    sort(partially_sorted.begin(), partially_sorted.end(), std::less<int>());
    
    EXPECT_EQ(partially_sorted, expected);
    EXPECT_TRUE(std::is_sorted(partially_sorted.begin(), partially_sorted.end()));
}

TEST(SortingAlgorithm, WorksWithDifferentNumericTypes) {
    std::vector<double> doubles = {3.14, 2.71, 1.41, 1.62, 0.58};
    std::vector<double> expected = {0.58, 1.41, 1.62, 2.71, 3.14};
    
    sort(doubles.begin(), doubles.end(), std::less<double>());
    
    EXPECT_EQ(doubles.size(), expected.size());
    for (size_t i = 0; i < doubles.size(); ++i) {
        EXPECT_DOUBLE_EQ(doubles[i], expected[i]);
    }
    
    EXPECT_TRUE(std::is_sorted(doubles.begin(), doubles.end()));
}

TEST(SortingAlgorithm, HandlesLongStrings) {
    std::vector<std::string> long_strings;

    for (int i = 0; i < 100; ++i) {
        long_strings.push_back(std::string(i % 10 + 1, 'A' + (i % 26)));
    }
    
    std::vector<std::string> reference = long_strings;
    std::sort(reference.begin(), reference.end());
    
    sort(long_strings.begin(), long_strings.end(), std::less<std::string>());
    
    EXPECT_EQ(long_strings, reference);
    EXPECT_TRUE(std::is_sorted(long_strings.begin(), long_strings.end()));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}