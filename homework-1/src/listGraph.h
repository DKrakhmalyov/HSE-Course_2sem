#ifndef HOMEWORK_1_LISTGRAPH_H
#define HOMEWORK_1_LISTGRAPH_H

#include <list>
#include <map>
#include <queue>
#include <utility>

#include "../graph.h"
#include "graph_builder.hpp"

template <typename T>
class ListGraph : public IGraph<T> {
 public:
  void AddEdge(int from, int to, T &&element) override {
    m_edges[from].emplace_back(to, element);
    if (m_edges.find(to) == m_edges.end()) {
      m_edges.emplace(to, std::list<std::pair<int, T>>{});
    }
  };

  ListGraph() = default;

  ListGraph(IGraph<T> *other) {
    ConcreteGraphBuilder<ListGraph> builder;
    other->BuildCopy(builder);

    auto ptr = builder.Build().release();
    ListGraph(std::move(*ptr));
    delete ptr;
  }

  ListGraph(ListGraph &&other) : m_edges(std::move(other.m_edges)) {}

  int VerticesCount() const override {
    return static_cast<int>(m_edges.size());
  };

  void GetNextVertices(int vertex, std::vector<int> &vertices) const override {
    vertices.clear();
    auto it = m_edges.find(vertex);
    if (it == m_edges.end()) {
      return;
    }

    vertices.reserve(it->second.size());
    for (const auto &t : it->second) {
      vertices.push_back(t.first);
    }
  };

  void GetPrevVertices(int vertex, std::vector<int> &vertices) const override {
    vertices.clear();
    for (const auto &node : m_edges) {
      for (const auto &edge : node.second) {
        if (edge.first == vertex) {
          vertices.push_back(node.first);
        }
      }
    }
  };

  void BuildCopy(IGraphBuilder<T> &builder) override {
    builder.Init();
    for (auto &[vertex, edges] : m_edges) {
      for (auto &edge : edges) {
        builder.AddEdge(vertex, edge.first, T(edge.second));
      }
    }
  }

  ~ListGraph() override = default;

 private:
  std::map<int, std::list<std::pair<int, T>>> m_edges;
};

#endif  // HOMEWORK_1_LISTGRAPH_H
