
#ifndef HOMEWORK_1_LISTGRAPH_H
#define HOMEWORK_1_LISTGRAPH_H

#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <deque>
#include <cassert>
#include "../graph.h"
#include "graphTraveler.h"
#include "graphConverter.h"

template<typename T>
class ListGraph : public IGraph<T> {
public:
    virtual void AddEdge(int from, int to, T&& element) {
        edgesByVertex[from].push_back(Edge(to, element));
        reversedEdgesByVertex[to].push_back(Edge(from, element));
    };

    ListGraph() = default;

    explicit ListGraph(IGraph<T> *_oth) {
        GraphConverter<T, ListGraph>().convertTo(_oth, this);
    };

    virtual int VerticesCount() const { return (int) edgesByVertex.size(); };

    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const {
        if (edgesByVertex.contains(vertex)) {
            const std::vector<Edge>& edges = edgesByVertex.at(vertex);
            for (const Edge& e:edges) {
                vertices.push_back(e.to);
            }
        }
    };

    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const {
        if (reversedEdgesByVertex.contains(vertex)) {
            const std::vector<Edge>& edges = reversedEdgesByVertex.at(vertex);
            for (const Edge& e:edges) {
                vertices.push_back(e.to);
            }
        }
    };

    void GetAllVertices(std::vector<int>& vertices) const override {
        for (auto &[vertex, edges] : edgesByVertex) {
            vertices.push_back(vertex);
        }
    }

    T GetWeight(int from, int to) const override {
        for (auto [curTo, weight] : edgesByVertex.at(from)) {
            if (curTo == to) {
                return weight;
            }
        }
        assert(false);
    }

private:
    struct Edge {
        int to;
        T weight;

        Edge(int to, T weight) : to(to), weight(weight) {}
    };

    std::unordered_map<int, std::vector<Edge>> edgesByVertex;
    std::unordered_map<int, std::vector<Edge>> reversedEdgesByVertex;
};

#endif //HOMEWORK_1_LISTGRAPH_H
