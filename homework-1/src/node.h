
#ifndef HOMEWORK_1_NODE_H
#define HOMEWORK_1_NODE_H

template<typename T>
struct Node {

    Node() : is_checked(false) {};

    ~Node() = default;

    bool operator==(const Node<T>& rhs) const {
        return this == &rhs;
    }

    bool operator!=(const Node<T>& rhs) const {
        return !operator==(rhs);
    }

    bool is_checked;

    std::list<std::pair<Node<T>*, T>> toList;

    std::list<std::pair<Node<T>*, T>> fromList;
};

#endif //HOMEWORK_1_NODE_H
