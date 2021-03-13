
#ifndef HOMEWORK_1_MATRIXGRAPH_H
#define HOMEWORK_1_MATRIXGRAPH_H


#include "../graph.h"
#include <unordered_map>
#include <unordered_set>
#include <queue>

template<typename T = void>
class MatrixGraph : public IGraph<T> {
public:
    virtual void AddEdge(int from, int to, T &&element) {
        AddVertex(from);
        AddVertex(to);
        isConnected[newID[from]][newID[to]] = true;
        weights[newID[from]][newID[to]] = std::forward<T>(element);
    };

    MatrixGraph() : size(0) {};

    MatrixGraph(IGraph<T> *_oth) : size(0) {
        std::vector<std::pair<std::pair<int,int>, T>> edges;
        _oth->GetEdges(edges);
        for (auto &it : edges) {
            int from = it.first.first;
            int to = it.first.second;
            T weight = it.second;
            AddEdge(from, to, std::forward<T>(weight));
        }
    };

    virtual int VerticesCount() const { 
        return size;
    };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        if (!newID.contains(vertex)) return;
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                if (isConnected[i][j] && newID.find(vertex)->second == i) {
                    vertices.push_back(oldID.find(j)->second);
                }
            }
        }
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        if (!newID.contains(vertex)) return;
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                if (isConnected[i][j] && newID.find(vertex)->second == j) {
                    vertices.push_back(oldID.find(i)->second);
                }
            }
        }
    };

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
        std::unordered_set<int> used_nodes;
        dfs(vertex, vertices, used_nodes);
    };

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
        std::unordered_set<int> used_nodes;
        std::queue<int> q;
        q.push(vertex);
        while(!q.empty()) {
            vertex = q.front();
            q.pop();
            vertices.push_back(vertex);
            for (size_t to = 0; to < size; ++to) {
                size_t id = oldID.find(to)->second;
                if (isConnected[newID.find(vertex)->second][to] && !used_nodes.contains(id)) {
                    q.push(id);
                    used_nodes.insert(id);
                }
            }
        }
    };

    virtual void GetEdges(std::vector<std::pair<std::pair<int,int>, T>> &edges) const {
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                if (isConnected[i][j]) {
                    edges.emplace_back(std::make_pair(oldID.find(i)->second, oldID.find(j)->second), weights[i][j]);
                }
            }
        }
    };
private:
    size_t size;
    std::vector<std::vector<bool>> isConnected;
    std::vector<std::vector<T>> weights;
    std::unordered_map<int,int> newID;
    std::unordered_map<int,int> oldID;
    virtual void AddVertex(int vertex) {
        if (newID.contains(vertex)) return;
        newID[vertex] = size;
        oldID[size] = vertex;
        size++;
        isConnected.resize(size);
        for (auto &it : isConnected) {
            it.resize(size);
        }
        weights.resize(size);
        for (auto &it : weights) {
            it.resize(size);
        }
    };
    void dfs(int vertex, std::vector<int> &vertices, std::unordered_set<int>& used_nodes) const {
        used_nodes.insert(vertex);
        vertices.push_back(vertex);
         for (size_t to = 0; to < size; ++to) {
                size_t id = oldID.find(to)->second;
                if (isConnected[newID.find(vertex)->second][to] && !used_nodes.contains(id)) {
                    dfs(id, vertices,used_nodes);
                }
            }
    }
};

#endif //HOMEWORK_1_MATRIXGRAPH_H
