
#ifndef HOMEWORK_1_PTRSGRAPH_H
#define HOMEWORK_1_PTRSGRAPH_H

#include "node.h"
#include "../graph.h"

template<typename T = void>
class PtrsGraph : public IPtrsGraph<T> {

public:
    virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) {
        from->next.emplace_back(to, _obj);
        to->prev.emplace_back(from, _obj);
    };

    PtrsGraph() = default;

    virtual int VerticesCount() const { return static_cast<int>(nodes.size()); };

    virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        for(std::pair<Node<T>*, T> t : vertex->next){
            vertices.emplace_back(t.first);
        }
    };

    virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        for(std::pair<Node<T>*, T> t : vertex->prev){
            vertices.emplace_back(t.first);
        }
    };

    virtual void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        std::set<Node<T>*> used;
        _dfs(vertex, vertices, used);
    };

    virtual void BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        std::set<Node<T> *> used;
        std::queue<Node<T> *> order;
        order.push(vertex);

        while(!order.empty()){
            vertex = order.front();
            order.pop();
            used.insert(vertex);
            vertices.push_back(vertex);
            for(std::pair<Node<T>*, T> edge : vertex->next){
                if(used.find(edge.first) == used.end()) {
                    order.push(edge.first);
                    used.insert(edge.first);
                }
            }
        }

    };

protected:
    std::set<Node<T>*> nodes;

    void _dfs(Node<T> *vertex, std::vector<Node<T> *> &vertices, std::set<Node<T>*> used) const{
        used.insert(vertex);
        vertices.push_back(vertex);
        for(std::pair<Node<T>*, T> edge : vertex->next){
            if(used.find(edge.first) == used.end()) {
                _dfs(edge.first, vertices, used);
                used.insert(edge.first);
            }
        }
    }
};

#endif //HOMEWORK_1_PTRSGRAPH_H