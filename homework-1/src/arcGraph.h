
#ifndef HOMEWORK_1_ARCGRAPH_H
#define HOMEWORK_1_ARCGRAPH_H

#include "../graph.h"
#include <unordered_set>
#include <queue>

template<typename T = void>
class ArcGraph : public IGraph<T> {
public:
    virtual void AddEdge(int from, int to, T &&element) {
        edges.push_back({from, to});
        weights.push_back(std::forward<T>(element));
    };

    ArcGraph() {};

    ArcGraph(IGraph<T> *_oth) {
        std::vector<std::pair<std::pair<int,int>, T>> edges;
        _oth->GetEdges(edges);
        for (auto &it : edges) {
            this->edges.push_back(it.first);
            this->weights.push_back(it.second);
        }
    };

    virtual int VerticesCount() const { 
        return edges.size(); 
    };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        for (auto &it : edges) {
            if (it.first == vertex) {
                vertices.push_back(it.second);
            }
        }
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
         for (auto &it : edges) {
            if (it.second == vertex) {
                vertices.push_back(it.first);
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
            for (auto &it : edges) {
                if (it.first == vertex && !used_nodes.contains(it.second)) {
                    q.push(it.second);
                    used_nodes.insert(it.second);
                }
            }
        }
    };
    virtual void GetEdges(std::vector<std::pair<std::pair<int,int>, T>> &edges) const {
        edges.reserve(this->edges.size());
        for (size_t i = 0; i < this->edges.size(); ++i) {
            edges.push_back({this->edges[i], weights[i]});
        }
    };
private:
    std::vector<std::pair<int,int>> edges;
    std::vector<T> weights;
    void dfs(int vertex, std::vector<int> &vertices, std::unordered_set<int>& used_nodes) const {
        used_nodes.insert(vertex);
        vertices.push_back(vertex);
        for (auto &it : edges) {
            if (it.first == vertex && !used_nodes.contains(it.second)) {
                dfs(it.second, vertices, used_nodes);
            }
        }
    }
};

#endif //HOMEWORK_1_ARCGRAPH_H
