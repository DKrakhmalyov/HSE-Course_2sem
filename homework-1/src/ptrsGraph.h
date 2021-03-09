
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
        if(std::find(graph.begin(), graph.end(), from) == graph.end()){
            graph.push_back(from);
        }
        if(std::find(graph.begin(), graph.end(), to) == graph.end()){
            graph.push_back(to);
        }
        from->next.emplace_back(std::pair<Node<T>*, T>(to, std::move(_obj)));
    }

    PtrsGraph() = default;

    virtual int VerticesCount() const { return graph.size(); }

    virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        for(const std::pair<Node<T>*, T>& edge: vertex->next){
            vertices.push_back(edge.first);
        }
    }

    virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        for(Node<T>* i : graph){
            for(const std::pair<Node<T>*, T>& edge : i->next){
                if (edge.first == vertex){
                    vertices.push_back(i);
                    break;
                }
            }
        }
    }

    virtual void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        __dfs__(vertex, vertices);
        for(Node<T>* i: graph){
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
        for(Node<T>* i : graph){
            i->used = false;
        }
    }
protected:
    void __dfs__(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        vertex->used = true;
        vertices.push_back(vertex);
        for (const std::pair<Node<T>*, T>& edge : vertex->next){
            if(!edge.first->used){
                DeepFirstSearch(edge.first, vertices);
            }
        }
    }
    std::vector<Node<T>*> graph;
};

#endif //HOMEWORK_1_PTRSGRAPH_H
