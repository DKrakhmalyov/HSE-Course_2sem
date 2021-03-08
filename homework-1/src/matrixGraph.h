
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
        AddVertex(from);
        AddVertex(to);

        from = newNumber[from];
        to = newNumber[to];

        matrix[from][to] = true;
        weights[from][to] = std::forward<T>(element);
    };

    virtual void GetEdges(std::vector<std::pair<int, int>> &edges, std::vector<T> &weights) const
    {
        for (int i = 0; i < matrix.size(); i++)
            for (int j = 0; i < matrix[i].size(); i++)
                if (matrix[i][j])
                {
                    edges.push_back({oldNumber.at(i), oldNumber.at(j)});
                    weights.push_back(this->weights[i][j]);
                }
    };

    virtual int VerticesCount() const
    {
        return newNumber.size();
    };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const
    {
        if (!newNumber.contains(vertex))
            return;

        vertex = newNumber.at(vertex);

        for (int i = 0; i < matrix[vertex].size(); i++)
            if (matrix[vertex][i])
                vertices.push_back(oldNumber.at(i));
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const
    {
        if (!newNumber.contains(vertex))
            return;

        vertex = newNumber.at(vertex);

        for (int i = 0; i < matrix.size(); i++)
            if (matrix[i][vertex])
                vertices.push_back(oldNumber.at(i));
    };

private:
    std::vector<std::vector<bool>> matrix;
    std::vector<std::vector<T>> weights;
    std::unordered_map<int, int> newNumber;
    std::unordered_map<int, int> oldNumber;

    void AddVertex(int vertex)
    {
        if (newNumber.contains(vertex))
            return;

        newNumber[vertex] = newNumber.size();
        oldNumber[newNumber.size() - 1] = vertex;

        int n = newNumber.size();

        matrix.resize(n);
        for (auto &row : matrix)
            row.resize(n);

        weights.resize(n);
        for (auto &row : weights)
            row.resize(n);
    }
};

#endif //HOMEWORK_1_MATRIXGRAPH_H
