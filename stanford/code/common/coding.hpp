#pragma once

#include <algorithm>
#include <iterator>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

namespace coding
{
    template <typename T>
    void printVector(vector<T> const & v, size_t maxLength=20) {
        bool ellipsize = maxLength < v.size();

        if (!ellipsize) {
            for (auto elem : v) {
                std::cout << elem << " ";
            }
        } else {
            size_t part = maxLength/2;
            typedef typename vector<T>::const_iterator iter;
            for (iter it = v.begin(); it != (v.begin() + part); ++it)
            {
                std::cout << *it << " ";
            }
            std::cout << "... ";
            for (iter it = (v.end() - part); it != v.end(); ++it)
            {
                std::cout << *it << " ";
            }
        }

    }


    template <typename T>
    bool readVectorFromFile(string const & filename, vector<T> & output) {

        ifstream file(filename);

        if (file)
        {
            output.clear();

            istream_iterator<T> eos;
            istream_iterator<T> iit(file);
            copy(iit, eos, back_inserter(output));

            return true;
        }

        return false;
    }
}
