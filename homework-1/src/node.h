
#ifndef HOMEWORK_1_NODE_H
#define HOMEWORK_1_NODE_H

template <typename T>
class Node
{
public:
    void addEgde(Node<T> *node, T &&weight)
    {
        node->prevVertices.push_back({this, weight});
        nextVertices.push_back({node, std::forward<T>(weight)});
    }

    const std::vector<std::pair<Node<T> *, T>> &getNextVertices() const
    {
        return nextVertices;
    }

    const std::vector<std::pair<Node<T> *, T>> &getPrevVertices() const
    {
        return prevVertices;
    }

    bool empty() const
    {
        return nextVertices.size() == 0 && prevVertices.size() == 0;
    }

private:
    std::vector<std::pair<Node<T> *, T>> nextVertices, prevVertices;
};

#endif //HOMEWORK_1_NODE_H
