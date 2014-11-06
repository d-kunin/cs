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
    bool readFile = true;
    size_t problemSize = readFile ? 200 : 4;


    alg::Graph g(problemSize);

    if (readFile)
    {
        string filename = "kargerMinCut.txt";
//        string filename = "cut40_3.txt";
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

//    g.bfs(printer);


    size_t repeat = problemSize << 16;
    cout << endl << "Repeat: " << repeat << endl;
    size_t minCut = (size_t)-1;

    alg::Graph bk(g);

    for (size_t r = 0; r < repeat; ++r)
    {
        g = bk;
        vector<size_t> order;
        for (size_t i = 1; i <= problemSize; ++i) {
            order.push_back(i);
        }
        coding::shuffle_vector(order);


        while (g.countConnectedVertices() > 2) {

            size_t v1 = order.back();

            vector<size_t> const & adjs = g.adjacentTo(v1);
            size_t indx = coding::rand(adjs.size(), 1);
            size_t v2 = 1 + adjs[indx];

            g.merge(v1, v2);

            order.erase(std::remove(order.begin(), order.end(), v2), order.end());
            coding::shuffle_vector(order);
        }

        for (auto d : g.degrees()) {
            if (d > 0) {
                if (d < minCut) {
                    minCut = d;
                    cout << endl << "Min cut: " << minCut << endl;
                }
            }
        }

    }
    cout << endl << "Min cut: " << minCut << endl;

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

