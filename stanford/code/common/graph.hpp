#pragma once

#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <cassert>
#include <iostream>
#include <functional>

using std::vector;
using std::set;
using std::queue;
using std::endl;

namespace alg
{

    class Graph
    {

    // Interface

    public:

        // Must return 'false' to stop traversal
//        typedef bool (*VertexVisitor)(size_t, vvst const & story);
        typedef std::function<bool (size_t, vvst const &)> VertexVisitor;

        Graph(size_t numVertices, size_t selfLoops = false);

        void addEdge(size_t v1, size_t v2, bool bidirectional = true);
        bool hasEdge(size_t v1, size_t v2);
        bool removeEdge(size_t v1, size_t v2);
        void merge(size_t v1, size_t v2);

        void reverse();

        // Traverse
        void bfs(size_t v, VertexVisitor visitor);

        template <typename Func>
        void dfs(size_t v, Func visitor);


        vector<size_t> topologicalOrder();


        // Stat
        size_t  countConnectedVertices();
        vector<size_t> const & degrees() { return _degrees; }
        vector<size_t> const & adjacentTo(size_t v)
        {
            assertIndex(v);
            return _adjacencyList[toStoreIndex(v)];
        }

        // Intel
        static size_t KargerMinCut(Graph const &input);
        vvst sccKosaraju();


    // Impl

    private:
        size_t    _capacity;
        bool      _selfLoops;
        vvst      _adjacencyList;
        vst       _degrees;

        bool checkIndex(size_t v)
        {
            return v <= _capacity && v > 0;
        }

        void assertIndex(size_t v)
        {
            assert(checkIndex(v));
        }

        static size_t toStoreIndex(size_t v)
        {
            return v - 1;
        }

        static size_t toExtIndex(size_t v)
        {
            return v + 1;
        }

        friend std::ostream & operator<<(std::ostream &os, const Graph& g);
    };

    //



    Graph::Graph(size_t numVertices, size_t selfLoops)
        : _capacity(numVertices)
        , _selfLoops(selfLoops)
        , _adjacencyList(numVertices)
        , _degrees(numVertices)
    {}

    void Graph::addEdge(size_t v1, size_t v2, bool bidirectional)
    {
        assertIndex(v1);
        assertIndex(v2);

        if (!_selfLoops && (v1 == v2))
        {
            return;
        }

        v1 = toStoreIndex(v1);
        v2 = toStoreIndex(v2);

        _adjacencyList[v1].push_back(v2);
        ++_degrees[v1];

        if (bidirectional)
        {
            _adjacencyList[v2].push_back(v1);
            ++_degrees[v2];
        }
    }

    bool Graph::hasEdge(size_t v1, size_t v2)
    {
        assertIndex(v1);
        assertIndex(v2);

        v1 = toStoreIndex(v1);
        v2 = toStoreIndex(v2);

        for (size_t v : _adjacencyList[v1])
        {
            if (v == v2)
            {
                return true;
            }
        }
        return false;
    }

    bool Graph::removeEdge(size_t v1, size_t v2)
    {
        assertIndex(v1);
        assertIndex(v2);

        v1 = toStoreIndex(v1);
        v2 = toStoreIndex(v2);

        bool found = false;
        vector<size_t> & left = _adjacencyList[v1];

        for (vector<size_t>::iterator it = left.begin(); it != left.end(); ++it)
        {
            if (*it == v2)
            {
                left.erase(it);
                --_degrees[v2];
                found = true;
                break;
            }
        }

        vector<size_t> & right = _adjacencyList[v2];
        for (vector<size_t >::iterator it = right.begin(); it != right.end(); ++it)
        {
            if (*it == v1)
            {
                right.erase(it);
                --_degrees[v1];
                found = true;
                break;
            }
        }

        return found;
    }

    void Graph::bfs(size_t v, VertexVisitor visitor) {

        checkIndex(v);
        v = toStoreIndex(v);

        set<size_t> visited;
        queue<size_t> q;
        vector< vector<size_t> > paths(_capacity);


        visited.insert(v);
        q.push(v);

        // find any vertex to start

        while (!q.empty())
        {
            size_t vertex = q.front();
            q.pop();


            for (auto v : _adjacencyList[vertex])
            {
                if (visited.find(v) == visited.end())
                {
                    // remember path
                    paths[v].assign(paths[vertex].begin(), paths[vertex].end());
                    paths[v].push_back(toExtIndex(vertex));

                    // add to processing
                    q.push(v);

                    // mark visited
                    visited.insert(v);
                }
            }

            if (!visitor(toExtIndex(vertex), paths)) {
                return;
            }
        }
    }

    template <typename Func>
    void Graph::dfs(size_t v, Func visitor) {

        checkIndex(v);
        v = toStoreIndex(v);

        set<size_t> visited;
        stack<size_t> s;
        vvst story(_capacity);

        s.push(v);

        while (!s.empty())
        {
            size_t vertex = s.top();
            s.pop();

            for (auto v : _adjacencyList[vertex])
            {
                if (visited.find(v) == visited.end())
                {
                    // copy path to prev node
                    story[v].assign(story[vertex].begin(), story[vertex].end());
                    story[v].push_back(toExtIndex(vertex));

                    // add to processing stack
                    s.push(v);
                }
            }

            if (visited.find(vertex) == visited.end()) {
                visited.insert(vertex);

                if (!visitor(toExtIndex(vertex), story)) {
                    return;
                }
            }
        }

    }

    void Graph::merge(size_t v1, size_t v2)
    {
        assertIndex(v1);
        assertIndex(v2);

        assert(hasEdge(v1, v2));

        // this vertices must be moved to v1
        vector<size_t> transfer(_adjacencyList[toStoreIndex(v2)]);

        for (auto v : transfer)
        {
            v = toExtIndex(v);

            removeEdge(v2, v);

            if (v != v1)
            {
                addEdge(v1, v);
            }
        }

        removeEdge(v1, v2);
        removeEdge(v1, v1);
        removeEdge(v2, v2);
    }

    size_t Graph::countConnectedVertices()
    {
        size_t count = 0;
        for (auto deg : _degrees)
        {
            count += deg > 0 ? 1 : 0;
        }
        return count;
    }

    ostream & operator<<(ostream & os, Graph const & g)
    {
        for (vector<size_t> vtx : g._adjacencyList) {
            os << endl;
            for (size_t v : vtx)
            {
                os << v + 1 << " ";
            }
        }
        return os;
    }

    size_t Graph::KargerMinCut(Graph const &input)
    {
        Graph g(input);
        Graph bk(input);

        size_t problemSize = input._capacity;
        size_t minCut = (size_t)-1;
        size_t repeat = problemSize << 2;

        fprintf(stderr, "Repeat %lu times\n", repeat);


        for (size_t r = 0; r < repeat; ++r)
        {
            g = bk;
            vector<size_t> order = coding::sequence<size_t>(1, problemSize + 1);


            while (g.countConnectedVertices() > 2)
            {
                size_t v1 = coding::randomFrom(order);
                size_t v2 = 1 + coding::randomFrom(g.adjacentTo(v1));

                g.merge(v1, v2);

                order.erase(std::remove(order.begin(), order.end(), v2), order.end());
            }

            for (auto d : g.degrees()) {
                if (d > 0 && d < minCut) {
                    minCut = d;
                    fprintf(stderr, "Min cut=%lu\n", minCut);
                    break;
                }
            }
        }

        return minCut;
    }

    vector<size_t> Graph::topologicalOrder()
    {
        set<size_t> visited;
        vector<size_t> order(_capacity);
        stack<size_t> s;
        size_t currentLabel = _capacity;

        for (auto vertex : coding::sequence<size_t>(0, _capacity))
        {

            if (visited.find(vertex) == visited.end())
            {
                s.push(vertex);
                visited.insert(vertex);
            }

            while (!s.empty())
            {
                size_t currentVertex = s.top();
                bool sink = true;

                for (auto adjV : _adjacencyList[currentVertex])
                {
                    if (visited.find(adjV) == visited.end())
                    {
                        s.push(adjV);
                        visited.insert(adjV);
                        sink = false;
                    }
                }

                if (sink)
                {
                    s.pop();
                    order[--currentLabel] = toExtIndex(currentVertex);
                }
            }
        }

        return order;
    }

    void Graph::reverse()
    {
        vvst reversedAdj(_capacity);

        for (size_t i = 0; i < _capacity; ++i)
        {
            size_t v1 = i;
            for (size_t j = 0; j < _adjacencyList[i].size(); ++j)
            {
                size_t v2 = _adjacencyList[i][j];
                reversedAdj[v2].pb(v1);
            }
        }

        _adjacencyList.assign(all(reversedAdj));
        // TODO recalculate degrees?
    }

    vvst Graph::sccKosaraju()
    {
        reverse();

        // create traverse vector
        vst explored(_capacity);
        vst traverseOrder;

        for_range(0, _capacity, i)
        {
            if (explored[i] == 0)
            {
                stack<size_t> s;
                s.push(i);
                explored[i] = 1;

                while (!s.empty())
                {
                    size_t v = s.top();
                    s.pop();

                    for (auto av : _adjacencyList[v])
                    {
                        if (explored[av] == 0)
                        {
                            s.push(av);
                            explored[av] = 1;
                        }
                    }
                    traverseOrder.pb(v + 1);
                }

//                // todo rewrite
//                dfs(toExtIndex(i), [&] (size_t vrtx, vvst const & story)
//                {
//                    if (explored[vrtx - 1] == 0)
//                    {
//                        traverseOrder.pb(vrtx);
//                        explored[vrtx - 1] = 1;
//                    }
//                    return true;
//                });

            }
        }

        coding::printVector(traverseOrder);
        reverse();


        // traverse from the latest finishing time
        vvst sccs;
        std::fill(all(explored), 0);

        for (auto it = traverseOrder.rbegin(); it != traverseOrder.rend(); ++it)
        {
            size_t leader = *it;
            if (explored[leader - 1] == 0) {
                vst currentSCC;

                stack<size_t> s;
                s.push(leader);
                explored[leader - 1] = 1;

                while (!s.empty()) {
                    size_t v = s.top();
                    s.pop();

                    for (auto av : _adjacencyList[v - 1])
                    {
                        av = toExtIndex(av);
                        if (explored[av - 1] == 0) {
                            s.push(av);
                            explored[av - 1] = 1;
                        }
                    }
                    currentSCC.pb(v);
                }


                newline();
                cout << "[" << currentSCC.size() << "] ";
                coding::printVector(currentSCC);
                sccs.pb(currentSCC);
            }
        }

        return sccs;
    }
}