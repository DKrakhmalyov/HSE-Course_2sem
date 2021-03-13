
#ifndef HOMEWORK_1_ARCGRAPH_H
#define HOMEWORK_1_ARCGRAPH_H

#include "../graph.h"

template<typename T = void>
class ArcGraph : public IGraph<T> {
    std::map<std::pair<int, int>, T> data_;
    std::unordered_set<int> vertices_;
public:
    virtual void AddEdge(int from, int to, T &&element) override {
        data_[{from, to}] = std::forward<T>(element);
        vertices_.insert(from);
        vertices_.insert(to);
    }

    ArcGraph() {};

    ArcGraph(IGraph<T> *_oth) {
        this->Construct(*_oth);
    }

    virtual int VerticesCount() const override { return vertices_.size(); };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const override {
        auto it = data_.lower_bound({vertex, INT32_MIN});
        for (auto i = it; i != data_.end() && i->first.first == vertex; ++i) {
            vertices.push_back(i->first.second);
        }
    }

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const override {
        for (auto const &[edge, weight] : data_) {
            if (edge.second == vertex)
                vertices.push_back(edge.first);
        }
    }

    void GetVertices(std::vector<int> &vertices) const override {
        vertices.assign(vertices_.begin(), vertices_.end());
    }

    T GetEdgeWeight(int from, int to) const override {
        return data_.at({from, to});
    }
};

#endif //HOMEWORK_1_ARCGRAPH_H
