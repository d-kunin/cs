#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <sstream>
#include <fstream>

#include "common/merge.hpp"
#include "common/coding.hpp"
#include "common/quicksort.hpp"
#include "common/quickselect.hpp"
#include "common/graph.hpp"

void p3_0(alg::Graph & g);

using namespace std;

static alg::Graph::VertexVisitor  printer = [] (size_t v) {
    cout << "{" << v << "}";
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
    alg::Graph g(200);

//    p3_0(g);
    string filename = "kargerMinCut.txt";
    std::ifstream file(filename);
    string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        size_t v1;
        ss >> v1;
        while (ss)
        {
            size_t v2;
            ss >> v2;
            g.addEdge(v1, v2);
        }
    }

    g.bfs(printer);

    return 0;
}

void p3_0(alg::Graph & g) {
    cout << g.hasEdge(2, 1) << endl;

    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(2, 5);
    g.addEdge(3, 4);
    g.addEdge(3, 6);
    g.addEdge(5, 7);

    cout << g.hasEdge(2, 1) << endl;
    cout << g.hasEdge(1, 2) << endl;

    cout << endl;
    g.bfs(printer);
    cout << endl;

    cout << endl;
    g.dfs(printer);
    cout << endl << endl;

    g.removeEdge(1, 2);
    cout << g.hasEdge(1, 2) << endl;
    cout << g.hasEdge(2, 1) << endl;
}


int main()
{
//    return p1();
//    return p2();
//    return qselect();
    return p3();
}

