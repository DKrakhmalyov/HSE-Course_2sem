#ifndef HOMEWORK_1_PTRSGRAPH_H
#define HOMEWORK_1_PTRSGRAPH_H

#include <iostream>
#include <unordered_set>
#include <vector>
#include<algorithm>

#include "node.h"
#include "../graph.h"

/*
Тут достаточно важно сказать, что все ноды мы получаем из вне,
следовательно не можем отвечать за их удаление.
Вот почему я не реализовывал деструкторы (и всё правило 5ти) ни для нод ни для этого графа 
*/


template<typename T = void>
class PtrsGraph : public IPtrsGraph<T> {
    std::vector<Node<T>*> vertices; 
public:
    PtrsGraph() {};

    void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) override {
        from->addNext(to, _obj);
        to->addPrev(from, _obj);

        bool add_from = true;
        bool add_to = from != to;

        for (int i = 0; i < vertices.size(); ++i) {
            if (vertices[i] == from) {
                add_from = false;
            }
            if (vertices[i] == to) {
                add_to = false;
            }
        }
        if (add_from) {
            vertices.push_back(from);
        }
        if(add_to) {
            vertices.push_back(to);
        }
    };

    int VerticesCount() const override { return vertices.size(); };

    void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const override {
        vertices = vertex->getNext();
    };

    void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const override {
        vertex->getPrev(vertices);
    };

    void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const override {
        std::vector<std::pair<Node<T>*, int>> first;

        std::vector<Node<T>*> stack;
        stack.push_back(vertex);
        vertices.push_back(vertex);

        while (!stack.empty()) {
            Node<T> *v = stack.back();

            int ind_v = -1; 
            for (int i = 0; i < first.size(); ++i) {
                if (first[i].first == v) {
                    ind_v = i;
                    break;
                }
            }
            if (ind_v == -1) {
                ind_v = first.size();
                first.push_back(std::make_pair(v, 0));   
            } 
            if (first[ind_v].second < v->getNextSize()) {
                Node<T> *u = v->at(first[ind_v].second++);

                int ind_u = -1;
                for (int i = 0; i < first.size(); ++i) {
                    if (first[i].first == u) {
                        ind_u = i;
                        break;
                    }
                }

                if (ind_u == -1) {
                    stack.push_back(u);
                    vertices.push_back(u);
                }
            } else {
                stack.pop_back();
            }
        }
    };

    void BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const override {
        std::vector<Node<T>*> used;

        std::queue<Node<T>*> vertices_queue;
        vertices_queue.push(vertex);
        vertices.push_back(vertex);

        while (!vertices_queue.empty()) {
            Node<T> *v = vertices_queue.front();
            vertices_queue.pop();

            used.push_back(v);

            auto next_v = v->getNext();
            for (auto u : next_v) {
                if (std::find(used.begin(), used.end(), u) == used.end()) {
                    vertices_queue.push(u);
                    vertices.push_back(u);
                }
            } 
        }

    };

};

#endif //HOMEWORK_1_PTRSGRAPH_H
