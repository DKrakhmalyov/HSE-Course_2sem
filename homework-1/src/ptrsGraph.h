
#ifndef HOMEWORK_1_PTRSGRAPH_H
#define HOMEWORK_1_PTRSGRAPH_H

#include "node.h"
#include "../graph.h"

template<typename T = void>
class PtrsGraph : public IPtrsGraph<T> {

private:
  std::set<Node<T> *> nodes;

public:
  void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) override {
    nodes.insert(from);
    nodes.insert(to);
    from->addChild(to, _obj);
  };

  PtrsGraph() {};

  [[nodiscard]] int VerticesCount() const override { return nodes.size(); };

  void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const override {
    vertices = vertex->getChildren();
  };

  void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const override {
    vertices = vertex->getParents();
  };

  void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const override {
    std::set<Node<T> *> visited;

    std::stack<Node<T> *> stack;
    stack.push(vertex);

    while (!stack.empty()) {
      auto top = stack.top();
      stack.pop();

      if (!visited.contains(top)) {
        visited.insert(top);
        vertices.push_back(top);
      }

      std::vector<Node<T> *> next;
      GetNextVertices(top, next);

      for (auto adjacent: next) {
        if (!visited.contains(adjacent)) stack.push(adjacent);
      }
    }

  };

  void BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const override {
    std::set<Node<T> *> visited;

    std::queue<Node<T> *> queue;
    queue.push(vertex);

    while (!queue.empty()) {
      auto front = queue.front();

      vertices.push_back(front);
      queue.pop();

      std::vector<Node<T> *> next;
      GetNextVertices(front, next);

      for (auto adjacent: next) {
        if (!visited.contains(adjacent)) {
          queue.push(adjacent);
          visited.insert(adjacent);
        }
      }

    }
  }
};

#endif //HOMEWORK_1_PTRSGRAPH_H
