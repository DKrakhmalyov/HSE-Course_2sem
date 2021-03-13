#include "../graph.h"

#ifndef HOMEWORK_1_NODE_H
#define HOMEWORK_1_NODE_H

template<typename T>
class Node {

public:

    Node() {
        number = Node<T>::count++;
    }

    void Mark() {
        used = true;
    }

    void Unmark() {
        used = false;
    }

    bool Marked() const {
        return used;
    }

    bool CheckEdgeTo(Node<T> *vertex) const {
        for (const std::pair<Node<T>*, T> &node : next)
            if (node.first == vertex)
                return true;
        return false;  
    }

    void AddNextVertex(Node<T> *vertex, T&& element) {
        if (Node<T>::CheckEdgeTo(vertex))
            return;

        next.emplace_back(vertex, element);
    }

    void GetNextVertices(std::vector<Node<T> *> &vertices) const {
        for (const std::pair<Node<T>*, T> &node : next)
            vertices.push_back(node.first);
    }

    struct less {
        bool operator() (Node<T> *l, Node<T> *r) const {
            return l->number < r->number;
        }
    };

    bool operator==(const Node<T> &other) const {
        return (this == &other);
    }

private:

    bool used;

    int number;

    static int count;

    std::vector<std::pair<Node<T>*, T>> next; 
};

template<typename T>
int Node<T>::count = 0;

#endif //HOMEWORK_1_NODE_H
