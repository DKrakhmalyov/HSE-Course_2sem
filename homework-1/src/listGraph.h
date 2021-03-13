
#ifndef HOMEWORK_1_LISTGRAPH_H
#define HOMEWORK_1_LISTGRAPH_H

#include <unordered_set>
#include <queue>
#include "../graph.h"


template<typename T>
class ListGraph : public IGraph<T> {
    std::unordered_map<int, std::vector<std::pair<int, T>>> data_;
    std::unordered_map<int, std::vector<int>> prev_data_;
    std::unordered_set<int> vertices_;
public:
    virtual void AddEdge(int from, int to, T &&element) {
        data_[from].emplace_back(to, std::move(element));
        prev_data_[to].emplace_back(from);
        vertices_.insert(from);
        vertices_.insert(to);
    }

    ListGraph() = default;

    ListGraph(IGraph<T> *_oth) {
        this->Construct(*_oth);
    }

    virtual int VerticesCount() const { return vertices_.size(); }

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const override {
        if (!data_.contains(vertex))
            return;
        for (auto const &[i, _] : data_.at(vertex))
            vertices.push_back(i);
    }

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const override {
        if (!prev_data_.contains(vertex))
            return;
        vertices = prev_data_.at(vertex);
    }

    void GetVertices(std::vector<int> &vertices) const override {
        vertices.assign(vertices_.begin(), vertices_.end());
    }

    T GetEdgeWeight(int from, int to) const override {
        auto &search = data_.at(from);
        return std::find_if(search.begin(), search.end(),
                         [to](auto const &value) { return value.first == to; })->second;

    }
};


#endif //HOMEWORK_1_LISTGRAPH_H
