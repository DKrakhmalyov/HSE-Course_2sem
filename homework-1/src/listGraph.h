
#ifndef HOMEWORK_1_LISTGRAPH_H
#define HOMEWORK_1_LISTGRAPH_H

#include "../graph.h"
#include <unordered_map>
#include <unordered_set>
#include <queue>

template<typename T>
class ListGraph : public IGraph<T> {
public:
    virtual void AddEdge(int from, int to, T &&element) {
        next[from].push_back({to, element});
        prev[to].push_back({from, std::forward<T>(element)});
    };

    ListGraph() {};

    ListGraph(IGraph<T> *_oth) {
        std::vector<std::pair<std::pair<int,int>, T>> edges;
        _oth->GetEdges(edges);
        for (auto &it : edges) {
            AddEdge(it.first.first, it.first.second, std::move(it.second));
        }
    };

    virtual int VerticesCount() const { 
        return next.size();
    };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        if (!next.contains(vertex))
            return;
        auto neededEdges = next.find(vertex);
        vertices.clear();
        vertices.reserve(neededEdges->second.size());
        for (auto nextVertex : neededEdges->second) {
            vertices.push_back(nextVertex.first);
        }
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        if (!prev.contains(vertex))
            return;
        auto neededEdges = prev.find(vertex);
        vertices.clear();
        vertices.reserve(neededEdges->second.size());
        for (auto prevVertex : neededEdges->second) {
            vertices.push_back(prevVertex.first);
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
            if (next.contains(vertex)) {
                auto neededEdges = next.find(vertex);
                for (auto &to : neededEdges->second) {
                    if (!used_nodes.contains(to.first)) {
                        q.push(to.first);
                        used_nodes.insert(to.first);
                    }
                }
            }
        }
    };
    virtual void GetEdges(std::vector<std::pair<std::pair<int,int>, T>> &edges) const {
        for (auto &from : next) {
            for (auto &to : from.second) {
                edges.push_back({{from.first, to.first}, to.second});
            }
        }
    };
private:
    std::unordered_map<int, std::vector<std::pair<int, T>>> next;
    std::unordered_map<int, std::vector<std::pair<int, T>>> prev;
    void dfs(int vertex, std::vector<int> &vertices, std::unordered_set<int>& used_nodes) const {
        used_nodes.insert(vertex);
        vertices.push_back(vertex);
        if (next.contains(vertex)) {
            auto neededEdges = next.find(vertex);
            for (auto &to : neededEdges->second) {
                if (!used_nodes.contains(to.first)) {
                    dfs(to.first, vertices, used_nodes);
                }
            }
        }
    }
};


#endif //HOMEWORK_1_LISTGRAPH_H
