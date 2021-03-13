
#ifndef HOMEWORK_1_NODE_H
#define HOMEWORK_1_NODE_H

#include <vector>

template<typename T>
class Node {
public:
    Node() {}
    std::vector<Node<T>*> next;
    std::vector<int> weights;
};

#endif //HOMEWORK_1_NODE_H
