#pragma once

#include "../graph.h"

template<typename T = void>
class MatrixGraph final : public IGraph<T> {
public:

    MatrixGraph();

    MatrixGraph(IGraph<T> *_oth);

    MatrixGraph(const MatrixGraph<T>& other);

    ~MatrixGraph();

    virtual void addEdge(const int32_t& from, const int32_t& to, T element) override;

    virtual int verticesCount() override;

    virtual void getNextVertices(const int32_t& vertex, std::vector<int32_t> &vertices) override;

    virtual void getPrevVertices(const int32_t& vertex, std::vector<int32_t> &vertices) override;

    virtual void deepFirstSearch(const int32_t& vertex, std::vector<int32_t> &vertices) override;

    virtual void breadthFirstSearch(const int32_t& vertex, std::vector<int32_t> &vertices) override;

    std::vector<std::map<int32_t, T>> getMatrix() const noexcept;

private:

    std::vector<std::map<int32_t, T>> matrix;

    void clearValue();

    bool valueIsEmpty() const noexcept;
    bool valueIsNotEmpty() const noexcept;

    MatrixGraph<T>* getCopy() const noexcept;
};
