#include "ptrsGraph.h"
#include "listGraph.h"

#include <set>

template<typename T>
PtrsGraph<T>::PtrsGraph() = default;

template<typename T>
PtrsGraph<T>::~PtrsGraph() {
    this->clearValue();
}

template<typename T>
void PtrsGraph<T>::addEdge(Node<T> *from, Node<T> *to, const T &obj) {
    T* weight = new T(obj);
    std::pair<Node<T>*, std::pair<Node<T>*, T*>> pair =  std::pair<Node<T>*, std::pair<Node<T>*, T*>>(
        from,
        std::pair<Node<T>*, T*>(to, weight)
    );
    this->edges.push_back(pair);
}

template<typename T>
int PtrsGraph<T>::verticesCount() {
    std::set<Node<T>*> used;
    for (const std::pair<Node<T>*, std::pair<Node<T>*, T*>> edge : this->edges) {
        used.insert(edge.first);
        used.insert(edge.second.first);
    }
    return used.size();
}

template<typename T>
void PtrsGraph<T>::getNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) {
    vertices.clear();
    vertices.shrink_to_fit();
    for (const std::pair<Node<T>*, std::pair<Node<T>*, T*>> edge : this->edges) {
        if (edge.first == vertex) {
            vertices.push_back(edge.second.first);
        }
    }
}

template<typename T>
void PtrsGraph<T>::getPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) {
    vertices.clear();
    vertices.shrink_to_fit();
    for (const std::pair<Node<T>*, std::pair<Node<T>*, T*>> edge : this->edges) {
        if (edge.second.first == vertex) {
            vertices.push_back(edge.first);
        }
    }
}

template<typename T>
void PtrsGraph<T>::deepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) {
    vertices.clear();
    vertices.shrink_to_fit();
    ListGraph<T>* listGraph = this->createListGraph();
    std::vector<int32_t> listVertices;
    listGraph->deepFirstSearch(vertex->getIndex(), listVertices);
    delete listGraph;
    for (int32_t index: listVertices) {
        for (std::pair<Node<T>*, std::pair<Node<T>*, T*>> pair: this->edges) {
            if (pair.first->getIndex() == index) {
                vertices.push_back(pair.first);
                break;
            }
            if (pair.second.first->getIndex() == index) {
                vertices.push_back(pair.second.first);
                break;
            }
        }
    }
}

template<typename T>
void PtrsGraph<T>::breadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) {
    vertices.clear();
    vertices.shrink_to_fit();
    ListGraph<T>* listGraph = this->createListGraph();
    std::vector<int32_t> listVertices;
    listGraph->breadthFirstSearch(vertex->getIndex(), listVertices);
    delete listGraph;
        for (int32_t index: listVertices) {
        for (std::pair<Node<T>*, std::pair<Node<T>*, T*>> pair: this->edges) {
            if (pair.first->getIndex() == index) {
                vertices.push_back(pair.first);
                break;
            }
            if (pair.second.first->getIndex() == index) {
                vertices.push_back(pair.second.first);
                break;
            }
        }
    }
}

template<typename T>
void PtrsGraph<T>::clearValue() {
    std::map<int32_t, Node<T>*> nodes;
    for (const std::pair<Node<T>*, std::pair<Node<T>*, T*>> edge : this->edges) {
        T* weight = edge.second.second;
        delete weight;
    }
}

template<typename T>
ListGraph<T>* PtrsGraph<T>::createListGraph() const noexcept {
    ListGraph<T>* resultGraph = new ListGraph<T>();
    for (const std::pair<Node<T>*, std::pair<Node<T>*, T*>> edge: this->edges) {
        int32_t firstNode = (edge.first)->getIndex();
        int32_t secondNode = (edge.second.first)->getIndex();
        resultGraph->addEdge(firstNode, secondNode, *(edge.second.second));
    }
    return resultGraph;
}