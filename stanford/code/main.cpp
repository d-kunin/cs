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
                    "1000.txt"
            };

    for (auto filename : filenames)
    {
        for (auto fun : choosers)
        {
            vector<int> testvec;
            coding::readVectorFromFile(filename, testvec);

            size_t numComp = alg::quicksort(testvec, 0, testvec.size() - 1, fun);


            cout << numComp << " " << testvec.size() << " : ";
            coding::printVector(vector<int>(testvec.begin(), testvec.begin() + 10));
            cout << "... ";
            coding::printVector(vector<int>(testvec.end() - 10, testvec.end()));
            cout << endl;
        }
        cout << endl;
    }


    return 0;
}

int main()
{
//    return p1();
    return p2();
}

