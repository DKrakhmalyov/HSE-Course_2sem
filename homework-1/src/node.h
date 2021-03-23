
#ifndef HOMEWORK_1_NODE_H
#define HOMEWORK_1_NODE_H

#include <vector>

template<typename T>
class Node {
public:
    Node() {
        used = false;
        next = std::vector<std::pair<Node<T> *, T>>();
        prev = std::vector<Node<T>*>();
    }

    std::vector<std::pair<Node<T> *, T>> next;
    std::vector<Node<T>*> prev;
    bool used; // переменная, используемая при обходе в глубину - хранит, была ли посещена вершина
};

#endif //HOMEWORK_1_NODE_H
