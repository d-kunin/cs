#pragma once

#include <vector>
#include <algorithm>

using std::vector;
using std::swap;

namespace alg
{
    template <typename T>
    size_t partition(vector<T> & vec, size_t left, size_t right) {
        T pivot = vec[left]; // TODO add different choosePivot()
        size_t border = left + 1;
        for (size_t j = left + 1; j <= right; ++j)
        {
            if (vec[j] < pivot)
            {
                swap(vec[border], vec[j]);
                ++border;
            }
        }
        swap(vec[left], vec[border - 1]);
        return border - 1;
    }

    template <typename T>
    void quicksort(vector<T> & vec, size_t left, size_t right)
    {
        size_t vec_size = right - left + 1;
        if (vec_size < 2) return;

        size_t pivotIndex = partition(vec, left, right);
        quicksort(vec, left, pivotIndex - 1);
        quicksort(vec, pivotIndex + 1, right);
    }

}
