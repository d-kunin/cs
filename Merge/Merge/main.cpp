//
//  main.cpp
//  Merge
//
//  Created by Dzmitry Kunin on 16.10.14.
//  Copyright (c) 2014 BSUIR. All rights reserved.
//

#include <iostream>
#include "merge.hpp"

using std::vector;
using std::cout;
using std::endl;

void printVector(vector<int> const & v) {
    for (auto i : v) {
        cout << i << " ";
    }
    cout << endl;
}

int main(int argc, const char * argv[]) {
    
    vector<int> v1 {9, 4, 5, 6, 8, 7, 1, 44, 66, 423};
    vector<int> v2 {3, 2, 5, 1, 4};
    vector<int> out;
    
    // sort it
    cout << "v1 as is:  ";
    printVector(v1);
    out = alg::mergeSort(v1);
    cout << "v1 sorted: ";
    printVector(out);
    
    cout << "v2 as is:  ";
    printVector(v2);
    out = alg::mergeSort(v2);
    cout << "v2 sorted: ";
    printVector(out);
    
    return 0;
}
