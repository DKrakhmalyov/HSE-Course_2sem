#ifndef HOMEWORK_1_NODE_H
#define HOMEWORK_1_NODE_H

#include <iostream>
#include <vector>

template<typename T>
class Node {
    std::vector<std::pair<Node<T>*, T>> next_nodes; 
    std::vector<std::pair<Node<T>*, T>> prev_nodes;
public:
    void addNext(Node<T> *node, T elem) {
        for (int i = 0; i < next_nodes.size(); ++i) {
            if (next_nodes[i].first == node) {
                next_nodes[i].second = elem;
                return;
            }
        }
        next_nodes.push_back(std::make_pair(node, elem));
    }

    void addPrev(Node<T> *node, T elem) {
        for (int i = 0; i < prev_nodes.size(); ++i) {
            if (prev_nodes[i].first == node) {
                prev_nodes[i].second = elem;
                return;
            }
        }
        prev_nodes.push_back(std::make_pair(node, elem));
    }

    std::vector<Node<T>*> getNext() const {
        std::vector<Node<T>*> result;

        for (int i = 0; i < next_nodes.size(); ++i) {
            result.push_back(next_nodes[i].first);
        } 
        return result;
    }

    void getPrev(std::vector<Node<T>*> &result) const {
        for (int i = 0; i < prev_nodes.size(); ++i) {
            result.push_back(prev_nodes[i].first);
        } 
    }

    int getNextSize() const {
        return next_nodes.size();
    }

    Node<T>* at(int ind) {
        return next_nodes[ind].first;
    }

    friend auto operator == (const Node<T>& n1, const Node<T>& n2) {
        return (n1.next_nodes == n2.next_nodes) && (n1.prev_nodes == n2.prev_nodes);
    }
};

#endif //HOMEWORK_1_NODE_H
