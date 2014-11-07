#pragma once

#include <algorithm>
#include <iterator>
#include <string>
#include <fstream>
#include <vector>
#include <assert.h>

using namespace std;

namespace coding
{
    template <typename T>
    void printVector(vector<T> const & v, size_t maxLength=20) {
        if (v.empty())
        {
            cout << "{empty} ";
            return;
        }


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

    template <typename T>
    void shuffle_vector(vector<T> & v)
    {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(v.begin(), v.end(), g);
    }

    template <typename T>
    vector<T> sequence(T from, T to)
    {
        assert(from < to);

        vector<T> result;

        for (T i = from; i < to; ++i)
            result.push_back(i);

        return result;
    }

    template <typename T>
    vector<T> randomizedSequence(T from, T to)
    {
        vector<T> result = sequence(from, to);
        shuffle_vector(result);
        return result;
    }

    size_t rand(size_t max, size_t min = 0)
    {
        std::random_device rd;
        std::default_random_engine e(rd());
        return (e() + min) % max;
    }

    template <typename T>
    T randomFrom(vector<T> const & vec)
    {
        auto pos = rand(vec.size());
        return vec[pos];
    }


}
