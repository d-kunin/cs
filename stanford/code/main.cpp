#include <iostream>
#include <vector>
#include <random>
#include <set>
#include <sstream>
#include <fstream>

#include "common/merge.hpp"
#include "common/coding.hpp"
#include "common/quicksort.hpp"
#include "common/quickselect.hpp"
#include "common/graph.hpp"

void p3_0(alg::Graph & g);

using namespace std;

static alg::Graph::VertexVisitor  printer = [] (size_t v, vector<vector<size_t>> const & story) {
    cout << "{" << v << "}";
    cout << "[";
    for (auto pathElem : story[v - 1])
    {
        cout << pathElem << " ";
    }
    cout << "]" << endl;
    return true;
};

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
    for (size_t i = 0; i < 10; ++i)
    {

        std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

        coding::shuffle_vector(v);
        coding::printVector(v);

        cout << endl;
        for (size_t j = 0; j < 10; ++j)
        {
            int stat = alg::quickselect(v, j);
            printf("{%lu, %d} ", j, stat);
        }
        cout << endl;
    }

    vector<int> v;

    try
    {
        alg::quickselect(v, 0);
        alg::quickselect(v, 1);
    }
    catch (std::exception const & e)
    {
        cout << "ERROR: " << e.what() << endl;
    }


    return 0;
}

int p3()
{
    bool readFile = true;
    size_t const fileInputSize = 200;
    size_t const toyInputSize = 4;

    size_t problemSize = readFile ? fileInputSize : toyInputSize;

    alg::Graph g(problemSize);

    if (readFile)
    {
        string filename = "kargerMinCut.txt";
        std::ifstream file(filename);
        string line;

        while (std::getline(file, line)) {
            std::stringstream ss(line);

            size_t v1;
            ss >> v1;

            size_t v2;
            while (ss >> v2) {
                g.addEdge(v1, v2, false);
            }
        }

    }
    else
    {
        g.addEdge(1, 2);
        g.addEdge(1, 3);
        g.addEdge(1, 4);
        g.addEdge(4, 3);
        g.addEdge(2, 3);
    }

    alg::Graph::KargerMinCut(g);

    cout << "Done!" << endl;
    return 0;
}

void p3_0(alg::Graph & g) {

    g = alg::Graph(9);

    // first
    g.addEdge(1, 7, false);
    g.addEdge(7, 4, false);
    g.addEdge(4, 1, false);
    g.addEdge(7, 9, false);

    // second
    g.addEdge(9, 6, false);
    g.addEdge(6, 3, false);
    g.addEdge(3, 9, false);
    g.addEdge(6, 8, false);

    // third
    g.addEdge(8, 2, false);
    g.addEdge(2, 5, false);
    g.addEdge(5, 8, false);

    g.sccKosaraju();

}


int main()
{
//    return p1();
//    return p2();
//    return qselect();
//    return p3();
    alg::Graph g(10);
    p3_0(g);

    return 0;
}

