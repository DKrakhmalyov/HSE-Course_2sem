
#ifndef HOMEWORK_1_ARCGRAPH_H
#define HOMEWORK_1_ARCGRAPH_H

#include "../graph.h"
#include <unordered_set>

template<typename T = void>
class ArcGraph : public IGraph<T> {
private:
    std::vector<std::tuple<int, int, T>> edges;
    std::unordered_set<int> vrtcs;
public:
    virtual void AddEdge(int from, int to, T &&element) {
        edges.emplace_back(from, to, std::forward<T>(element));
        vrtcs.insert(from);
        vrtcs.insert(to);
    };

    ArcGraph() {};

    ArcGraph(IGraph<T> *_oth) {
        for (auto v : _oth->GetAllVertices()) {
            std::vector<int> next;
            _oth->GetNextVertices(v, next);
            for (auto u : next)
                edges.emplace_back(v, u, _oth->GetWeight(v, u));
        }
    };

    virtual int VerticesCount() const { return vrtcs.size(); };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        for (auto const &[v, u, w] : edges) if (v == vertex) vertices.push_back(u);
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        for (auto const &[v, u, w] : edges) if (u == vertex) vertices.push_back(v);
    };

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
        std::unordered_map<int, bool> used;
        auto dfs = [&used, &vertices, this](int vrtx, auto &dfs_) mutable -> void {
            used[vrtx] = true;
            vertices.push_back(vrtx);
            std::vector<int> next;
            GetNextVertices(vrtx, next);
            for (auto v : next) {
                if (!used[v])
                    dfs_(v, dfs_);
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
            std::vector<int> next;
            GetNextVertices(q.front(), next);
            for (auto v : next)
                if (!used[v])
                    q.push(v), used[v] = true;
            vertices.push_back(q.front());
            q.pop();
        }
    };

    std::vector<int> GetAllVertices() const {
        return std::vector<int>(vrtcs.begin(), vrtcs.end());
    }

    T GetWeight(int from, int to) const {
        for (auto const &[v, u, w] : edges) if (from == v && to == u) return w;
    }

};

#endif //HOMEWORK_1_ARCGRAPH_H
