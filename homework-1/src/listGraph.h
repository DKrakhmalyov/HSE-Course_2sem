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
    const static int size_graph = 100000; // max size of graph
    int real_vertices[size_graph]; // real names of vertices
    std :: vector<std :: pair<int, T>> list_graph[size_graph];
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
        list_graph[ph_from].push_back(std :: make_pair(ph_to, element));
    };

    ListGraph() {
        for(int i = 0; i < size_graph; i++) {
            real_vertices[i] = -1;
        }
    };

    ListGraph(IGraph<T> *_oth) {
        _oth->Convert(this);
    };

    ~ListGraph() {
        delete arcGr;
    }

    virtual int VerticesCount() const { return arcGr->VerticesCount(); };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        for(int i = 0; i < now_size; i++) {
            if(real_vertices[i] == vertex) {
                for(int j = 0; j < list_graph[i].size(); j++) {
                    vertices.push_back(real_vertices[list_graph[i][j].first]);
                }
                break;
            }
        }
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        for(int i = 0; i < now_size; i++) {
            if(real_vertices[i] == vertex) {
                for(int j = 0; j < now_size; j++) {
                    for(int k = 0; k < list_graph[j].size(); k++) {
                        if(list_graph[j][k].first == i) {
                            vertices.push_back(real_vertices[j]);
                        }
                    }
                }
                break;
            }
        }
    };

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


#endif //HOMEWORK_1_LISTGRAPH_H
