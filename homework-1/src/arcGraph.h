#ifndef HOMEWORK_1_ARCGRAPH_H
#define HOMEWORK_1_ARCGRAPH_H

#include <vector>
#include <unordered_map>
#include <iostream>

#include "../graph.h"

template<typename T = void>
class ArcGraph : public IGraph<T> {
    private: 
    std::vector<std::pair<int, int>> edges;
    std::vector<T> weigths;
    std::unordered_map<int, int> vertices_count;
    std::unordered_map<int, int> reverse_vertices;

    int GetVertex(int v) {
        if (vertices_count.find(v) == vertices_count.end()) {
            reverse_vertices[vertices_count.size()] = v;
            vertices_count[v] = vertices_count.size();
        }
        return vertices_count[v];
    }


    void GetGraphStructure(std::vector<std::vector<int>> &graph) const {
        int n = VerticesCount();
        graph.resize(n);
        for (int i = 0; i < edges.size(); ++i) {
            graph[edges[i].first].push_back(edges[i].second);
        }
    }

    public:
    ArcGraph() {}

    ArcGraph(IGraph<T> *another) {

        std::vector<std::pair<int, int>> another_edges;
        another->GetEdges(another_edges, weigths);


        for (int i = 0; i < another_edges.size(); ++i) {
            int from = GetVertex(another_edges[i].first);
            int to = GetVertex(another_edges[i].second);
            edges.push_back(std::make_pair(from, to));
        }
    }

    void AddEdge(int from, int to, T &&element) override {
        from = GetVertex(from);
        to = GetVertex(to);
        edges.push_back(std::make_pair(from, to));
        weigths.push_back(element);
    };

    int VerticesCount() const override {
        return vertices_count.size(); 
    };

    void GetNextVertices(int vertex, std::vector<int> &vertices) const override {
        if (vertices_count.find(vertex) != vertices_count.end()) {
            vertex = vertices_count.at(vertex);
            for (auto e : edges) {
                if (e.first == vertex) {
                    vertices.push_back(reverse_vertices.at(e.second));
                }
            }
        }
    };

    void GetPrevVertices(int vertex, std::vector<int> &vertices) const override {
        if (vertices_count.find(vertex) != vertices_count.end()) {
            vertex = vertices_count.at(vertex);
            for (auto e : edges) {
                if (e.second == vertex) {
                    vertices.push_back(reverse_vertices.at(e.first));
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
        for (auto e : this->edges) {
            edges.push_back(std::make_pair(reverse_vertices.at(e.first), reverse_vertices.at(e.second)));
        }
        weigths = this->weigths;
    }
};

#endif //HOMEWORK_1_ARCGRAPH_H
