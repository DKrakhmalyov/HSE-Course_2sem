#ifndef HOMEWORK_1_MATRIXGRAPH_H
#define HOMEWORK_1_MATRIXGRAPH_H


#include "../graph.h"

template<typename T = void>
class MatrixGraph : public IGraph<T> {

public:

    MatrixGraph() = default;

    virtual ~MatrixGraph() = default;

    MatrixGraph(const MatrixGraph<T> &other) = default;

    MatrixGraph(MatrixGraph<T> &&other) = default;

    MatrixGraph<T>& operator=(const MatrixGraph<T> &other) {
        if (&other == this)
            return *this;

        m_graph = other.m_graph;
        m_idx2vtx = other.m_idx2vtx;
        m_vtx2idx = other.m_vtx2idx;
        return *this;
    }

    MatrixGraph<T>& operator=(MatrixGraph<T> &&other) {
        if (&other == this)
            return *this;

        m_graph = std::move(other.m_graph);
        m_idx2vtx = std::move(other.m_idx2vtx);
        m_vtx2idx = std::move(other.m_vtx2idx);
        return *this;
    }

    MatrixGraph(IGraph<T> *_oth) {
        std::vector<std::pair<T, std::pair<int, int>>> arcGraph;
        _oth->TransformToArc(arcGraph);
        MatrixGraph<T>::ConstructFromArc(arcGraph);
    }

    virtual int VerticesCount() const {
        return static_cast<int>(m_graph.size());
    }
    
    virtual void AddEdge(int from, int to, T &&element) {
        if (m_vtx2idx.find(from) == m_vtx2idx.end())
            MatrixGraph<T>::AddVertex(from);

        if (m_vtx2idx.find(to) == m_vtx2idx.end())
            MatrixGraph<T>::AddVertex(to);

        if (MatrixGraph<T>::CheckEdge(m_vtx2idx.at(from), m_vtx2idx.at(to)))
            return;

        m_graph[m_vtx2idx.at(from)][m_vtx2idx.at(to)] = std::make_pair(true, element);
    }

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        if (m_vtx2idx.find(vertex) == m_vtx2idx.end())
            return;
        
        for (std::size_t to = 0; to < static_cast<std::size_t>(MatrixGraph<T>::VerticesCount()); to++)
            if (MatrixGraph<T>::CheckEdge(m_vtx2idx.at(vertex), to))
                vertices.push_back(m_idx2vtx[to]);
    }

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        if (m_vtx2idx.find(vertex) == m_vtx2idx.end())
            return;

        for (std::size_t from = 0; from < static_cast<std::size_t>(MatrixGraph<T>::VerticesCount()); from++)
            if (MatrixGraph<T>::CheckEdge(from, m_vtx2idx.at(vertex)))
                vertices.push_back(m_idx2vtx[from]);
    }

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
        if (m_vtx2idx.find(vertex) == m_vtx2idx.end())
            return;

        std::vector<bool> used(MatrixGraph<T>::VerticesCount(), false);
        MatrixGraph<T>::DoDFS(m_vtx2idx.at(vertex), vertices, used);
    }


    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
        if (m_vtx2idx.find(vertex) == m_vtx2idx.end())
            return;

        std::vector<bool> used(MatrixGraph<T>::VerticesCount(), false);
        MatrixGraph<T>::DoBFS(m_vtx2idx.at(vertex), vertices, used);
    }

    virtual void TransformToArc(std::vector<std::pair<T, std::pair<int, int>>> &graph) const {
        for (std::size_t from = 0; from < static_cast<std::size_t>(MatrixGraph<T>::VerticesCount()); from++)
            for (std::size_t to = 0; to < static_cast<std::size_t>(MatrixGraph<T>::VerticesCount()); to++)
                if (MatrixGraph<T>::CheckEdge(from, to))
                    graph.push_back(std::make_pair(
                        m_graph[from][to].second, 
                        std::make_pair(m_idx2vtx[from], m_idx2vtx[to]))
                    );
    }


private:

    void AddVertex(int vertex) {
        if (m_vtx2idx.find(vertex) != m_vtx2idx.end())
            return;

        m_vtx2idx[vertex] = m_vtx2idx.size();
        m_idx2vtx.push_back(vertex);

        MatrixGraph<T>::ResizeGraph(MatrixGraph<T>::VerticesCount() + 1);
    }

    void ResizeGraph(std::size_t new_size) {
        m_graph.resize(new_size);
        for (std::vector<std::pair<bool, T>> &i : m_graph)
            i.resize(new_size);
    }

    virtual bool CheckEdge(int from, int to) const {
        return m_graph[from][to].first;
    }

    virtual void ConstructFromArc(std::vector<std::pair<T, std::pair<int, int>>> &graph) {
        for (std::pair<T, std::pair<int, int>> &arc : graph) {
            MatrixGraph<T>::AddEdge(
                arc.second.first, 
                arc.second.second, 
                std::move(arc.first)
            );
        }
    }

    virtual void DoDFS(int vertex, std::vector<int> &vertices, std::vector<bool> &used) const {
        used[vertex] = true;
        vertices.push_back(m_idx2vtx[vertex]);

        for (std::size_t v = 0; v < static_cast<std::size_t>(MatrixGraph<T>::VerticesCount()); v++)
            if (MatrixGraph<T>::CheckEdge(vertex, v) && !used[v])
                DoDFS(v, vertices, used);
    }

    virtual void DoBFS(int vertex, std::vector<int> &vertices, std::vector<bool> &used) const {
        used[vertex] = true;

        std::queue<int> q;
        q.push(vertex);

        while (q.size()) {
            int current_vertex = q.front();
            vertices.push_back(m_idx2vtx[current_vertex]);
            q.pop();

            for (std::size_t v = 0; v < static_cast<std::size_t>(MatrixGraph<T>::VerticesCount()); v++)
                if (MatrixGraph<T>::CheckEdge(current_vertex, v) && !used[v]) {
                    q.push(v);
                    used[v] = true;
                }
        }
    }


public:

    std::vector<int> m_idx2vtx;

    std::unordered_map<int, int> m_vtx2idx;

    std::vector<std::vector<std::pair<bool, T>>> m_graph;
};

#endif //HOMEWORK_1_MATRIXGRAPH_H
