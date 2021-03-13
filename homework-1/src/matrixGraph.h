#ifndef HOMEWORK_1_MATRIXGRAPH_H
#define HOMEWORK_1_MATRIXGRAPH_H

#include "../graph.h"

template <typename T = void>
class MatrixGraph : public IGraph<T>
{

private:
    std::unordered_map<int, std::unordered_map<int, T>> matrix;
    std::unordered_set<int> existingV;

public:
    virtual T getWeightOf(int from, int to) {
        return matrix[from][to];
    };
    virtual void AddEdge(int from, int to, T &&element)
    {
        existingV.insert(from);
        existingV.insert(to);
        matrix[from][to] = element;
    };
    virtual void GetEdges(std::vector<std::pair<int, int>> v) {
        for (auto x: matrix) {
            for (auto y: matrix[x.first]) {
                v.push_back(std::make_pair(x.first, y.first));
            }
        }
    };

    MatrixGraph(){};

    MatrixGraph(IGraph<T> *_oth){};

    virtual int VerticesCount() const { return existingV.size(); };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const
    {
        for (auto x : matrix.at(vertex))
        {
            vertices.push_back(x.first);
        }
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const
    {
        for (auto x : matrix)
        {
            for (auto y : x.second)
            {
                if (y.first == vertex)
                {
                    vertices.push_back(x.first);
                }
            }
        }
    };
};

#endif //HOMEWORK_1_MATRIXGRAPH_H