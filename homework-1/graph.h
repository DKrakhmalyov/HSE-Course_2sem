
#ifndef HOMEWORK_1_GRAPH_H
#define HOMEWORK_1_GRAPH_H

#include <vector>
#include <map>
#include <set>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include "src/node.h"

template <typename T>
class IGraph
{
private:

    virtual void RealDfs(int curr, std::vector<int> &vertices, std::unordered_map<int, int> &used) const
    {
        used[curr] = 1;
        vertices.push_back(curr);
        std::vector<int> newStep;
        GetNextVertices(curr, newStep);
        for (size_t i = 0; i < newStep.size(); i++)
        {
            if (used[newStep[i]] == 0)
            {
                RealDfs(newStep[i], vertices, used);
            }
        }
    }
    std::unordered_set<int> existingV;

public:
    virtual ~IGraph() {}

    IGraph(){};

    IGraph(IGraph *_oth) {
        std::vector<std::pair<int, int>> new_Edges;
        _oth->GetEdges(new_Edges);
        for (auto x: new_Edges) {
            T var;
            _oth->getWeightOf(x.first, x.second, var);
            AddEdge(x.first, x.second, var);
        }  
    };
    virtual void GetExistingV(std::unordered_set<T> &new_existingV) {
        for (auto x: this->existingV) {
            new_existingV.insert(x);
        }
    }
    virtual void AddEdge(int from, int to, T &&_obj) = 0;

    virtual int VerticesCount() const = 0;

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const = 0;

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const = 0;

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const
    {
        std::unordered_map<int, int> used;
        RealDfs(vertex, vertices, used);
    }
    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const
    {
        std::queue<int> q;
        std::map<int, int> used;

        q.push(vertex);

        while (q.size())
        {
            int curr = q.front();
            q.pop();

            used[curr] = 1;
            vertices.push_back(curr);

            std::vector<int> news;
            GetNextVertices(curr, news);

            for (auto x : news)
                if (used[x] == 0)
                    q.push(x);
        }
    };
};

template <typename T = void>
class IPtrsGraph
{
private:
    virtual void RealDfs(Node<T> *curr, std::vector<Node<T> *> &vertices, std::unordered_map<Node<T> *, int> &used) const
    {
        used[curr] = 1;
        vertices.push_back(curr);
        std::vector<Node<T> *> newStep;
        GetNextVertices(curr, newStep);

        for (size_t i = 0; i < newStep.size(); i++)
        {
            if (used[newStep[i]] == 0)
            {
                RealDfs(newStep[i], vertices, used);
            }
        }
    }

public:
    virtual ~IPtrsGraph() {}

    IPtrsGraph(){};

    virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) = 0;

    virtual int VerticesCount() const = 0;

    virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const = 0;

    virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const = 0;

    virtual void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const
    {
        std::unordered_map<Node<T> *, int> used;
        RealDfs(vertex, vertices, used);
    }

    virtual void BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const
    {
        std::queue<Node<T> *> q;
        std::map<Node<T> *, int> used;

        q.push(vertex);

        while (q.size())
        {
            Node<T> *curr = q.front();
            q.pop();

            used[curr] = 1;
            vertices.push_back(curr);

            std::vector<Node<T> *> news;
            GetNextVertices(curr, news);

            for (auto x : news)
                if (used[x] == 0)
                    q.push(x);
        }
    };
    virtual void getVerts() {

    };
};
#endif //HOMEWORK_1_GRAPH_H
