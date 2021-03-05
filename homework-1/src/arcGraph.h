
#ifndef HOMEWORK_1_ARCGRAPH_H
#define HOMEWORK_1_ARCGRAPH_H

#include "../graph.h"
#include "graph_builder.hpp"

template <typename T = void>
class ArcGraph : public IGraph<T> {
 public:

  ArcGraph() = default;

  ArcGraph(IGraph<T> *other) {
    ConcreteGraphBuilder<ArcGraph> builder;
    other->BuildCopy(builder);

    auto ptr = builder.Build().release();
    ArcGraph(std::move(*ptr));
    delete ptr;
  }

  ArcGraph(ArcGraph &&other) : m_edges(std::move(other.m_edges)) {}


  void AddEdge(int from, int to, T &&element) override {
      m_edges.emplace_back(from, to, element);
  };

  int VerticesCount() const override {
    std::set<int> vertices;
    for (const auto &edge : m_edges) {
      vertices.insert(std::get<0>(edge));
      vertices.insert(std::get<1>(edge));
    }
    return static_cast<int>(vertices.size());
  };

  void GetNextVertices(int vertex, std::vector<int> &vertices) const override {
    vertices.clear();
    for (auto &edge : m_edges) {
      int from = std::get<0>(edge);
      int to = std::get<1>(edge);
      if (from == vertex) {
        vertices.push_back(to);
      }
    }
  };

  void GetPrevVertices(int vertex, std::vector<int> &vertices) const override {
    vertices.clear();
    for (auto &edge : m_edges) {
      int from = std::get<0>(edge);
      int to = std::get<1>(edge);
      if (to == vertex) {
        vertices.push_back(from);
      }
    }
  };

  void BuildCopy(IGraphBuilder<T> &builder) override {
    builder.Init();
    for (auto &[from, to, cost] : m_edges) {
      builder.AddEdge(from, to, T(cost));
    }
  }

  ~ArcGraph() override = default;

 private:
  std::vector<std::tuple<int, int, T>> m_edges;
};

#endif  // HOMEWORK_1_ARCGRAPH_H
