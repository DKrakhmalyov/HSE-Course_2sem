
#ifndef HOMEWORK_1_PTRSGRAPH_H
#define HOMEWORK_1_PTRSGRAPH_H
#include <map>
#include <queue>
#include <vector>

#include "../graph.h"
#include "node.h"

template <typename T = void>
class PtrsGraph : public IPtrsGraph<T> {
 public:
  PtrsGraph() = default;
  ~PtrsGraph() override {}

  void AddEdge(Node<T> *from, Node<T> *to, T &&weight) override {
    from->edges.emplace_back(to, weight);
    to->income_edges.emplace_back(from, weight);
    if (from->edges.empty() && from->income_edges.empty()) {
      m_size++;
    }
    if (to->edges.empty() && from->income_edges.empty()) {
      m_size++;
    }
  }

  int VerticesCount() const override { return m_size; };

  void GetNextVertices(Node<T> *vertex,
                       std::vector<Node<T> *> &vertices) const override {
    vertices.clear();
    for (auto &[node, _] : vertex->edges) {
      vertices.emplace_back(node);
    }
  };

  void GetPrevVertices(Node<T> *vertex,
                       std::vector<Node<T> *> &vertices) const override {
    vertices.clear();
    for (auto &[node, _] : vertex->income_edges) {
      vertices.emplace_back(node);
    }
  };

  void DeepFirstSearch(Node<T> *vertex,
                       std::vector<Node<T> *> &vertices) const override {
    std::set<Node<T> *> used;
    DeepFirstSearchImpl(vertex, vertices, used);
  };

  void BreadthFirstSearch(Node<T> *vertex,
                          std::vector<Node<T> *> &vertices) const override {
    vertices.clear();
    BreadthFirstSearchImpl(vertex, vertices);
  };

 private:
  void DeepFirstSearchImpl(Node<T> *vertex, std::vector<Node<T> *> &vertices,
                           std::set<Node<T> *> &used) const {
    vertices.push_back(vertex);
    used.insert(vertex);
    for (auto &edge : vertex->edges) {
      if (used.find(edge.first) == used.end()) {
        DeepFirstSearchImpl(edge.first, vertices, used);
      }
    }

  }

  void BreadthFirstSearchImpl(Node<T> *vertex,
                              std::vector<Node<T> *> &vertices) const {
    std::set<Node<T> *> used;
    std::queue<Node<T> *> q;

    q.push(vertex);
    while (!q.empty()) {
      vertex = q.front();
      q.pop();
      used.insert(vertex);
      vertices.push_back(vertex);

      for (const auto &edge : vertex->edges) {
        if (used.find(edge.first) == used.end()) {
          q.push(edge.first);
        }
      }
    }
  }

 private:
  size_t m_size = 0;
};

#endif  // HOMEWORK_1_PTRSGRAPH_H
