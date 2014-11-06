#pragma once

#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <cassert>
#include <iostream>

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
        typedef bool (*VertexVisitor)(size_t);

        Graph(size_t numVertices, size_t selfLoops = false);

        void addEdge(size_t v1, size_t v2, bool both=true);
        bool hasEdge(size_t v1, size_t v2);
        bool removeEdge(size_t v1, size_t v2);
        void merge(size_t v1, size_t v2);

        // Traverse
        void bfs(VertexVisitor visitor);
        void dfs(VertexVisitor visitor);


        // Stat
        size_t  countConnectedVertices();
        vector<size_t> const & degrees() { return _degrees; }
        vector<size_t> const & adjacentTo(size_t v)
        {
            assertIndex(v);
            return _adjacencyList[toStoreIndex(v)];
        }
        size_t  numEdges();

    // Impl

    private:
        vector< vector<size_t> > _adjacencyList;
        vector<size_t> _degrees;
        size_t    _capacity;
        bool      _selfLoops;

        bool checkIndex(size_t v)
        {
            return v <= _capacity && v > 0;
        }

        void assertIndex(size_t v)
        {
            assert(checkIndex(v));
        }

        size_t toStoreIndex(size_t v)
        {
            return v - 1;
        }

        size_t toExtIndex(size_t v)
        {
            return v + 1;
        }

        friend std::ostream & operator<<(std::ostream &os, const Graph& g);
    };

    //



    Graph::Graph(size_t numVertices, size_t selfLoops)
        : _capacity(numVertices)
        , _selfLoops(selfLoops)
    {
        _adjacencyList.resize(_capacity);
        _degrees.resize(_capacity);
    }

    void Graph::addEdge(size_t v1, size_t v2, bool both)
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

        if (both)
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

    void Graph::bfs(VertexVisitor visitor) {

        set<size_t> visited;
        queue<size_t> q;

        // find any vertex to start
        for (size_t i = 0; i < _capacity; ++i)
        {
            if (!_adjacencyList[i].empty())
            {
                q.push(i);
                visited.insert(i);
                break;
            }
        }

        while (!q.empty())
        {
            size_t vertex = q.front();
            q.pop();
            visitor(toExtIndex(vertex));

            for (auto v : _adjacencyList[vertex])
            {
                if (visited.find(v) == visited.end())
                {
                    // not visited, so add
                    q.push(v);
                    visited.insert(v);
                }
            }
        }
    }

    void Graph::dfs(VertexVisitor visitor) {

        set<size_t> visited;
        stack<size_t> s;

        // find any vertex to start
        for (size_t i = 0; i < _capacity; ++i)
        {
            if (!_adjacencyList[i].empty())
            {
                s.push(i);
                break;
            }
        }

        while (!s.empty())
        {
            size_t vertex = s.top();
            s.pop();

            if (visited.find(vertex) == visited.end())
            {
                visited.insert(vertex);
                visitor(toExtIndex(vertex));
                for (auto v : _adjacencyList[vertex])
                {
                    s.push(v);
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


}