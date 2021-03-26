
#ifndef HOMEWORK_1_NODE_H
#define HOMEWORK_1_NODE_H

#include <vector>

template<typename T>
class Node {
public:
    Node(){
        next = std::vector<std::pair<Node<T>*, T>>();
    }

    bool operator ==(const Node& right){
        return(next == right.next && prev == right.prev);
    }

    std::vector<std::pair<Node<T>*, T>> next;
    std::vector<std::pair<Node<T>*, T>> prev;

};

#endif //HOMEWORK_1_NODE_H
 