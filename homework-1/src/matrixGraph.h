
#ifndef HOMEWORK_1_MATRIXGRAPH_H
#define HOMEWORK_1_MATRIXGRAPH_H


#include "../graph.h"
#include <unordered_map>
#include <unordered_set>

template<typename T = void>
class MatrixGraph : public IGraph<T> {
private:
    std::unordered_map<int, std::unordered_map<int, T>> mtrx;
    std::unordered_set<int> vrtcs;
public:
    virtual void AddEdge(int from, int to, T &&element) {
        mtrx[from][to] = std::move(element);
        vrtcs.insert(from);
        vrtcs.insert(to);
    };

    MatrixGraph() {};

    MatrixGraph(IGraph<T> *_oth) {
        for (auto v : _oth->GetAllVertices()) {
            std::vector<int> next;
            _oth->GetNextVertices(v, next);
            for (auto u : next)
                mtrx[v][u] = _oth->GetWeight(v, u);
        }
    };

    virtual int VerticesCount() const { return vrtcs.size(); };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        auto it = mtrx.find(vertex);
        if (it == mtrx.end()) return;
        for (auto const &[v, w] : it->second) vertices.push_back(v);
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        for (auto const &[v, mp] : mtrx){
            if (mp.find(vertex) != mp.end())
                vertices.push_back(v);
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

    std::vector<int> GetAllVertices() const override {
        return std::vector<int>(vrtcs.begin(), vrtcs.end());
    }

    T GetWeight(int from, int to) const override {
        return mtrx.at(from).at(to);
    }
};

#endif //HOMEWORK_1_MATRIXGRAPH_H
