
#ifndef HOMEWORK_1_MATRIXGRAPH_H
#define HOMEWORK_1_MATRIXGRAPH_H


#include "../graph.h"

template<typename T = void>
class MatrixGraph : public IGraph<T> {
    std::unordered_map<int, std::unordered_map<int, T>> data_;
    std::unordered_set<int> vertices_;
public:
    virtual void AddEdge(int from, int to, T &&element) {
        data_[from][to] = std::forward<T>(element);
        vertices_.insert(from);
        vertices_.insert(to);
    };

    MatrixGraph() {};

    MatrixGraph(IGraph<T> *_oth) {
        this->Construct(*_oth);
    };

    virtual int VerticesCount() const override { return vertices_.size(); };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const override {
        if (!data_.contains(vertex))
            return;
        for (auto const &[vertex, _] : data_.at(vertex))
            vertices.push_back(vertex);
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const override{
        if (!vertices_.contains(vertex))
            return;
        for (auto const &[from, tos] : data_) {
            if (tos.contains(vertex))
                vertices.push_back(from);
        }
    };

    void GetVertices(std::vector<int> &vertices) const override {
        vertices.assign(vertices_.begin(), vertices_.end());
    }


    T GetEdgeWeight(int from, int to) const override {
        return data_.at(from).at(to);
    }
};

#endif //HOMEWORK_1_MATRIXGRAPH_H
