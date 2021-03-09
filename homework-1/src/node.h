
#ifndef HOMEWORK_1_NODE_H
#define HOMEWORK_1_NODE_H

#include <vector>

template<typename T>
class Node {
    public:
    Node(){
        used = false;
        next = std::vector<std::pair<Node<T>*, T>>();
    }
    std::vector<std::pair<Node<T>*, T>> next;
    bool used;
};

#endif //HOMEWORK_1_NODE_H
