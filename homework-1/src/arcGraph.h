
#ifndef HOMEWORK_1_ARCGRAPH_H
#define HOMEWORK_1_ARCGRAPH_H

#include "../graph.h"

template<typename T>
class ArcGraph : public IGraph<T> {

public:

    ArcGraph() = default;

    virtual ~ArcGraph() = default;

    ArcGraph(const ArcGraph<T> &other) = default;

    ArcGraph(ArcGraph<T> &&other) = default;

    ArcGraph<T>& operator=(const ArcGraph<T> &other) {
        if (&other == this)
            return *this;

        m_graph = other.m_graph;
        m_vtx2idx = other.m_vtx2idx;
        m_idx2vtx = other.m_idx2vtx;
        return *this;
    }

    ArcGraph<T>& operator=(ArcGraph<T> &&other) {
        if (&other == this)
            return *this;

        m_graph = std::move(other.m_graph);
        m_vtx2idx = std::move(other.m_vtx2idx);
        m_idx2vtx = std::move(other.m_idx2vtx);
        return *this;
    }


    ArcGraph(IGraph<T> *_oth) {
        std::vector<std::pair<T, std::pair<int, int>>> arcGraph;
        _oth->TransformToArc(arcGraph);
        ArcGraph<T>::ConstructFromArc(arcGraph);
    }

    virtual int VerticesCount() const {
        return static_cast<int>(m_idx2vtx.size());
    }

    virtual void AddEdge(int from, int to, T &&element) {
        if (ArcGraph<T>::CheckEdge(from, to))
            return;

        if (m_vtx2idx.find(from) == m_vtx2idx.end())
            ArcGraph<T>::AddVertex(from);

        if (m_vtx2idx.find(to) == m_vtx2idx.end())
            ArcGraph<T>::AddVertex(to);

        m_graph.push_back(std::make_pair(element, std::make_pair(from, to)));
    }

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        for (const std::pair<T, std::pair<int, int>> &i : m_graph)
            if (i.second.first == vertex)
                vertices.push_back(i.second.second);
    }

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        for (const std::pair<T, std::pair<int, int>> &i : m_graph)
            if (i.second.second == vertex)
                vertices.push_back(i.second.first);
    }

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
        if (m_vtx2idx.find(vertex) == m_vtx2idx.end())
            return;

        std::vector<bool> used(ArcGraph<T>::VerticesCount(), false);
        ArcGraph<T>::DoDFS(vertex, vertices, used);
    }

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
        if (m_vtx2idx.find(vertex) == m_vtx2idx.end())
            return;

        std::vector<bool> used(ArcGraph<T>::VerticesCount(), false);
        ArcGraph<T>::DoBFS(vertex, vertices, used);
    }

    virtual void TransformToArc(std::vector<std::pair<T, std::pair<int, int>>> &graph) const {
        graph = m_graph;
    }

private:

    void AddVertex(int vertex) {
        if (m_vtx2idx.find(vertex) != m_vtx2idx.end())
            return;

        m_vtx2idx[vertex] = m_vtx2idx.size();    
        m_idx2vtx.push_back(vertex);
    }

    virtual bool CheckEdge(int from, int to) const {
        for (const std::pair<T, std::pair<int, int>> &i : m_graph)
            if (i.second.first == from && i.second.second == to)
                return true;
        return false;
    }


    virtual void ConstructFromArc(std::vector<std::pair<T, std::pair<int, int>>> &graph) {
        for (std::pair<T, std::pair<int, int>> &arc : graph)
            ArcGraph<T>::AddEdge(arc.second.first, arc.second.second, std::move(arc.first));
    }

    virtual void DoDFS(int vertex, std::vector<int> &vertices, std::vector<bool> &used) const {
        used[m_vtx2idx.at(vertex)] = true;
        vertices.push_back(vertex);

        for (const std::pair<T, std::pair<int, int>> &v : m_graph)
            if (v.second.first == vertex && !used[m_vtx2idx.at(v.second.second)])
                ArcGraph<T>::DoDFS(v.second.second, vertices, used);
    }

    virtual void DoBFS(int vertex, std::vector<int> &vertices, std::vector<bool> &used) const {
        used[m_vtx2idx.at(vertex)] = true;

        std::queue<int> q;
        q.push(vertex);

        while (q.size()) {
            int current_vertex = q.front();
            vertices.push_back(current_vertex);
            q.pop();

            for (const std::pair<T, std::pair<int, int>> &v : m_graph)
                if (v.second.first == current_vertex && !used[m_vtx2idx.at(v.second.second)]) {
                    used[m_vtx2idx.at(v.second.second)] = true;
                    q.push(v.second.second);
                }
        }
    }
    
private:

    std::vector<int> m_idx2vtx;

    std::unordered_map<int, int> m_vtx2idx;

    std::vector<std::pair<T, std::pair<int, int>>> m_graph;

};

#endif //HOMEWORK_1_ARCGRAPH_H
