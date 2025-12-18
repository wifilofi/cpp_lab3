//
// Created by gfn on 12/19/2025.
//

#ifndef CPP_LAB3_SORT_ALGORITHMS_H
#define CPP_LAB3_SORT_ALGORITHMS_H
#include <algorithm>


class sort_algorithms
{
};

template <typename T>
inline void MoveSwap(T& a, T& b)
{
    T Tmp = std::move(a);
    a = std::move(b);
    b = std::move(Tmp);
}

template <typename T, typename Compare>
void InsertionSort(T* first, T* last, Compare comp)
{
    if (first >= last) return;
    for (T* It = first + 1; It < last; ++It)
    {
        T Key = std::move(*It);
        T* J = It;
        while (J > first && comp(Key, *(J - 1)))
        {
            *J = std::move(*(J - 1));
            --J;
        }
        *J = std::move(Key);
    }
}

template <typename T, typename Compare>
T* MedianOfThree(T* a, T* b, T* c, Compare comp)
{
    if (comp(*a, *b))
    {
        if (comp(*b, *c))
        {
            return b;
        }

        else if (comp(*a, *c))
        {
            return c;
        }

        else
        {
            return a;
        }
    }

    else
    {
        if (comp(*a, *c))
        {
            return a;
        }
        else if (comp(*b, *c))
        {
            return c;
        }
        else
        {
            return b;
        }
    }
}


#endif //CPP_LAB3_SORT_ALGORITHMS_H
