
#ifndef HOMEWORK_1_ARCGRAPH_H
#define HOMEWORK_1_ARCGRAPH_H

#include "../graph.h"

template<typename T = void>
class ArcGraph : public IGraph<T> {
public:
    virtual void AddEdge(int from, int to, T &&element) override final;

    ArcGraph() {};

    ArcGraph(IGraph<T> *_oth) {};

    virtual int VerticesCount() const override final;

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const override final;

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const override final;

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const override final;

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const override final;

private:

    std::set<int> verticeList;

    std::multiset<std::tuple<int, int, T>> edges;

    // std::multiset<std::tuple<int, int, T>>::iterator
    auto getLbound(int vertex) const;
};

#endif //HOMEWORK_1_ARCGRAPH_H
