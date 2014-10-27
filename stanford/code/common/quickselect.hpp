#pragma once


#include <vector>
#include "quicksort.hpp"

namespace alg
{
    template <typename T>
    T quickselect(vector<T> vec, size_t kth)
    {
        auto left = 0;
        auto right = vec.size() - 1;
        while (left < right) {
            size_t pivotIndex = partition(vec, left, right);
            if (pivotIndex < kth) {
                left = pivotIndex + 1;
            }
            else if (pivotIndex > kth)
            {
                right = pivotIndex - 1;
            }
            else {
                return vec[kth];
            }
        }
        // TODO do I need this?
        return vec[left];
    }

}
