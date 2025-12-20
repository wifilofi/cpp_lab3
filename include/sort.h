//
// Created by gfn on 12/19/2025.
//

#ifndef CPP_LAB3_SORT_ALGORITHMS_H
#define CPP_LAB3_SORT_ALGORITHMS_H
#include <algorithm>

template <typename T, typename Compare>
void insertion_sort(T* first, T* last, Compare comp)
{
    for (T* i = first + 1; i < last; i++)
    {
        T* k = i - 1;
        while (k >= first && comp(*(k + 1), *k))
        {
            std::swap(*(k + 1), *k);
            k -= 1;
        }
    }
}

template <typename T, typename Compare>
T* median_of_three(T* a, T* b, T* c, Compare comp)
{
    //a < b
    if (comp(*a, *b))
    {
        //a < b < c
        if (comp(*b, *c))
        {
            return b;
        }

        //a < c < b
        if (comp(*a, *c))
        {
            return c;
        }

        //c < a < b
        return a;
    }

    //b <= a < c
    if (comp(*a, *c))
    {
        return a;
    }

    //b < c < a
    if (comp(*b, *c))
    {
        return c;
    }

    //c < b <=a
    return b;
}

template <typename T, typename Compare>
T* partition(T* first, T* last, Compare comp)
{
    T* mid = first + (last - first) / 2;
    T* pivot_ptr = median_of_three(first, mid, last - 1, comp);

    std::swap(*first, *pivot_ptr);
    T pivot = std::move(*first);

    T* i = first;
    T* k = last;

    while (true)
    {
        do
        {
            ++i;
        }
        while (i < last && comp(*i, pivot));

        do
        {
            --k;
        }
        while (k > first && comp(pivot, *k));

        if (i >= k) break;

        std::swap(*i, *k);
    }

    std::swap(*first, *k);
    return k;
}


template <typename T, typename Compare>
void sort(T* first, T* last, Compare comp)
{
    const std::ptrdiff_t INSERTION_SORT_THRESHOLD = 10;

    while (last - first > INSERTION_SORT_THRESHOLD)
    {
        T* pivot = partition(first, last, comp);

        std::ptrdiff_t left_len = pivot - first;
        std::ptrdiff_t right_len = (last - 1) - pivot;

        if (left_len < right_len)
        {
            sort(first, pivot, comp);
            first = pivot + 1;
        }
        else
        {
            sort(pivot + 1, last, comp);
            last = pivot;
        }
    }

    insertion_sort(first, last, comp);
}
#endif //CPP_LAB3_SORT_ALGORITHMS_H
