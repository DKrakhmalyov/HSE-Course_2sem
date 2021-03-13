
#ifndef HOMEWORK_1_NODE_H
#define HOMEWORK_1_NODE_H

template<typename T>
class Node {
public:
    bool operator==(const Node<T> another) const {
        return another._id == this->_id;
    }

    Node() {
        static int id = 0;
        id++;
        _id = id;
    };

    ~Node() {
        static int id = 0;
        id++;
        _id = id;
    };
    std::vector<Node<T>*>& getVerts() {
        return verts;
    }
    std::map<Node<T>*, T>& getWeights() {
        return weights;
    }
    void addVert(Node<T> *node, T &&obj)
    {
        verts.push_back(node);
        weights[node] = obj;
    }
private:
    T weightOwn;
    std::vector<Node<T>*> verts;
    std::map<Node<T>*, T> weights;
    int _id;
};

#endif //HOMEWORK_1_NODE_H
