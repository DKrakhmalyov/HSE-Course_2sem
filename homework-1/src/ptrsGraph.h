
#ifndef HOMEWORK_1_PTRSGRAPH_H
#define HOMEWORK_1_PTRSGRAPH_H

#include "node.h"
#include "../graph.h"

template<typename T = void>
class PtrsGraph : public IPtrsGraph<T> {

private:
  std::size_t m_vertices_count{0};

  void ClearNodeMarks(std::vector<Node<T> *> &vertices) const {
    // Unmark nodes to avoid side effects.
    for (auto &vtx: vertices) {
      vtx->SetUsed(false);
    }
  }

  void InnerDeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
    std::stack<Node<T> *> stack;
    stack.push(vertex);

    while (!stack.empty()) {
      auto top = stack.top();
      stack.pop();

      if (!top->IsUsed()) {
        vertices.push_back(top);

        // Mark node to make sure we use it once.
        top->SetUsed(true);
      }

      std::vector<Node<T> *> next;
      GetNextVertices(top, next);

      for (auto adjacent: next) {
        if (!adjacent->IsUsed()) stack.push(adjacent);
      }
    }
  }

  void InnerBreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
    std::queue<Node<T> *> queue;
    queue.push(vertex);

    while (!queue.empty()) {
      auto front = queue.front();

      vertices.push_back(front);
      queue.pop();

      std::vector<Node<T> *> next;
      GetNextVertices(front, next);

      for (auto adjacent: next) {
        if (!adjacent->IsUsed()) {
          queue.push(adjacent);

          // Mark node to make sure we use it once.
          adjacent->SetUsed(true);
        }
      }
    }
  }

public:
  void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) override {
    // If 'from' vertex is new for the graph.
    if (from->GetChildren().size() == 0 && from->GetParents().size() == 0) {
      m_vertices_count++;
    }

    // If 'to' vertex is new for the graph.
    if (to->GetChildren().size() == 0 && to->GetParents().size() == 0) {
      m_vertices_count++;
    }

    from->AddChild(to, _obj);
  };

  PtrsGraph() {};

  [[nodiscard]] int VerticesCount() const override {
    return m_vertices_count;
  };

  void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const override {
    vertices = vertex->GetChildren();
  };

  void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const override {
    vertices = vertex->GetParents();
  };

  void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const override {
    InnerDeepFirstSearch(vertex, vertices);
    ClearNodeMarks(vertices);
  }

  void BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const override {
    InnerBreadthFirstSearch(vertex, vertices);
    ClearNodeMarks(vertices);
  }

};

#endif //HOMEWORK_1_PTRSGRAPH_H
