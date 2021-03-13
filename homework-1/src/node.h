
#ifndef HOMEWORK_1_NODE_H
#define HOMEWORK_1_NODE_H

#include <vector>

template<typename T>
class Node {
public:
    std::vector < std::pair <Node<T>*, T> >  edges, redges;
};

#endif //HOMEWORK_1_NODE_H
