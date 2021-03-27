
#ifndef HOMEWORK_1_NODE_H
#define HOMEWORK_1_NODE_H

#include <vector>
#include <utility>

template<typename T>
class Node {
 public:
  std::vector<std::pair<Node<T>*, T>> next_vs;
  std::vector<Node<T>*> prev_vs;
};

#endif //HOMEWORK_1_NODE_H
