
#ifndef HOMEWORK_1_NODE_H
#define HOMEWORK_1_NODE_H

#include <utility>
#include <list>

template <typename T>
struct Node {
  std::list<std::pair<Node<T>*, T>> edges;
  std::list<std::pair<Node<T>*, T>> income_edges;
};

#endif  // HOMEWORK_1_NODE_H
