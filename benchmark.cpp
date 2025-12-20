#include <cstdint>
#include <fstream>
#include <random>
#include <string>
#include <vector>
#include <iostream>

#include <nanobench.h>
#include "include/sort.h"

int main()
{
    std::ofstream insertion_file("insertion_results.txt");
    std::ofstream quick_file("quick_results.txt");
    std::ofstream hybrid_file("hybrid_results.txt");

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1000000);

    size_t best = 0;
    double best_ratio = 1e9;

    for (size_t size = 0; size <= 100; ++size)
    {
        std::vector<int32_t> data(size);
        for (size_t i = 0; i < size; ++i)
        {
            data[i] = dist(gen);
        }

        double insertion_time = 0.0;
        double quick_time = 0.0;
        double hybrid_time = 0.0;

        int iter = /*1000;*/
        (size <= 10) ? 10000 : (size <= 30) ? 1000 : (size <= 50) ? 100 : 10;
        int iterations_insertion = iter;
        int iterations_quick = iter;
        int iterations_hybrid = iter;

        // insertion sort
        if (size > 0)
        {
            ankerl::nanobench::Bench b1;
            b1.output(nullptr);
            b1.minEpochIterations(iterations_insertion);
            b1.run([&]
            {
                auto copy = data;
                insertion_sort(copy.data(), copy.data() + size,
                               [](int32_t a, int32_t b) { return a < b; });
                ankerl::nanobench::doNotOptimizeAway(copy);
            });

            auto r1 = b1.results();
            if (!r1.empty())
            {
                insertion_time = r1[0].median(ankerl::nanobench::Result::Measure::elapsed);
            }
        }

        // quick sort
        {
            ankerl::nanobench::Bench b2;
            b2.output(nullptr);
            b2.minEpochIterations(iterations_quick);
            b2.run([&]
            {
                auto copy = data;
                quick_sort(copy.data(), copy.data() + size,
                     [](int32_t a, int32_t b) { return a < b; });
                ankerl::nanobench::doNotOptimizeAway(copy);
            });

            auto r2 = b2.results();
            if (!r2.empty())
            {
                quick_time = r2[0].median(ankerl::nanobench::Result::Measure::elapsed);
            }
        }

        // hybrid sort
        {
            ankerl::nanobench::Bench b3;
            b3.output(nullptr);
            b3.minEpochIterations(iterations_hybrid);
            b3.run([&]
            {
                auto copy = data;
                hybrid_sort(copy.data(), copy.data() + size,
                     [](int32_t a, int32_t b) { return a < b; });
                ankerl::nanobench::doNotOptimizeAway(copy);
            });

            auto r3 = b3.results();
            if (!r3.empty())
            {
                hybrid_time = r3[0].median(ankerl::nanobench::Result::Measure::elapsed);
            }
        }

        insertion_file << insertion_time << "\n";
        quick_file << quick_time << "\n";
        hybrid_file << hybrid_time << "\n";

        if (size >= 10 && size <= 30 && insertion_time > 0 && quick_time > 0)
        {
            double ratio = insertion_time / quick_time;
            if (ratio < best_ratio)
            {
                best_ratio = ratio;
                best = size;
            }
        }
    }

    insertion_file.close();
    quick_file.close();
    hybrid_file.close();

    //std::cout << best << std::endl;

    return 0;
}