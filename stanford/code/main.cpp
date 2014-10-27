#include <iostream>
#include <vector>
#include <random>
#include <cstdio>

#include "common/merge.hpp"
#include "common/coding.hpp"
#include "common/quicksort.hpp"
#include "common/quickselect.hpp"

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
    typedef  size_t(*pivotChooser)(vector<int>&, size_t, size_t);

    pivotChooser choosers[] =
            {
              alg::chooseLeft,
              alg::chooseRight,
              alg::chooseMedianOfThree
            };

    string filenames[] =
            {
                    "10.txt",
                    "100.txt",
                    "1000.txt",
                    "QuickSort.txt"
            };

    for (auto filename : filenames)
    {
        for (auto fun : choosers)
        {
            vector<int> testvec;
            coding::readVectorFromFile(filename, testvec);

            size_t numComp = alg::quicksort(testvec, 0, testvec.size() - 1, fun);


            cout << numComp << " " << testvec.size() << " : ";
            coding::printVector(testvec, 16);
            cout << endl;
        }
        cout << endl;
    }


    return 0;
}

int qselect()
{
    for (int i = 0; i < 10; ++i)
    {

        std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

        coding::shuffle_vector(v);
        coding::printVector(v);

        cout << endl;
        for (int j = 0; j < 10; ++j)
        {
            int stat = alg::quickselect(v, j);
            printf("{%d, %d} ", j, stat);
        }
        cout << endl;
    }


    return 0;
}

int main()
{
//    return p1();
//    return p2();
    return qselect();
}

