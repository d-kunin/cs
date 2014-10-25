#include <iostream>
#include <vector>

#include "common/merge.hpp"
#include "common/coding.hpp"
#include "common/quicksort.hpp"

using namespace std;

int p1()
{
    string filename = "IntegerArray.txt";
    vector<int> vec;
    size_t invs;

    if (!coding::readVectorFromFile(filename, vec)) return 1;

    alg::sortAndCountInv(vec, invs);
    cout << invs << endl;

    return 0;
}

int p2()
{
    vector<int> testvec {4, 1, 2, 5, 1, 6, 7, 1, 0, 1};
    size_t pivot_index = alg::partition(testvec, 0, testvec.size() - 1);
    coding::printVector(testvec);
    cout << pivot_index << endl;

    alg::quicksort(testvec, 0, testvec.size() - 1);
    coding::printVector(testvec);
}

int main()
{
//    return p1();
    return p2();
}

