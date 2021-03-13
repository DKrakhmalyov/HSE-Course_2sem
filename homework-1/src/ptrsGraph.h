//
// Created by dikson on 02.03.2021.
//

#ifndef HOMEWORK_1_PTRSGRAPH_H
#define HOMEWORK_1_PTRSGRAPH_H

#include "node.h"
#include "../graph.h"
#include "arcGraph.h"

template<typename T = void>
class PtrsGraph : public IPtrsGraph<T> {
private:
    IGraph<T> *arcGr = new ArcGraph<T>;
    const static int size_graph = 100000; // max size of graph
    int real_vertices[size_graph]; // real names of vertices
public:
    virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) {
        arcGr->AddEdge(from->vertex_id, to->vertex_id, std :: forward<T>(_obj));
        from->next[from->next_size] = to;
        from->value_next[from->next_size] = _obj;
        from->next_size++;
        to->before[to->before_size] = from;
        to->value_before[to->before_size] = _obj;
        to->before_size++;
    };

    PtrsGraph() {
        for(int i = 0; i < size_graph; i++) {
            real_vertices[i] = -1;
        }
    };

    ~PtrsGraph() {
        delete arcGr;
    };

    virtual int VerticesCount() const { arcGr->VerticesCount(); };

    virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        for(int i = 0; i < vertex->next_size; i++) {
            vertices.push_back(vertex->next[i]);
        }
    };

    virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        for(int i = 0; i < vertex->before_size; i++) {
            vertices.push_back(vertex->before[i]);
        }
    }

    virtual void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        vertices.push_back(vertex);
        for(int i = 0; i < vertex->next_size; i++) {
            bool used_vertex = false;
            for(int j = 0; j < vertices.size(); j++) {
                if(vertices[j] == vertex->next[i]) {
                    used_vertex = true;
                }
            }
            if(!used_vertex) {
                DeepFirstSearch(vertex->next[i], vertices);
            }
        }
        return;
    }

    virtual void BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        std :: queue<Node<T> *> q;
        vertices.push_back(vertex);
        q.push(vertex);
        while(q.size() != 0) {
            Node<T> *t = q.front();
            q.pop();
            for(int i = 0; i < t->next_size; i++) {
                bool used_vertex = false;
                for(int j = 0; j < vertices.size(); j++) {
                    if(vertices[j] == t->next[i]) {
                        used_vertex = true;
                    }
                }
                if(!used_vertex) {
                    q.push(t->next[i]);
                    vertices.push_back(t->next[i]);
                }
            }
        }
    }

    virtual void Convert(IGraph<T> *Gr) {
        arcGr->Convert(Gr);
    };

};

#endif //HOMEWORK_1_PTRSGRAPH_H
