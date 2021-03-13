#ifndef HOMEWORK_1_LISTGRAPH_H
#define HOMEWORK_1_LISTGRAPH_H

#include <queue>
#include <algorithm>
#include <unordered_map>
#include <iostream>

#include "../graph.h"

template<typename T>
class ListGraph : public IGraph<T> {
public:
    private:
    std::vector<std::vector<int>> lists;
    std::vector<std::vector<int>> reverse_lists;
    std::vector<std::vector<T>> weigths;
    std::unordered_map<int, int> vertices_count;
    std::unordered_map<int, int> reverse_vertices;

    int GetVertex(int v) {
        if (vertices_count.find(v) == vertices_count.end()) {
            reverse_vertices[vertices_count.size()] = v;
            vertices_count[v] = vertices_count.size();
            lists.push_back(std::vector<int>());
            reverse_lists.push_back(std::vector<int>());
            weigths.push_back(std::vector<T>());
        }
        return vertices_count[v];
    }

    public:
    ListGraph() {}

    ListGraph(const IGraph<T>* another) {

        int n = another->VerticesCount();
        std::vector<std::pair<int, int>> another_edges;
        std::vector<T> another_weigths;
        another->GetEdges(another_edges, another_weigths);

        lists = std::vector<std::vector<int>>(n);

        for (int i = 0; i < another_edges.size(); ++i) {
            int from = GetVertex(another_edges[i].first);
            int to = GetVertex(another_edges[i].second);
            lists[from].push_back(to);
            reverse_lists[to].push_back(from);
            weigths[from].push_back(another_weigths[i]);
        }
    }

    void AddEdge(int from, int to, T &&element) override {
        from = GetVertex(from);
        to = GetVertex(to);

        lists[from].push_back(to);
        reverse_lists[to].push_back(from);
        weigths[from].push_back(element);
    };

    int VerticesCount() const override { return vertices_count.size(); };

    void GetNextVertices(int vertex, std::vector<int> &vertices) const override {
        if (vertices_count.find(vertex) != vertices_count.end()) {
            vertex = vertices_count.at(vertex);

            for (auto e : lists[vertex]) {
                vertices.push_back(reverse_vertices.at(e));
            }
        }
    };

    void GetPrevVertices(int vertex, std::vector<int> &vertices) const override {
        if (vertices_count.find(vertex) != vertices_count.end()) {
            vertex = vertices_count.at(vertex);

            for (auto e : reverse_lists[vertex]) {
                vertices.push_back(reverse_vertices.at(e));
            }
        }
    };

    void DeepFirstSearch(int vertex, std::vector<int> &vertices) const override {
        if (vertices_count.find(vertex) != vertices_count.end()) {
            vertex = vertices_count.at(vertex);

            std::vector<int> first(lists.size(), 0);

            std::vector<int> stack;
            stack.push_back(vertex);
            vertices.push_back(vertex);

            while (!stack.empty()) {
                int v = stack.back();
            
                if (first[v] < lists[v].size()) {
                    int u = lists[v][first[v]++];
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

            std::vector<bool> used(lists.size(), 0);

            std::queue<int> vertices_queue;
            vertices_queue.push(vertex);
            vertices.push_back(vertex);

            while (!vertices_queue.empty()) {
                int v = vertices_queue.front();
                vertices_queue.pop();

                used[v] = 1;

                for (auto u : lists[v]) {
                    if (!used[u]) {
                        vertices_queue.push(u);
                        vertices.push_back(u);
                    }
                }
            }
        }
    };
    
    void GetEdges(std::vector<std::pair<int, int>> &edges, std::vector<T> &weigths) const override {
        for (int v = 0; v < lists.size(); ++v) {
            for (int u = 0; u < lists[v].size(); ++u) {
                edges.push_back(std::make_pair(reverse_vertices.at(v), reverse_vertices.at(lists[v][u])));
                weigths.push_back(this->weigths[v][u]);
            }
        }
    }
};


#endif //HOMEWORK_1_LISTGRAPH_H
