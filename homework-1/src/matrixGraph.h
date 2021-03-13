//
// Created by dikson on 02.03.2021.
//

#ifndef HOMEWORK_1_MATRIXGRAPH_H
#define HOMEWORK_1_MATRIXGRAPH_H


#include "../graph.h"
#include "arcGraph.h"

using namespace std;

template<typename T = void>
class MatrixGraph : public IGraph<T> {
private:
    IGraph<T> * arcGr = new ArcGraph<T>;
    const static int size_graph = 1000; // max size of graph
    int real_vertices[size_graph]; // real names of vertices
    std :: pair<T, bool> matrix_graph[size_graph][size_graph];
public:
    virtual void AddEdge(int from, int to, T &&element) const;

    MatrixGraph();

    MatrixGraph(IGraph<T> *_oth);

    ~MatrixGraph();

    virtual int VerticesCount() const;

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const;

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const;

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const;

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const;

    virtual void Convert(IGraph<T> *Gr) const;
};

template<typename T>
void MatrixGraph<T>::AddEdge(int from, int to, T &&element) const {
    int ph_from = -1;
    int ph_to = -1;
    int now_size = arcGr->VerticesCount();
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
        now_size = now_size + 1;
    }
    if(ph_to == -1) {
        const_cast<int&>(real_vertices[now_size]) = to;
        ph_to = now_size;
        now_size++;
    }
    const_cast<T&>(matrix_graph[ph_from][ph_to].first) = element;
    const_cast<bool&>(matrix_graph[ph_from][ph_to].second) = true;
    arcGr->AddEdge(from, to, std :: forward<T>(element));
}

template<typename T>
MatrixGraph<T>::MatrixGraph() {
    for(int i = 0; i < size_graph; i++) {
        real_vertices[i] = -1;
        for(int j = 0; j < size_graph; j++) {
            matrix_graph[i][j].second = false;
        }
    }
}

template<typename T>
MatrixGraph<T>::MatrixGraph(IGraph<T> *_oth) {
    for(int i = 0; i < size_graph; i++) {
        real_vertices[i] = -1;
        for(int j = 0; j < size_graph; j++) {
            matrix_graph[i][j].second = false;
        }
    }
    _oth->Convert(this);
};

template<typename T>
MatrixGraph<T>::~MatrixGraph() {
    delete arcGr;
}

template<typename T>
int MatrixGraph<T>::VerticesCount() const {
    return arcGr->VerticesCount();
};

template<typename T>
void MatrixGraph<T>::GetNextVertices(int vertex, std::vector<int> &vertices) const {
    int now_size = arcGr->VerticesCount();
    for(int i = 0; i < now_size; i++) {
        if(real_vertices[i] == vertex) {
            for(int j = 0; j < now_size; j++) {
                if(matrix_graph[i][j].second) {
                    vertices.push_back(real_vertices[j]);
                }
            }
            break;
        }
    }
};

template<typename T>
void MatrixGraph<T>::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
    int now_size = arcGr->VerticesCount();
    for(int i = 0; i < now_size; i++) {
        if(real_vertices[i] == vertex) {
            for(int j = 0; j < now_size; j++) {
                if(matrix_graph[j][i].second) {
                    vertices.push_back(real_vertices[j]);
                }
            }
            break;
        }
    }
}

template<typename T>
void MatrixGraph<T>::DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
    arcGr->DeepFirstSearch(vertex, vertices);
};

template<typename T>
void MatrixGraph<T>::BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
    arcGr->BreadthFirstSearch(vertex, vertices);
};

template<typename T>
void MatrixGraph<T>::Convert(IGraph<T> *Gr) const {
    arcGr->Convert(Gr);
};

#endif //HOMEWORK_1_MATRIXGRAPH_H
