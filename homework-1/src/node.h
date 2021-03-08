
#ifndef HOMEWORK_1_NODE_H
#define HOMEWORK_1_NODE_H
#include <vector>
#include <utility>

template<typename T>
class Node {
    std::vector<std::pair<Node<T>*, T>> incoming;
    std::vector<std::pair<Node<T>*, T>> outgoing;
};

#endif //HOMEWORK_1_NODE_H
