
#ifndef HOMEWORK_1_NODE_H
#define HOMEWORK_1_NODE_H

#include <vector>

template<typename T>
class Node {
private:
  T m_data;
  std::vector<std::pair<Node<T> *, T>> m_children;
  std::vector<Node<T> *> m_parents;
  bool m_used;

public:
  Node() {}

  explicit Node(T data) : m_data(data) {}

  bool operator<(const Node &rhs) const {
    return m_data < rhs.m_data;
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
    return m_data == rhs.m_data;
  }

  bool operator!=(const Node &rhs) const {
    return !(rhs == *this);
  }

  void AddChild(Node *rhs, T weight) {
    rhs->m_parents.push_back(this);
    m_children.push_back({rhs, weight});
  }

  std::vector<Node<T> *> GetChildren() {
    auto result = std::vector<Node<T> *>();
    for (auto pair: m_children) {
      result.push_back(pair.first);
    }
    return result;
  }

  std::vector<Node<T> *> GetParents() {
    return m_parents;
  }

  void SetUsed(bool used) {
    m_used = used;
  }

  bool IsUsed() {
    return m_used;
  }
};

#endif //HOMEWORK_1_NODE_H
