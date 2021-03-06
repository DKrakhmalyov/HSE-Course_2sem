
#ifndef HOMEWORK_1_ARCGRAPH_H
#define HOMEWORK_1_ARCGRAPH_H

#include "../graph.h"

template <typename T = void>
class ArcGraph : public IGraph<T>
{
public:
    ArcGraph(){};

    ArcGraph(IGraph<T> *_oth){};

    virtual void AddEdge(int from, int to, T &&element)
    {
        arcs.push_back({from, to});
        weights.push_back(element);
    };

    virtual void GetEdges(std::vector<std::pair<int, int>> &edges, std::vector<T> &weights) const
    {
        edges = arcs;
        weights = this->weights;
    };

    virtual int VerticesCount() const
    {
        return arcs.size();
    };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const
    {
        for (auto arc : arcs)
            if (arc.first == vertex)
                vertices.push_back(arc.second);
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const
    {
        for (auto arc : arcs)
            if (arc.second == vertex)
                vertices.push_back(arc.first);
    };

private:
    std::vector<std::pair<int, int>> arcs;
    std::vector<T> weights;
};

#endif //HOMEWORK_1_ARCGRAPH_H
