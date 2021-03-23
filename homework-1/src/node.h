#include "../graph.h"

#ifndef HOMEWORK_1_NODE_H
#define HOMEWORK_1_NODE_H

template<typename T>
class Node {

public:
    void Mark() {
        m_used = true;
    }

    void Unmark() {
        m_used = false;
    }

    bool Marked() const {
        return m_used;
    }

    bool Added() const {
        return m_added;
    }

    void AddVertex() {
        m_added = true;
    }

    bool CheckEdgeTo(Node<T> *vertex) const {
        for (const std::pair<Node<T>*, T> &node : next)
            if (node.first == vertex)
                return true;
        return false;  
    }

    void AddNextVertex(Node<T> *vertex, T&& element) {
        next.emplace_back(vertex, element);
    }

    void AddPrevVertex(Node<T> *vertex, T&& element) {
        prev.emplace_back(vertex, element);
    }

    void GetNextVertices(std::vector<Node<T> *> &vertices) const {
        for (const std::pair<Node<T>*, T> &node : next)
            vertices.push_back(node.first);
    }

    void GetPrevVertices(std::vector<Node<T> *> &vertices) const {
        for (const std::pair<Node<T>*, T> &node : prev)
            vertices.push_back(node.first);
    }    

    bool operator==(const Node<T> &other) const {
        return (this == &other);
    }

private:

    bool m_used, m_added;

    std::vector<std::pair<Node<T>*, T>> next, prev; 
};

#endif //HOMEWORK_1_NODE_H
