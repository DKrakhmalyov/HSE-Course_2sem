#ifndef HOMEWORK_1_MATRIXGRAPH_H
#define HOMEWORK_1_MATRIXGRAPH_H

#include <algorithm>
#include <unordered_map>

#include "../graph.h"

template<typename T = void>
class MatrixGraph : public IGraph<T> {
    private:
    std::vector<std::vector<bool>> matrix;
    std::vector<std::vector<T>> weigths;
    std::unordered_map<int, int> vertices_count;
    std::unordered_map<int, int> reverse_vertices;

    int GetVertex(int v) {
        if (vertices_count.find(v) == vertices_count.end()) {
            int n = vertices_count.size();
            reverse_vertices[n] = v;
            vertices_count[v] = n;
            for (int i = 0; i < n; ++i) {
                matrix[i].push_back(false);
                weigths[i].push_back(T());
            }
            int new_n = vertices_count.size();
            matrix.push_back(std::vector<bool>(new_n));
            weigths.push_back(std::vector<T>(new_n));
        }
        return vertices_count[v];
    }


    void GetGraphStructure(std::vector<std::vector<int>> &graph) const {
        int n = vertices_count.size();

        graph.resize(n);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j]) {
                    graph[i].push_back(j);
                }
            }
        }
    }

    public:
    MatrixGraph() {}

    MatrixGraph(const IGraph<T>* another) {

        int n = another->VerticesCount();

        matrix.resize(n, std::vector<bool>(n));
        weigths.resize(n, std::vector<T>(n));

        std::vector<std::pair<int, int>> another_edges;
        std::vector<T> another_weigths;

        another->GetEdges(another_edges, another_weigths);

        for (int i = 0; i < another_edges.size(); ++i) {
            int from = GetVertex(another_edges[i].first);
            int to = GetVertex(another_edges[i].second);
            matrix[from][to] = 1;
            weigths[from][to] =  another_weigths[i];
        }
    }

    void AddEdge(int from, int to, T &&element) override {
        from = GetVertex(from);
        to = GetVertex(to);

        matrix[from][to] = element;
    };

    int VerticesCount() const override { return vertices_count.size(); };

    void GetNextVertices(int vertex, std::vector<int> &vertices) const override {
        if (vertices_count.find(vertex) != vertices_count.end()) {
            vertex = vertices_count.at(vertex);

            for (int i = 0; i < VerticesCount(); ++i) {
                if (matrix[vertex][i]) {
                    vertices.push_back(reverse_vertices.at(i));
                }
            }
        }
    };

    void GetPrevVertices(int vertex, std::vector<int> &vertices) const override {
        if (vertices_count.find(vertex) != vertices_count.end()) {
            vertex = vertices_count.at(vertex);

            for (int i = 0; i < VerticesCount(); ++i) {
                if (matrix[i][vertex]) {
                    vertices.push_back(reverse_vertices.at(i));
                }
            }
        }
    };

    void DeepFirstSearch(int vertex, std::vector<int> &vertices) const override {
        if (vertices_count.find(vertex) != vertices_count.end()) {
            vertex = vertices_count.at(vertex);

            std::vector<std::vector<int>> graph;
            this->GetGraphStructure(graph);

            std::vector<int> first(graph.size(), 0);

            std::vector<int> stack;
            stack.push_back(vertex);
            vertices.push_back(vertex);

            while (!stack.empty()) {
                int v = stack.back();

                if (first[v] < graph[v].size()) {
                    int u = graph[v][first[v]++];
                    if (first[u] == 0) {
                        stack.push_back(u);
                        vertices.push_back(reverse_vertices.at(u));
                    }
                } else {
                    stack.pop_back();
                }
            }
        }
    };

    void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const override {
        if (vertices_count.find(vertex) != vertices_count.end()) {
            vertex = vertices_count.at(vertex);

            std::vector<std::vector<int>> graph;
            GetGraphStructure(graph);

            std::vector<bool> used(graph.size(), 0);

            std::queue<int> vertices_queue;
            vertices_queue.push(vertex);
            vertices.push_back(vertex);

            while (!vertices_queue.empty()) {
                int v = vertices_queue.front();
                vertices_queue.pop();

                used[v] = 1;

                for (auto u : graph[v]) {
                    if (!used[u]) {
                        vertices_queue.push(u);
                        vertices.push_back(reverse_vertices.at(u));
                    }
                }
            }
        }
    };

    void GetEdges(std::vector<std::pair<int, int>> &edges, std::vector<T> &weigths) const override {
        int n = VerticesCount();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j]) {
                    edges.push_back(std::make_pair(reverse_vertices.at(i), reverse_vertices.at(j)));
                    weigths.push_back(this->weigths[i][j]);
                }
            }
        }
    }
};

#endif //HOMEWORK_1_MATRIXGRAPH_H
