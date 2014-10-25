#pragma once

#include <vector>
#include <algorithm>

using std::vector;
using std::swap;

namespace alg
{

    template <typename T>
    size_t chooseLeft(vector<T> & vec, size_t left, size_t right)
    {
        return vec[left];
    }

    template <typename T>
    size_t chooseRight(vector<T> & vec, size_t left, size_t right)
    {
        T pivot = vec[right];
        swap(vec[right], vec[left]);
        return pivot;
    }

    template <typename T>
    size_t chooseMedianOfThree(vector<T> & vec, size_t left, size_t right)
    {
        T begin = vec[left];
        T end   = vec[right];
        size_t midIndex = vec.size()/2 - 1;
        T mid   = vec[midIndex];

        T median = max(min(begin,end), min(max(begin,end),mid));

        // always place median as first value in array
        if (median == end)
        {
            swap(vec[right], vec[left]);
        }
        else if (median == mid)
        {
            swap(vec[midIndex], vec[left]);
        }

        return median;
    }

    template <typename T>
    size_t partition(
            vector<T> & vec,
            size_t left,
            size_t right,
            size_t (*choosePivotFunc)(vector<T>&, size_t, size_t) = &chooseLeft)
    {
        T pivot = choosePivotFunc(vec, left, right);
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
    void quicksort(
            vector<T> & vec,
            size_t left,
            size_t right,
            size_t (*choosePivotFunc)(vector<T>&, size_t, size_t) = &chooseLeft)
    {
        size_t vec_size = right - left + 1;
        if (vec_size < 2) return;

        size_t pivotIndex = partition(vec, left, right, choosePivotFunc);

        quicksort(vec, left, pivotIndex - 1);
        quicksort(vec, pivotIndex + 1, right);
    }

}
