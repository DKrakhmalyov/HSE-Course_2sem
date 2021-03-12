
#ifndef HOMEWORK_1_LISTGRAPH_H
#define HOMEWORK_1_LISTGRAPH_H

#include "../graph.h"
#include <list>
#include <queue>
#include <algorithm>
#include <map>
#include <unordered_set>

template<typename T>
class ListGraph : public IGraph<T> {
private:
    std::unordered_set<int> vrtcs;
    std::unordered_map<int, std::list<std::pair<int, T>>> nodes;
public:
    virtual void AddEdge(int from, int to, T &&element) {
        nodes[from].push_back({to, std::forward<T>(element)});
        vrtcs.insert(from);
        vrtcs.insert(to);
    };

    ListGraph() {};

    ListGraph(IGraph<T> *_oth) {
        for (auto v : _oth->GetAllVertices()) {
            std::vector<int> next_vertices;
            _oth->GetNextVertices(v, next_vertices);
            for (auto u : next_vertices)
                AddEdge(v, u, _oth->GetWeight(v, u));
        }
    };

    virtual int VerticesCount() const {
        return vrtcs.size();
    };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        auto it = nodes.find(vertex);
        if (it == nodes.end()) return;
        for (auto const &[v, w] : it->second)
            vertices.push_back(v);
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        for (auto const &[v, lst] : nodes) {
            if (std::find_if(lst.begin(), lst.end(),
                             [vertex](const std::pair<int, int> &p) {
                                 return p.first == vertex;
                             }) != lst.end()) {
                vertices.push_back(v);
            }
        }
    };

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
        std::unordered_map<int, bool> used;
        auto dfs = [&used, &vertices, this](int vrtx, auto &dfs_) mutable -> void {
            used[vrtx] = true;
            vertices.push_back(vrtx);
            std::vector<int> next;
            GetNextVertices(vrtx, next);
            for (auto v: next) {
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

    virtual std::vector<int> GetAllVertices() const {
        return std::vector<int>(vrtcs.begin(), vrtcs.end());
    }

    virtual T GetWeight(int from, int to) const {
        auto it = std::find_if(nodes.at(from).begin(), nodes.at(from).end(),
                               [to](const std::pair<int, int> &p) {
                                   return p.first == to;
                               });
        if (it != nodes.at(from).end()) return it->second;
    }
};

#endif //HOMEWORK_1_LISTGRAPH_H
