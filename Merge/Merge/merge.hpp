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
    void mergeSort(vector<T> & out, vector<T> const & input);
    
    template <typename T>
    void merge(vector<T> & out, vector<T> const & left, vector<T> const & right);
    
    template <typename T>
    void mergeSort(vector<T> & out, vector<T> const & input) {
        if (input.size() < 2) {
            out.resize(input.size());
            out.assign(input.begin(), input.end());
        } else {
            size_t mid = input.size()/2;
            
            vector<T> left(input.begin(), input.begin() + mid);
            vector<T> lOut;
            mergeSort(lOut, left);
            
            
            vector<T> rOut;
            vector<T> right(input.begin() + mid, input.end());
            mergeSort(rOut, right);

            merge(out, lOut, rOut);
        }
    }

    template <typename T>
    void merge(vector<T> & out, vector<T> const & left, vector<T> const & right) {
        size_t lSize = left.size();
        size_t rSize = right.size();
        size_t total = lSize + rSize;
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
    }
    
    template <typename T>
    void setAndIncrementPos(vector<T> & out, vector<T> const & src, size_t outPos, size_t & srcPos) {
        out[outPos] = src[srcPos];
        ++srcPos;
    }

};


