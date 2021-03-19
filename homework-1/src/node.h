
#ifndef HOMEWORK_1_NODE_H
#define HOMEWORK_1_NODE_H

#include <unordered_map>

template<typename T>
class Node {
    std::unordered_map<Node*, T> data_;
    std::unordered_set<Node*> prev_data_;
public:
    bool Empty() {
        return data_.empty() && prev_data_.empty();
    }

    void AddNode(Node* node, T&& weight) {
        data_[node] = std::forward<T>(weight);
    }

    void AddPrevNode(Node* node) {
        prev_data_.insert(node);
    }

    void GetNextNodes(std::vector<Node*> & nodes) {
        for (auto const & [v, _] : data_)
            nodes.push_back(v);
    }

    void GetPrevNodes(std::vector<Node*> & nodes) {
        nodes.assign(prev_data_.begin(), prev_data_.end());
    }

    bool operator==(const Node &rhs) const {
        return data_ == rhs.data_ &&
               prev_data_ == rhs.prev_data_;
    }

    bool operator!=(const Node &rhs) const {
        return !(rhs == *this);
    }
};

#endif //HOMEWORK_1_NODE_H
