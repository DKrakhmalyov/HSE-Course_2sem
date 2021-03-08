
#ifndef HOMEWORK_1_NODE_H
#define HOMEWORK_1_NODE_H

template <typename T>
class Node
{
public:
    void addEgde(Node<T> *node, T &&weight)
    {
        edges.push_back(node);
        weights.push_back(std::forward<T>(weight));
    }

    const std::vector<Node<T> *> &getEdges() const
    {
        return edges;
    }

private:
    std::vector<Node<T> *> edges;
    std::vector<T> weights;
};

#endif //HOMEWORK_1_NODE_H
