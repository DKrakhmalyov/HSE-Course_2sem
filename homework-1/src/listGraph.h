
#ifndef HOMEWORK_1_LISTGRAPH_H
#define HOMEWORK_1_LISTGRAPH_H

#include "../graph.h"

template <typename T = void>
class ListGraph : public IGraph<T>
{
public:
    ListGraph(){};

    ListGraph(IGraph<T> *other){};

    virtual void AddEdge(int from, int to, T &&element)
    {
        nextVertices[from].push_back({to, element});
        prevVertices[to].push_back({from, std::forward<T>(element)});
    };

    virtual void GetEdges(std::vector<std::pair<int, int>> &edges, std::vector<T> &weights) const
    {
        for (auto [from, fromEdges] : nextVertices)
        {
            for (auto [to, weight] : fromEdges)
            {
                edges.push_back({from, to});
                weights.push_back(weight);
            }
        }
    };

    virtual int VerticesCount() const
    {
        return nextVertices.size();
    };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const
    {
        if (!nextVertices.contains(vertex))
            return;

        for (auto nextVertex : (*nextVertices.find(vertex)).second)
            vertices.push_back(nextVertex.first);
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const
    {
        if (!prevVertices.contains(vertex))
            return;

        for (auto prevVertex : (*prevVertices.find(vertex)).second)
            vertices.push_back(prevVertex.first);
    };

private:
    std::unordered_map<int, std::vector<std::pair<int, T>>> nextVertices;
    std::unordered_map<int, std::vector<std::pair<int, T>>> prevVertices;
};

#endif //HOMEWORK_1_LISTGRAPH_H
