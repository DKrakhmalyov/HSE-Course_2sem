#ifndef HOMEWORK_1_NODE_H
#define HOMEWORK_1_NODE_H

#include <vector>
#include <utility>


template<typename T>
struct Node {
    std::vector<std::pair<Node *, T>> nodes;
};

#endif //HOMEWORK_1_NODE_H

