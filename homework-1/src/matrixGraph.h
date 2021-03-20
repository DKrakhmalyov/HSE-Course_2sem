#ifndef HOMEWORK_1_MATRIXGRAPH_H
#define HOMEWORK_1_MATRIXGRAPH_H

#include "../graph.h"
#include <unordered_map>
#include <unordered_set>

template<typename T = void>
class MatrixGraph : public IGraph<T> {
public:

    virtual void AddEdge(int from, int to, T &&element) {
        mtrx[from][to] = std::move(element);
        vrtcs.insert(from);
        vrtcs.insert(to);
    };

    MatrixGraph() {};

    MatrixGraph(IGraph<T> *_oth) {
        for (auto i : _oth->GetAllVertices()) {
            std::vector<int> newbound;
            _oth->GetNextVertices(i, newbound);
            for (auto j : next)
                mtrx[i][j] = _oth->GetWeight(i, j);
        }
    };

     virtual int VerticesCount() const { return vrtcs.size(); };

     virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        auto it = mtrx.find(vertex);
        if (it == mtrx.end()) return;
        for (auto const &[i, j] : it->second) 
        vertices.push_back(i);
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        for (auto const &[i, mp] : mtrx){
            if (mp.find(vertex) != mp.end())
                vertices.push_back(i);
        }
    };

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
        std::unordered_map<int, bool> used;
        auto dfs = [&used, &vertices, this](int vrtx, auto &dfs_) mutable -> void {
            used[vrtx] = true;
            vertices.push_back(vrtx);
            std::vector<int> newbound;
            GetNextVertices(vrtx, newbound);
            for (auto i: newbound) {
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

    std::vector<int> GetAllVertices() const override {
        return std::vector<int>(vrtcs.begin(), vrtcs.end());
    }

    T GetWeight(int from, int to) const override {
        return mtrx.at(from).at(to);
    }
    private:
    std::unordered_map<int, std::unordered_map<int, T>> mtrx;
    std::unordered_set<int> vrtcs;
};

#endif //HOMEWORK_1_MATRIXGRAPH_H
