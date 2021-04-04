//
// Created by dikson on 02.03.2021.
//

#ifndef HOMEWORK_1_PTRSGRAPH_H
#define HOMEWORK_1_PTRSGRAPH_H

#include "node.h"
#include "../graph.h"
#include <set>
#include <vector>
#include <cmath>

template<typename T = void>
class PtrsGraph : public IPtrsGraph<T> {
private:
    int counter_vertices = 0;
public:
    virtual void AddEdge(Node<T>* from, Node<T>* to, T&& _obj) const;

    PtrsGraph();

    ~PtrsGraph();

    virtual int VerticesCount() const;

    virtual void GetNextVertices(Node<T>* vertex, std::vector<Node<T>*>& vertices) const;

    virtual void GetPrevVertices(Node<T>* vertex, std::vector<Node<T>*>& vertices) const;

    virtual void DeepFirstSearch(Node<T>* vertex, std::vector<Node<T>*>& vertices) const;

    virtual void BreadthFirstSearch(Node<T>* vertex, std::vector<Node<T>*>& vertices) const;


};

template<typename T>
void PtrsGraph<T>::AddEdge(Node<T>* from, Node<T>* to, T&& _obj) const {
    const_cast<int&>(counter_vertices) = std::max(counter_vertices, std :: max(from->vertex_id, to->vertex_id));
    from->next[from->next_size] = to;
    from->value_next[from->next_size] = _obj;
    from->next_size++;
    to->before[to->before_size] = from;
    to->value_before[to->before_size] = _obj;
    to->before_size++;
};

template<typename T>
PtrsGraph<T>::PtrsGraph() {
    counter_vertices = 0;
};

template<typename T>
PtrsGraph<T>::~PtrsGraph() {
    
};


template<typename T>
int PtrsGraph<T>::VerticesCount() const {
    return counter_vertices;
};

template<typename T>
void PtrsGraph<T>::GetNextVertices(Node<T>* vertex, std::vector<Node<T>*>& vertices) const {
    for (int i = 0; i < vertex->next_size; i++) {
        vertices.push_back(vertex->next[i]);
    }
};

template<typename T>
void PtrsGraph<T>::GetPrevVertices(Node<T>* vertex, std::vector<Node<T>*>& vertices) const {
    for (int i = 0; i < vertex->before_size; i++) {
        vertices.push_back(vertex->before[i]);
    }
}

template<typename T>
void PtrsGraph<T>::DeepFirstSearch(Node<T>* vertex, std::vector<Node<T>*>& vertices) const {
    vertices.push_back(vertex);
    for (int i = 0; i < vertex->next_size; i++) {
        bool used_vertex = false;
        for (int j = 0; j < vertices.size(); j++) {
            if (vertices[j] == vertex->next[i]) {
                used_vertex = true;
            }
        }
        if (!used_vertex) {
            DeepFirstSearch(vertex->next[i], vertices);
        }
    }
    return;
}

template<typename T>
void PtrsGraph<T>::BreadthFirstSearch(Node<T>* vertex, std::vector<Node<T>*>& vertices) const {
    std::queue<Node<T>*> q;
    vertices.push_back(vertex);
    q.push(vertex);
    while (q.size() != 0) {
        Node<T>* t = q.front();
        q.pop();
        for (int i = 0; i < t->next_size; i++) {
            bool used_vertex = false;
            for (int j = 0; j < vertices.size(); j++) {
                if (vertices[j] == t->next[i]) {
                    used_vertex = true;
                }
            }
            if (!used_vertex) {
                q.push(t->next[i]);
                vertices.push_back(t->next[i]);
            }
        }
    }
}


#endif //HOMEWORK_1_PTRSGRAPH_H
