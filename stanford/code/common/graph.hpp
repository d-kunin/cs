#pragma once

#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <cassert>

using std::vector;
using std::set;
using std::queue;

namespace alg
{

    class Graph
    {

    // Interface

    public:

        // Must return 'false' to stop traversal
        typedef bool (*VertexVisitor)(size_t);

        Graph(size_t numVertices, size_t allowLoops = false);

        void addEdge(size_t v1, size_t v2);
        bool hasEdge(size_t v1, size_t v2);
        bool removeEdge(size_t v1, size_t v2);

        // Traverse
        void bfs(VertexVisitor visitor);
        void dfs(VertexVisitor visitor);


        // Stat
        size_t  numVertices();
        size_t  numEdges();

    // Impl

    private:
        vector< vector<size_t> > _adjacencyList;
        size_t  const  _numVertices;
        bool    const _allowLoops;

        bool checkIndex(size_t v)
        {
            return v <= _numVertices && v > 0;
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
    };

    //



    Graph::Graph(size_t numVertices, size_t allowLoops)
        : _numVertices(numVertices)
        , _allowLoops(allowLoops)
    {
        _adjacencyList.resize(_numVertices);
    }

    void Graph::addEdge(size_t v1, size_t v2)
    {
        assertIndex(v1);
        assertIndex(v2);

        if (!_allowLoops && (v1 == v2))
        {
            return;
        }

        v1 = toStoreIndex(v1);
        v2 = toStoreIndex(v2);

        _adjacencyList[v1].push_back(v2);
        _adjacencyList[v2].push_back(v1);
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
        for (size_t i = 0; i < _numVertices; ++i)
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
        for (size_t i = 0; i < _numVertices; ++i)
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


}