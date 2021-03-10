
#ifndef HOMEWORK_1_NODE_H
#define HOMEWORK_1_NODE_H
#include <vector>
#include <utility>

template<typename T>
class Node {
public:
    std::vector<std::pair<Node<T>*, T>> incoming;
    std::vector<std::pair<Node<T>*, T>> outgoing;

    bool operator== (const Node &rhs) const {
        return incoming == rhs.incoming && outgoing == rhs.outgoing;
    }
};

#endif //HOMEWORK_1_NODE_H
