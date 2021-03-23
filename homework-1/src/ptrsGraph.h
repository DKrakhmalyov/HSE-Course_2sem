
#ifndef HOMEWORK_1_PTRSGRAPH_H
#define HOMEWORK_1_PTRSGRAPH_H

#include "node.h"
#include "../graph.h"
#include <algorithm>
#include <queue>

template<typename T = void>
class PtrsGraph : public IPtrsGraph<T> {

public:
    virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) {
        /*
         * будем проверять, есть ли у вершины соседи - если их нет, то это новая вершина в графе -> vertices_count++
         */
        if(from->next.size() == 0 && from->prev.size() == 0){
            vertices_count++;
        }
        if(from->next.size() == 0 && from->prev.size() == 0){
            vertices_count++;
        }
        from->next.emplace_back(std::pair<Node<T>*, T>(to, std::move(_obj)));
        to->prev.emplace_back(from);
    }

    PtrsGraph(){
        vertices_count = 0;
    };

    virtual int VerticesCount() const { return vertices_count; }

    virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        for(const std::pair<Node<T>*, T>& edge: vertex->next){
            vertices.push_back(edge.first);
        }
    }

    virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        for(Node<T>* i : vertex->prev) {
            vertices.push_back(i);
        }
    }

    virtual void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        __dfs__(vertex, vertices);
        for(Node<T>* i: vertices){
            i->used = false;
        }
    }

    virtual void BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        std::queue<Node<T>*> ord;
        ord.push(vertex);
        vertex->used = true;
        while(!ord.empty()){
            Node<T>* current = ord.front();
            ord.pop();
            vertices.push_back(current);
            for (const std::pair<Node<T>*, T>& i : current->next){
                if(!i.first->used){
                    i.first->used = true;
                    ord.push(i.first);
                }
            }
        }
        for(Node<T>* i : vertices){
            i->used = false;
        }
    }

protected:
    int vertices_count;

    void __dfs__(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        vertex->used = true;
        vertices.push_back(vertex);
        for (const std::pair<Node<T>*, T>& edge : vertex->next){
            if(!edge.first->used){
                DeepFirstSearch(edge.first, vertices);
            }
        }
    }
};

#endif //HOMEWORK_1_PTRSGRAPH_H
