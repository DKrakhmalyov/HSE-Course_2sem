//
// Created by dikson on 02.03.2021.
//

#ifndef HOMEWORK_1_LISTGRAPH_H
#define HOMEWORK_1_LISTGRAPH_H

#include "../graph.h"
#include "arcGraph.h"


template<typename T = void>
class ListGraph : public IGraph<T> {
private:
    IGraph<T> * arcGr = new ArcGraph<T>;
    int now_size = 0;
    const static int size_graph = 1000; // max size of graph
    int real_vertices[size_graph]; // real names of vertices
    int counter_vertices[size_graph];
    std :: pair<int, T> list_graph[size_graph][size_graph];
public:
    virtual void AddEdge(int from, int to, T &&element) const;

    ListGraph();

    ListGraph(IGraph<T> *_oth);

    ~ListGraph();

    virtual int VerticesCount() const;

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const;

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const;

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const;

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const;

    virtual void Convert(IGraph<T> *Gr) const;
};


template<typename T>
void ListGraph<T>::AddEdge(int from, int to, T &&element) const {
    arcGr->AddEdge(from, to, std :: forward<T>(element));
    int ph_from = -1;
    int ph_to = -1;
    for(int i = 0; i < now_size; i++) {
        if(real_vertices[i] == from) {
            ph_from = i;
        }
        if(real_vertices[i] == to) {
            ph_to = i;
        }
    }
    if(ph_from == -1) {
        const_cast<int&>(real_vertices[now_size]) = from;
        ph_from = now_size;
        const_cast<int&>(now_size)++;
    }
    if(ph_to == -1) {
        const_cast<int&>(real_vertices[now_size]) = to;
        ph_to = now_size;
        const_cast<int&>(now_size)++;
    }
    const_cast<int&>(list_graph[ph_from][counter_vertices[ph_from]].first) = ph_to;
    const_cast<T&>(list_graph[ph_from][counter_vertices[ph_from]].second) = element;
    const_cast<int&>(counter_vertices[ph_from])++;
};

template<typename T>
ListGraph<T>::ListGraph() {
    for(int i = 0; i < size_graph; i++) {
        counter_vertices[i] = 0;
        real_vertices[i] = -1;
    }
};

template<typename T>
ListGraph<T>::ListGraph(IGraph<T> *_oth) {
    for(int i = 0; i < size_graph; i++) {
        counter_vertices[i] = 0;
        real_vertices[i] = -1;
    }
    _oth->Convert(this);
};

template<typename T>
ListGraph<T>::~ListGraph() {
    delete arcGr;
}

template<typename T>
int ListGraph<T>::VerticesCount() const { return arcGr->VerticesCount(); };

template<typename T>
void ListGraph<T>::GetNextVertices(int vertex, std::vector<int> &vertices) const {
    for(int i = 0; i < now_size; i++) {
        if(real_vertices[i] == vertex) {
            for(int j = 0; j < counter_vertices[i]; j++) {
                vertices.push_back(real_vertices[list_graph[i][j].first]);
            }
            break;
        }
    }
};

template<typename T>
void ListGraph<T>::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
    for(int i = 0; i < now_size; i++) {
        if(real_vertices[i] == vertex) {
            for(int j = 0; j < now_size; j++) {
                for(int k = 0; k < counter_vertices[j]; k++) {
                    if(list_graph[j][k].first == i) {
                        vertices.push_back(real_vertices[j]);
                    }
                }
            }
            break;
        }
    }
};

template<typename T>
void ListGraph<T>::DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
    arcGr->DeepFirstSearch(vertex, vertices);
};

template<typename T>
void ListGraph<T>::BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
    arcGr->BreadthFirstSearch(vertex, vertices);
};

template<typename T>
void ListGraph<T>::Convert(IGraph<T> *Gr) const{
    arcGr->Convert(Gr);
};
#endif //HOMEWORK_1_LISTGRAPH_H