
#ifndef HOMEWORK_1_NODE_H
#define HOMEWORK_1_NODE_H

#include <vector>

template<typename T>
class Node {
private:
  T data;
  std::vector<std::pair<Node<T> *, T>> children;
  std::vector<Node<T> *> parents;

public:
  Node() {}

  explicit Node(T data) : data(data) {}

  bool operator<(const Node &rhs) const {
    return data < rhs.data;
  }

  bool operator>(const Node &rhs) const {
    return rhs < *this;
  }

  bool operator<=(const Node &rhs) const {
    return !(rhs < *this);
  }

  bool operator>=(const Node &rhs) const {
    return !(*this < rhs);
  }

  bool operator==(const Node &rhs) const {
    return data == rhs.data;
  }

  bool operator!=(const Node &rhs) const {
    return !(rhs == *this);
  }

  void addChild(Node *rhs, T weight) {
    rhs->parents.push_back(this);
    children.push_back({rhs, weight});
  }

  std::vector<Node<T> *> getChildren() {
    auto result = std::vector<Node<T> *>();
    for (auto pair: children) {
      result.push_back(pair.first);
    }
    return result;
  }

  std::vector<Node<T> *> getParents() {
    return parents;
  }
};

#endif //HOMEWORK_1_NODE_H
