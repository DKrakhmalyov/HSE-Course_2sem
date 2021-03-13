
#ifndef HOMEWORK_1_GRAPH_H
#define HOMEWORK_1_GRAPH_H

#include <vector>
#include <queue>
#include <stack>
#include "src/node.h"

template<typename T>
class IGraph {
public:
  virtual ~IGraph() {}

  IGraph() {};

  explicit IGraph(IGraph *oth) {};

  virtual void AddEdge(int from, int to, T &&_obj) = 0;

  virtual const T *GetWeight(int from, int to) const = 0;

  [[nodiscard]] virtual int VerticesCount() const = 0;

  virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const = 0;

  virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const = 0;

  void DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
    std::vector<bool> visited(VerticesCount());

    std::stack<int> stack;
    stack.push(vertex);

    while (!stack.empty()) {
      auto top = stack.top();
      stack.pop();

      if (!visited[top]) {
        visited[top] = true;
        vertices.push_back(top);
      }

      std::vector<int> next;
      GetNextVertices(top, next);

      for (auto adjacent: next) {
        if (!visited[adjacent]) stack.push(adjacent);
      }
    }
  }

  void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
    std::vector<bool> visited(VerticesCount());

    std::queue<int> queue;
    queue.push(vertex);

    while (!queue.empty()) {
      auto front = queue.front();

      vertices.push_back(front);
      queue.pop();

      std::vector<int> next;
      GetNextVertices(front, next);

      for (auto adjacent: next) {
        if (!visited[adjacent]) {
          queue.push(adjacent);
          visited[adjacent] = true;
        }
      }

    }
  }
};

template<typename T = void>
class IPtrsGraph {
public:
  virtual ~IPtrsGraph() {}

  IPtrsGraph() {};

  virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) = 0;

  [[nodiscard]] virtual int VerticesCount() const = 0;

  virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const = 0;

  virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const = 0;

  virtual void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const = 0;

  virtual void BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const = 0;
};

#endif //HOMEWORK_1_GRAPH_H
