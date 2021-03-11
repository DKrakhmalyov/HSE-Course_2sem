
#ifndef HOMEWORK_1_NODE_H
#define HOMEWORK_1_NODE_H

template<typename T>
class Node {
public:

    Node() {};

    std::vector<Node*> next;
    std::vector<T> weights;

    void addEdge(Node* other, T&& _obj) {
        next.emplace_back(other);
        weights.emplace_back(_obj);
    }
};

#endif //HOMEWORK_1_NODE_H
