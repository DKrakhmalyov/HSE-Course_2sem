
#ifndef HOMEWORK_1_MATRIXGRAPH_H
#define HOMEWORK_1_MATRIXGRAPH_H


#include "../graph.h"

template<typename T = void>
class MatrixGraph : public IGraph<T> {
public:
    virtual void AddEdge(int from, int to, T &&element) {};

    MatrixGraph() {};

    MatrixGraph(IGraph<T> *_oth) {};

    virtual int VerticesCount() const { return 0; };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {};

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {};

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const {};

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {};
};

#endif //HOMEWORK_1_MATRIXGRAPH_H
