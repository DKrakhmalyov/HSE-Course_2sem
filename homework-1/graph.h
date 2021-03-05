
#ifndef HOMEWORK_1_GRAPH_H
#define HOMEWORK_1_GRAPH_H

#include <memory>
#include <queue>
#include <set>
#include <tuple>
#include <vector>

#include "src/graph_builder.hpp"
#include "src/node.h"

template <typename T>
class IGraph {
 public:
  using EdgeCostType = T;

  virtual ~IGraph() {}

  IGraph(){};

  IGraph(IGraph *_oth){};

  virtual void AddEdge(int from, int to, T &&_obj) = 0;

  virtual int VerticesCount() const = 0;

  virtual void GetNextVertices(int vertex,
                               std::vector<int> &vertices) const = 0;

  virtual void GetPrevVertices(int vertex,
                               std::vector<int> &vertices) const = 0;

  virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
    vertices.clear();
    std::set<int> used;
    DeepFirstSearchImpl(vertex, vertices, used);
  }

  virtual void BreadthFirstSearch(int vertex,
                                  std::vector<int> &vertices) const {
    vertices.clear();
    BreadthFirstSearchImpl(vertex, vertices);
  }

  virtual void BuildCopy(IGraphBuilder<T> &builder) = 0;

 private:
  void BreadthFirstSearchImpl(int vertex, std::vector<int> &vertices) const {
    std::set<int> used;
    std::queue<int> q;
    q.push(vertex);

    while (!q.empty()) {
      vertex = q.front();
      q.pop();
      vertices.push_back(vertex);
      used.insert(vertex);

      std::vector<int> next_vertices;
      GetNextVertices(vertex, next_vertices);
      for (int to : next_vertices) {
        if (used.find(to) == used.end()) {
          used.insert(to);
          q.push(to);
        }
      }
    }
  }

  void DeepFirstSearchImpl(int vertex, std::vector<int> &vertices,
                           std::set<int> &used) const {
    used.insert(vertex);

    std::vector<int> next_vertices;
    GetNextVertices(vertex, next_vertices);
    for (int to : next_vertices) {
      if (used.find(to) == used.end()) {
        DeepFirstSearchImpl(to, vertices, used);
      }
    }
    vertices.push_back(vertex);
  }
};

template <typename T = void>
class IPtrsGraph {
 public:
  IPtrsGraph() = default;

  virtual ~IPtrsGraph() = default;

  virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) = 0;

  virtual int VerticesCount() const = 0;

  virtual void GetNextVertices(Node<T> *vertex,
                               std::vector<Node<T> *> &vertices) const = 0;

  virtual void GetPrevVertices(Node<T> *vertex,
                               std::vector<Node<T> *> &vertices) const = 0;

  virtual void DeepFirstSearch(Node<T> *vertex,
                               std::vector<Node<T> *> &vertices) const = 0;

  virtual void BreadthFirstSearch(Node<T> *vertex,
                                  std::vector<Node<T> *> &vertices) const = 0;
};

#endif  // HOMEWORK_1_GRAPH_H
