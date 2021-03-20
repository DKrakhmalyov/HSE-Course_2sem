#ifndef HOMEWORK_1_ARCGRAPH_H
#define HOMEWORK_1_ARCGRAPH_H

#include "../graph.h"
#include <unordered_set>

template<typename T = void>
class ArcGraph : public IGraph<T> {

public:
virtual void AddEdge(int from, int to, T &&element) {
        edges.emplace_back(from, to, std::forward<T>(element));
        vrtcs.insert(from);
        vrtcs.insert(to);
    };

    ArcGraph() {};

     ArcGraph(IGraph<T> *_oth) {
        for (auto i : _oth->GetAllVertices()) {
            std::vector<int> newbound;
            _oth->GetNextVertices(i, newbound);
            for (auto j : newbound)
                edges.emplace_back(i, j, _oth->GetWeight(i, j));
        }
    };

    virtual int VerticesCount() const { return vrtcs.size(); };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        for (auto const &[i, j, w] : edges) 
        if (i == vertex) vertices.push_back(j);
    };

     virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        for (auto const &[i, j, w] : edges) 
        if (j == vertex) vertices.push_back(i);
    };

      virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
        std::unordered_map<int, bool> used;
        auto dfs = [&used, &vertices, this](int vrtx, auto &dfs_) mutable -> void {
            used[vrtx] = true;
            vertices.push_back(vrtx);
            std::vector<int> newbound;
            GetNextVertices(vrtx, newbound);
            for (auto i : newbound) {
                if (!used[i])
                    dfs_(i, dfs_);
            }
        };
        dfs(vertex, dfs);
    };

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
        std::unordered_map<int, bool> used;
        std::queue<int> q;
        q.push(vertex);
        used[vertex] = true;
        while (!q.empty()) {
            std::vector<int> newbound;
            GetNextVertices(q.front(), newbound);
            for (auto i : newbound)
                if (!used[i])
                    q.push(i), used[i] = true;
            vertices.push_back(q.front());
            q.pop();
        }
    };

    T GetWeight(int from, int to) const {
        for (auto const &[i, j, w] : edges) 
        if (from == i && to == j) return w;
    }
    std::vector<int> GetAllVertices() const {
        return std::vector<int>(vrtcs.begin(), vrtcs.end());
    }

    private:
    std::vector<std::tuple<int, int, T>> edges;
    std::unordered_set<int> vrtcs;
};
    #endif //HOMEWORK_1_ARCGRAPH_H
