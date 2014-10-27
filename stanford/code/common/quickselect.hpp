#pragma once


#include <vector>
#include <stdexcept>
#include "quicksort.hpp"

namespace alg
{
    template <typename T>
    T quickselect(vector<T> vec, size_t kth)
    {
        size_t left = 0;
        size_t right = vec.size() - 1;

        if (kth >= vec.size())
            throw std::range_error("Unsupported kth");

        for (;;)
        {
            size_t pivotIndex = partition(vec, left, right);

            if (pivotIndex == kth) {
                return vec[pivotIndex];
            }
            else if (pivotIndex < kth)
            {
                left = pivotIndex + 1;
            }
            else
            {
                right = pivotIndex - 1;
            }
        }
    }

}
