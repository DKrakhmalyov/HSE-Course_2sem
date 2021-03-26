
#ifndef HOMEWORK_1_GRAPH_H
#define HOMEWORK_1_GRAPH_H

#include <vector>
#include <set>
#include <queue>
#include "src/node.h"

template<typename T>
class IGraph {
 public:
  virtual ~IGraph() {}

  IGraph() {};

  IGraph(IGraph *_oth) {};

  virtual void AddEdge(int from, int to, T &&_obj) = 0;

  virtual int VerticesCount() const = 0;

  virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const = 0;

  virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const = 0;

  virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
    std::set<int> visited_vertices;
    recursive_dfs(vertex, vertices, visited_vertices);
  };

  virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
    std::set<int> visited_vertices;
    std::queue<int> visit_queue;

    visit_queue.push(vertex);
    visited_vertices.insert(vertex);

    while (!visit_queue.empty()) {
      int cur_v = visit_queue.front();
      visit_queue.pop();

      vertices.push_back(cur_v);

      std::vector<int> next_vertices;
      GetNextVertices(cur_v, next_vertices);

      for (auto neighbor : next_vertices) {
        if (visited_vertices.find(neighbor) == visited_vertices.end()) {
          visit_queue.push(neighbor);
          visited_vertices.insert(neighbor);
        }
      }
    }
  };

 private:
  void recursive_dfs(int vertex, std::vector<int> &vertices, std::set<int> &visited_vertices) const {
    vertices.push_back(vertex);
    visited_vertices.insert(vertex);

    std::vector<int> next_vertices;
    GetNextVertices(vertex, next_vertices);

    for (auto next_vertex : next_vertices)
      if (visited_vertices.find(next_vertex) == visited_vertices.end())
        recursive_dfs(next_vertex, vertices, visited_vertices);
  }
};

template<typename T = void>
class IPtrsGraph {
 public:
  virtual ~IPtrsGraph() {}

  IPtrsGraph() {};

  virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) = 0;

  virtual int VerticesCount() const = 0;

  virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const = 0;

  virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const = 0;

  virtual void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const = 0;

  virtual void BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const = 0;
};

#endif //HOMEWORK_1_GRAPH_H
