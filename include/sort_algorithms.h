//
// Created by gfn on 12/19/2025.
//

#ifndef CPP_LAB3_SORT_ALGORITHMS_H
#define CPP_LAB3_SORT_ALGORITHMS_H
#include <algorithm>


class sort_algorithms
{
};

template<typename T>
inline void MoveSwap(T &a, T &b)
{
    T Tmp = std::move(a);
    a = std::move(b);
    b = std::move(Tmp);
}


#endif //CPP_LAB3_SORT_ALGORITHMS_H
