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
    void printVector(vector<T> const & v) {
        for (auto elem : v) {
            std::cout << elem << " ";
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
