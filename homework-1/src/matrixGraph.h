
#ifndef HOMEWORK_1_MATRIXGRAPH_H
#define HOMEWORK_1_MATRIXGRAPH_H

#include "../graph.h"

template <typename T = void>
class MatrixGraph : public IGraph<T>
{
public:
    MatrixGraph(){};

    MatrixGraph(IGraph<T> *other){};

    virtual void AddEdge(int from, int to, T &&element)
    {
        existingVertices.insert(from);
        existingVertices.insert(to);
        matrix[from][to] = element;
    };

    virtual void GetEdges(std::vector<std::pair<int, int>> &edges, std::vector<T> &weights) const
    {
        for (auto [from, fromEdges] : matrix)
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
        return matrix.size();
    };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const
    {
        if (!matrix.contains(vertex))
            return;

        for (auto nextVertex : (*matrix.find(vertex)).second)
            vertices.push_back(nextVertex.first);
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const
    {
        if (!matrix.contains(vertex))
            return;

        for (auto existingVertex : existingVertices)
            if ((*matrix.find(existingVertex)).second.contains(vertex))
                vertices.push_back(existingVertex);
    };

private:
    std::unordered_map<int, std::unordered_map<int, T>> matrix;
    std::unordered_set<int> existingVertices;
};

#endif //HOMEWORK_1_MATRIXGRAPH_H
