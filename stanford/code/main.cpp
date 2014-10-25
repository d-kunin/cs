#include <iostream>
#include <fstream>
#include <vector>

#include "common/merge.hpp"

using namespace std;


int main() {
    string filename = "IntegerArray.txt";
    ifstream filein;
    filein.open(filename);

    if (!filein.is_open()) {
        return 1;
    }

    int num;
    vector<int> vec;

    while (filein >> num) {
        vec.push_back(num);
    }

    size_t invs;
    alg::sortAndCountInv(vec, invs);
    cout << invs << endl;

    return 0;
}