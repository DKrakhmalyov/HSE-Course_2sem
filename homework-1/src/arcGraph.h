
#ifndef HOMEWORK_1_ARCGRAPH_H
#define HOMEWORK_1_ARCGRAPH_H

#include "../graph.h"

template <typename T = void>
class ArcGraph : public IGraph<T>
{
public:
    ArcGraph(){};

    ArcGraph(IGraph<T> *other){};

    virtual void AddEdge(int from, int to, T &&element)
    {
        edges.push_back({from, to});
        weights.push_back(std::forward<T>(element));
    };

    virtual void GetEdges(std::vector<std::pair<int, int>> &edges, std::vector<T> &weights) const
    {
        edges = this->edges;
        weights = this->weights;
    };

    virtual int VerticesCount() const
    {
        return edges.size();
    };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const
    {
        for (auto [from, to] : edges)
            if (from == vertex)
                vertices.push_back(to);
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const
    {
        for (auto [from, to] : edges)
            if (to == vertex)
                vertices.push_back(from);
    };

private:
    std::vector<std::pair<int, int>> edges;
    std::vector<T> weights;
};

#endif //HOMEWORK_1_ARCGRAPH_H
