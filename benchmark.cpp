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

        int iter = (size <= 10) ? 10000 : (size <= 30) ? 1000 : (size <= 50) ? 100 : 10;
        int iterations_insertion = iter;
        int iterations_quick = iter;

        // insert
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

        //quick sort
        {
            ankerl::nanobench::Bench b2;
            //bypas output
            b2.output(nullptr);
            b2.minEpochIterations(iterations_quick);
            b2.run([&]
            {
                auto copy = data;
                sort(copy.data(), copy.data() + size,
                     [](int32_t a, int32_t b) { return a < b; });
                ankerl::nanobench::doNotOptimizeAway(copy);
            });

            auto r2 = b2.results();
            if (!r2.empty())
            {
                quick_time = r2[0].median(ankerl::nanobench::Result::Measure::elapsed);
            }
        }

        insertion_file << insertion_time << "\n";
        quick_file << quick_time << "\n";

        if (size >= 10 && size <= 100 && insertion_time > 0 && quick_time > 0)
        {
            double ratio = insertion_time / quick_time;
            if (ratio < best_ratio)
            {
                best_ratio = ratio;
                best = size;
            }
        }
    }

    std::cout << best << std::endl;

    return 0;
}
