
#ifndef HOMEWORK_1_NODE_H
#define HOMEWORK_1_NODE_H

template<typename T>
class Node {
public:

    Node() {};

    bool added = 0;
    std::vector<Node*> next;
    std::vector<Node*> prev;
    std::vector<T> next_weights;
    std::vector<T> prev_weights;

    void addEdge(Node* other, T&& _obj) {
        next.emplace_back(other);
        next_weights.emplace_back(std::forward<T>(_obj));
        prev.emplace_back(other);
        prev_weights.emplace_back(std::forward<T>(_obj));
    }
};

#endif //HOMEWORK_1_NODE_H
