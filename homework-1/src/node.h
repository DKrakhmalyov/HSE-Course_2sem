
#ifndef HOMEWORK_1_NODE_H
#define HOMEWORK_1_NODE_H

#include <vector>
#include <tuple>

template<typename T>
class Node {
public:
    struct Edge {
        Node<T>* to;
        T weight;

        Edge(Node<T> *to, T weight) : to(to), weight(weight) {}

        bool operator==(const Edge& rhs) const {
            return std::tie(to, weight) == std::tie(rhs.to, rhs.weight);
        }

        bool operator!=(const Edge& rhs) const {
            return rhs != *this;
        }
    };

    std::vector<Edge> nextVertexes;
    std::vector<Edge> prevVertexes;

    bool operator==(const Node<T>& rhs) const {
        return nextVertexes == rhs.nextVertexes;
    }

    bool operator!=(const Node<T>& rhs) const {
        return rhs != *this;
    }
};

#endif //HOMEWORK_1_NODE_H
