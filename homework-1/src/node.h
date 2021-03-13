//
// Created by dikson on 02.03.2021.
//

#ifndef HOMEWORK_1_NODE_H
#define HOMEWORK_1_NODE_H

template<typename T>
class Node {
private:
    const static int max_size = 100;
    T null_type = -1;
public:
    Node *next[max_size];
    Node *before[max_size];
    int next_size = 0;
    int before_size = 0;
    T value_next[max_size];
    T value_before[max_size];
    static int counter_vertex; // счетчик вершин
    int vertex_id;
    Node();

    Node(const Node<T>* vertex);

    Node<T> & operator=(const Node<T>* vertex);

    bool operator == (const Node<T> *vertex);
};
template<class T>
int Node<T>:: counter_vertex = 0;

template<typename T>
Node<T>::Node() {
    vertex_id = counter_vertex;
    counter_vertex++;
    for(int i = 0; i < max_size; i++) {
        next[i] = nullptr;
        before[i] = nullptr;
        value_before[i] = null_type;
        value_next[i] = null_type;
    }
}

template<typename T>
Node<T>::Node(const Node<T>* vertex) {
    vertex_id = counter_vertex;
    counter_vertex++;
    for(int i = 0; i < max_size; i++) {
        next[i] = nullptr;
        before[i] = nullptr;
        value_before[i] = null_type;
        value_next[i] = null_type;
    }

    next_size = vertex->next_size;
    before_size = vertex->before_size;
    for(int i = 0; i < next_size; i++) {
        next[i] = vertex->next[i];
        value_next[i] = vertex->value_next[i];
    }
    for(int i = 0; i < before_size; i++) {
        before[i] = vertex->before[i];
        value_next[i] = vertex->value_next[i];
    }
}

template<typename T>
Node<T> & Node<T>::operator=(const Node<T>* vertex) {
    next_size = vertex->next_size;
    before_size = vertex->before_size;
    for(int i = 0; i < next_size; i++) {
        next[i] = vertex->next[i];
        value_next[i] = vertex->value_next[i];
    }
    for(int i = 0; i < before_size; i++) {
        before[i] = vertex->before[i];
        value_next[i] = vertex->value_next[i];
    }
}

template<typename T>
bool Node<T>::operator == (const Node<T> *vertex) {
    if(vertex_id == vertex->vertex_id) {
        return true;
    }
    return false;
}

template<typename T>
bool operator == (const Node<T> vertex_1, const Node<T> vertex_2) {
    if(vertex_1.vertex_id == vertex_2.vertex_id) {
        return true;
    }
    return false;
}


#endif //HOMEWORK_1_NODE_H
