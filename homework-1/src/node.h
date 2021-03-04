#include "../graph.h"

#ifndef HOMEWORK_1_NODE_H
#define HOMEWORK_1_NODE_H

template<typename T>
class Node {

public:

    Node();

    void Mark();

    void Unmark();

    bool Marked() const;

    bool CheckEdgeTo(Node<T> *vertex) const;

    void AddNextVertex(Node<T> *vertex, T&& element);

    void GetNextVertices(std::vector<Node<T> *> &vertices) const;

    struct less {
        bool operator() (Node<T> *l, Node<T> *r) const;
    };

private:

    bool used;

    int number;

    static int count;

    std::vector<std::pair<Node<T>*, T>> next; 
};

#endif //HOMEWORK_1_NODE_H
