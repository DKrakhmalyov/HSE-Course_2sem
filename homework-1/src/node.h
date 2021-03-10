
#ifndef HOMEWORK_1_NODE_H
#define HOMEWORK_1_NODE_H

template<typename T>
class Node {
public:

    Node() = delete;

    ~Node() = default;
private:

    std::list<std::pair<Node<T>*, T>> to;

    std::list<std::pair<Node<T>*, T>> from;
};

#endif //HOMEWORK_1_NODE_H
