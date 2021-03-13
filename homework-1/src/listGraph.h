#pragma once

#include "../graph.h"

template<typename T>
class ListGraph final: public IGraph<T> {
public:

    ListGraph() noexcept;

    ListGraph(IGraph<T> *_oth) noexcept;

    ListGraph(const ListGraph<T>& other) noexcept;

    ~ListGraph() noexcept;

    virtual void addEdge(const int32_t& from, const int32_t& to, T element) override;

    virtual int verticesCount() override;

    virtual void getNextVertices(const int32_t& vertex, std::vector<int32_t> &vertices) override;

    virtual void getPrevVertices(const int32_t& vertex, std::vector<int32_t> &vertices) override;

    virtual void deepFirstSearch(const int32_t& vertex, std::vector<int32_t> &vertices) override;

    virtual void breadthFirstSearch(const int32_t& vertex, std::vector<int32_t> &vertices) override;

    std::vector<std::vector<std::pair<int32_t, T*>>> getListOfEdges() const noexcept;

private:

    std::vector<std::vector<std::pair<int32_t, T*>>> listOfEdges;

    bool valueIsEmpty() const noexcept;
    bool valueIsNotEmpty() const noexcept;

    void clearValue();

    ListGraph<T>* getCopy() const noexcept;

    void dfs(const int32_t currentVertice, std::vector<bool>& used, std::vector<int32_t>& resultVector) const noexcept;
    void bfs(const int32_t startVertice, std::vector<int32_t>& resultVector) const noexcept;
};

