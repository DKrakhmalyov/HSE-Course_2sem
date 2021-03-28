
#ifndef HOMEWORK_1_PTRSGRAPH_H
#define HOMEWORK_1_PTRSGRAPH_H

#include "node.h"
#include "../graph.h"
#include <vector>
#include <memory>
#include <utility>


template<typename T = void>
class PtrsGraph : public IPtrsGraph<T> {
 public:
  PtrsGraph() = default;
  ~PtrsGraph() override = default;

  virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) {
    from->next_vs.emplace_back(to, std::forward<T>(_obj));
    to->prev_vs.emplace_back(from);
    ++vertices_counter;
  };

  virtual int VerticesCount() const { 
    return vertices_counter; 
  };

  virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const override {
    for (auto node : vertex->next_vs)
      vertices.push_back(node.first);
  };

  virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const override {
    for (auto node : vertex->prev_vs)
      vertices.push_back(node);
  };

 protected:
  size_t vertices_counter;
};

#endif //HOMEWORK_1_PTRSGRAPH_H
