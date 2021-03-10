
#ifndef HOMEWORK_1_LISTGRAPH_H
#define HOMEWORK_1_LISTGRAPH_H

#include "../graph.h"


template<typename T>
class ListGraph : public IGraph<T> {
public:
    virtual void AddEdge(int from, int to, T &&element) override final;

    ListGraph() {};

    ListGraph(IGraph<T> *_oth) {};

    virtual int VerticesCount() const override final;

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const override final;

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const override final;

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const override final;

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const override final;

private:

    std::map<int, std::list<std::pair<int, T>>> toList;

    std::map<int, std::list<std::pair<int, T>>> fromList;
};


#endif //HOMEWORK_1_LISTGRAPH_H
