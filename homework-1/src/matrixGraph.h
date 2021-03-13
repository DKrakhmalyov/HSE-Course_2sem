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
    int now_size = 0;
    T null_type;
    const static int size_graph = 1000; // max size of graph
    int real_vertices[size_graph]; // real names of vertices
    T matrix_graph[size_graph][size_graph];
public:
    virtual void AddEdge(int from, int to, T &&element) {
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
            real_vertices[now_size] = from;
            ph_from = now_size;
            now_size++;
        }
        if(ph_to == -1) {
            real_vertices[now_size] = to;
            ph_to = now_size;
            now_size++;
        }
        matrix_graph[ph_from][ph_to] = element;
    }

    MatrixGraph() {
        null_type = -1;
        now_size = 0;
        for(int i = 0; i < size_graph; i++) {
            real_vertices[i] = -1;
            for(int j = 0; j < size_graph; j++) {
                matrix_graph[i][j] = null_type;
            }
        }
    }

    MatrixGraph(IGraph<T> *_oth) {
        _oth->Convert(this);
    };

    ~MatrixGraph() {
        delete arcGr;
    }

    virtual int VerticesCount() const { arcGr->VerticesCount(); };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        for(int i = 0; i < now_size; i++) {
            if(real_vertices[i] == vertex) {
                for(int j = 0; j < now_size; j++) {
                    if(matrix_graph[i][j] != null_type) {
                        vertices.push_back(real_vertices[j]);
                    }
                }
                break;
            }
        }
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        for(int i = 0; i < now_size; i++) {
            if(real_vertices[i] == vertex) {
                for(int j = 0; j < now_size; j++) {
                    if(matrix_graph[j][i] != null_type) {
                        vertices.push_back(real_vertices[j]);
                    }
                }
                break;
            }
        }
    }

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
        arcGr->DeepFirstSearch(vertex, vertices);
    };

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
        arcGr->BreadthFirstSearch(vertex, vertices);
    };

    virtual void Convert(IGraph<T> *Gr) {
        arcGr->Convert(Gr);
    };
};

#endif //HOMEWORK_1_MATRIXGRAPH_H
