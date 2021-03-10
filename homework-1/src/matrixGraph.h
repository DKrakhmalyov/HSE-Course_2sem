
#ifndef HOMEWORK_1_MATRIXGRAPH_H
#define HOMEWORK_1_MATRIXGRAPH_H


#include "../graph.h"

template<typename T = void>
class MatrixGraph : public IGraph<T> {
public:
    virtual void AddEdge(int from, int to, T &&element) override final;

    MatrixGraph();

    MatrixGraph(IGraph<T> *_oth);

    virtual int VerticesCount() const { return 0; };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const override final;

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const override final;

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const override final;

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const override final;

private:
    
    std::map<int, int> toId;

    std::vector<int> toVertex;

    std::vector<std::vector<std::pair<bool, T>>> matrix;

    void AddVertex(int vertex);
};

#endif //HOMEWORK_1_MATRIXGRAPH_H
