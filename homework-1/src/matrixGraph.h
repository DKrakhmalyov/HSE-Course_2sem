
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

    MatrixGraph(IGraph<T> *_oth) {
        std::multiset<std::tuple<int, int, T>> _graph;
        _oth->ConvertToArcGraph(_graph);
        ConvertFromArcGraph(_graph);
    }

    MatrixGraph<T>& operator=(const MatrixGraph<T> &other) {
        if (this != &other) {
            toId = other.toId;
            toVertex = other.toVertex;
            matrix = other.matrix;
        }
        return *this;
    }

    MatrixGraph<T>& operator=(MatrixGraph<T> &&other) {
        if (this != &other) {
            toId = std::move(other.toId);
            toVertex = std::move(other.toVertex);
            matrix = std::move(other.matrix);
        }
        return *this;
    }

    virtual void AddEdge(int from, int to, T &&element) override final {
        AddVertex(from);
        AddVertex(to);
        matrix[toId[from]][toId[to]].first = true;
        matrix[toId[from]][toId[to]].second.push_back(element);
    }

    virtual int VerticesCount() const override final  {
        return static_cast<int>(toVertex.size());
    }

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const override final {
        vertices.clear();
        if (toId.find(vertex) == toId.end()) {
            return;
        }
        for (int i = 0; i < VerticesCount(); ++i) {
            if (matrix[toId[vertex]][i].first) {
                vertices.push_back(toVertex[i]);
            }
        }
    }

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const override final {
        vertices.clear();
        if (toId.find(vertex) == toId.end()) {
            return;
        }
        for (int i = 0; i < VerticesCount(); ++i) {
            if (matrix[i][toId[vertex]].first) {
                vertices.push_back(toVertex[i]);
            }
        }
    }

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const override final {
        vertices.clear();
        if (toId.find(vertex) == toId.end()) {
            return;
        }
        std::vector<bool> used(VerticesCount(), false);
        std::function<void(int)> dfs = [&](int current) {
            int from = toId[current];
            used[from] = true;
            vertices.push_back(current);
            for (int to = 0; to < VerticesCount(); ++to) {
                if (matrix[from][to].first && !used[to]) { 
                    dfs(toVertex[to]);
                }
            }
        };
        dfs(vertex);
    }

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const override final {
        vertices.clear();
        if (toId.find(vertex) == toId.end()) {
            return;
        }
        std::vector<bool> used(VerticesCount(), false);
        std::queue<int, std::list<int>> bfs;
        used[toId[vertex]] = true;
        bfs.push(vertex);
        while (!bfs.empty()) {
            int current = bfs.front();
            bfs.pop();
            vertices.push_back(current);
            int from = toId[current];
            for (int to = 0; to < VerticesCount(); ++to) {
                if (matrix[from][to].first && !used[to]) {                
                    used[to] = true;
                    bfs.push(toVertex[to]);
                }
            }
        }
    }

    virtual void ConvertToArcGraph(std::multiset<std::tuple<int, int, T>>& _graph) override final {
        _graph.clear();
        for (int from = 0; from < VerticesCount(); from++) {
            for (int to = 0; to < VerticesCount(); to++) {
                for (const auto& wEdge: matrix[from][to].second) {
                    _graph.insert(std::make_tuple(
                        toVertex[from],
                        toVertex[to],
                        wEdge
                    ));
                }
            }
        }
    }

    virtual void ConvertFromArcGraph(std::multiset<std::tuple<int, int, T>>& _graph) override final {
        for (auto edge: _graph) {
            AddEdge(std::get<0>(edge), std::get<1>(edge), std::move(std::get<2>(edge)));
        }
    }

private:
    
    mutable std::map<int, int> toId;

    std::vector<int> toVertex;

    std::vector<std::vector<std::pair<bool, std::list<T>>>> matrix;

    void AddVertex(int vertex){
        if (toId.find(vertex) != toId.end()) {
            return;
        }
        toVertex.push_back(vertex);
        int sz = static_cast<int>(toVertex.size());
        toId[vertex] = sz - 1;
        matrix.emplace_back();
        for (auto& row: matrix) {
            row.resize(sz);
        }
    }
};

#endif //HOMEWORK_1_MATRIXGRAPH_H
