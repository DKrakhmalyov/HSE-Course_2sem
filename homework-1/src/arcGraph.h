
#ifndef HOMEWORK_1_ARCGRAPH_H
#define HOMEWORK_1_ARCGRAPH_H

#include "../graph.h"

template<typename T>
class ArcGraph : public IGraph<T> {

public:

    ArcGraph() = default;

    ArcGraph(IGraph<T> *_oth);

    virtual ~ArcGraph() = default;

    virtual int VerticesCount() const;

    virtual void AddEdge(int from, int to, T &&element);

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const;

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const;

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const;

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const;

    virtual void TransformToArc(std::vector<std::pair<T, std::pair<int, int>>> &graph) const;

private:

    void AddVertex(int vertex);

    virtual bool CheckEdge(int from, int to) const;

    virtual void ConstructFromArc(std::vector<std::pair<T, std::pair<int, int>>> &graph);

    virtual void DoDFS(int vertex, std::vector<int> &vertices, std::vector<bool> &used) const;

    virtual void DoBFS(int vertex, std::vector<int> &vertices, std::vector<bool> &used) const;

private:

    std::vector<int> m_idx2vtx;

    std::unordered_map<int, int> m_vtx2idx;

    std::vector<std::pair<T, std::pair<int, int>>> m_graph;

};

#endif //HOMEWORK_1_ARCGRAPH_H
