
#ifndef HOMEWORK_1_ARCGRAPH_H
#define HOMEWORK_1_ARCGRAPH_H

#include <set>
#include <cassert>
#include "../graph.h"
#include "graphConverter.h"

template<typename T = void>
class ArcGraph : public IGraph<T> {
public:
    virtual void AddEdge(int from, int to, T &&element) {
        edges.push_back(Edge(from, to, element));
    };

    ArcGraph() {};

    ArcGraph(IGraph<T> *_oth) {
        GraphConverter<T, ArcGraph>().convertTo(_oth, this);
    };

    virtual int VerticesCount() const {
        std::vector<int> vertices;
        GetAllVertices(vertices);
        return vertices.size();
    };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        for (auto [from, to, weight] : edges) {
            if (from == vertex) {
                vertices.push_back(to);
            }
        }
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        for (auto [from, to, weight] : edges) {
            if (to == vertex) {
                vertices.push_back(from);
            }
        }
    };

    void GetAllVertices(std::vector<int>& vertices) const override {
        std::set<int> verticesSet;
        for (auto [from, to, weight] : edges) {
            verticesSet.insert(from);
            verticesSet.insert(to);
        }
        for (int vertex : verticesSet) {
            vertices.push_back(vertex);
        }
    }

    T GetWeight(int from, int to) const override {
        for (auto [curFrom, curTo, weight] : edges) {
            if (from == curFrom && to == curTo) {
                return weight;
            }
        }
        assert(false);
    }

private:
    struct Edge {
        int from, to;
        T weight;

        Edge(int from, int to, T weight) : from(from), to(to), weight(weight) {}
    };

    std::vector<Edge> edges;
};

#endif //HOMEWORK_1_ARCGRAPH_H
