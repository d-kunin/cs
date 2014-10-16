//
//  merge.hpp
//  Merge
//
//  Created by Dzmitry Kunin on 16.10.14.
//  Copyright (c) 2014 BSUIR. All rights reserved.
//

#pragma once

#include <vector>

using std::vector;

template <typename T>
void printVector(vector<T> const & v) {
    for (auto i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

namespace alg {
    
    template <typename T>
    void setAndIncrementPos(vector<T> & out, vector<T> const & src, size_t outPos, size_t & srcPos);
    
    template <typename T>
    vector<T> mergeSort(vector<T> & vec);
    
    template <typename T>
    vector<T> merge(vector<T> const & left, vector<T> const & right);
    
    template <typename T>
    vector<T> mergeSort(vector<T> & vec) {
        if (vec.size() < 2) {
            return vec;
        } else {
            typename vector<T>::iterator mid = vec.begin() + (vec.size()/2);
            
            vector<T> left(vec.begin(), mid);
            left = mergeSort(left);
            
            vector<T> right(mid, vec.end());
            right = mergeSort(right);

            return merge(left, right);
        }
    }

    template <typename T>
    vector<T> merge(vector<T> const & left, vector<T> const & right) {
        size_t lSize = left.size();
        size_t rSize = right.size();
        size_t total = lSize + rSize;
        
        vector<T> out;
        out.resize(total);
        
        size_t lPos = 0;
        size_t rPos = 0;
        for (size_t i = 0; i < total; ++i) {
            
            if (lPos < lSize && rPos < rSize) {
                
                if (left[lPos] < right[rPos]) {
                    setAndIncrementPos(out, left, i, lPos);
                } else {
                    setAndIncrementPos(out, right, i, rPos);
                }
                
            } else if (lPos < lSize) {
                setAndIncrementPos(out, left, i, lPos);
            } else {
                setAndIncrementPos(out, right, i, rPos);
            }
        }
        return out;
    }
    
    template <typename T>
    void setAndIncrementPos(vector<T> & out, vector<T> const & src, size_t outPos, size_t & srcPos) {
        out[outPos] = src[srcPos];
        ++srcPos;
    }

};


