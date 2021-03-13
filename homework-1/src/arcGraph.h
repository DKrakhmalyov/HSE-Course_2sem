#pragma once

#include "../graph.h"

template<typename T>
class ArcGraph final: public IGraph<T> {
public:

    ArcGraph() = default;
    ArcGraph(IGraph<T>* other);
    ArcGraph(const ArcGraph& graph);
    virtual ~ArcGraph();

    virtual void addEdge(const int32_t& from, const int32_t& to, T element) override;

    virtual int verticesCount() override;

    virtual void getNextVertices(const int32_t& vertex, std::vector<int32_t> &vertices) override;

    virtual void getPrevVertices(const int32_t& vertex, std::vector<int32_t> &vertices) override;

    virtual void deepFirstSearch(const int32_t& vertex, std::vector<int32_t> &vertices) override;

    virtual void breadthFirstSearch(const int32_t& vertex, std::vector<int32_t> &vertices) override;

    ArcGraph<T>& operator = (const ArcGraph<T>& other) noexcept;

    std::vector<NodePair<T>*> getListOfEdges() const noexcept;

private:
    
    std::vector<NodePair<T>*> pairsOfVertices;

    void clearValue() noexcept;

    bool isValueEmpty() const noexcept;
    bool isValueNotEmpty() const noexcept;

    ArcGraph<T>* getCopy() const noexcept;
};