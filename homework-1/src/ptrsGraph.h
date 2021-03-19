
#ifndef HOMEWORK_1_PTRSGRAPH_H
#define HOMEWORK_1_PTRSGRAPH_H

#include <stack>
#include <queue>
#include "node.h"
#include "../graph.h"

template<typename T = void>
class PtrsGraph : public IPtrsGraph<T> {

public:

    void GetNextVertices(Node<T>* vertex, std::vector<Node<T>*>& vertices) const override {

        for (auto t : vertex->next)
        {
            vertices.emplace_back(t.first);
        }
    }

    void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) override {

        vertices += from->IsEmpty();
        vertices += to->IsEmpty();

        from->next.emplace_back(to, _obj);
        to->prev.emplace_back(to, _obj);
    }

    PtrsGraph() : nodes(std::set< Node<T>* >())  {}

    int VerticesCount() const override { return vertices; };

    

    void GetPrevVertices(Node<T>* vertex, std::vector<Node<T>*>& vertices) const override  {

        for (Node<T>* t : vertex->prev)
        {
            vertices.emplace_back(t);
        }
    }

    void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const override {

        std::stack<Node<T>*> stack;
        std::set<Node<T>*> used;
        used.insert(vertex);
        vertices.push_back(vertex);
        stack.push(vertex);

        while (stack.size())
        {
            Node<T>* current = stack.top();
            stack.pop();

            for (std::pair<Node<T>*,T> t : current->next)
            {
                if (used.insert(t.first).second) {
                    vertices.emplace_back(t.first);
                    stack.push(t.first);
                }
            }
        }
    }

    void BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const override {
    
        std::queue<Node<T>*> queue;
        std::set<Node<T>*> used;
        used.insert(vertex);
        vertices.push_back(vertex);

        queue.push(vertex);

        while (queue.size())
        {
            Node<T>* current = queue.front();
            queue.pop();

            for (std::pair<Node<T>*, T> t : current->next)
            {
                if (used.insert(t.first).second) {
                    vertices.emplace_back(t.first);
                    queue.push(t.first);
                }
            }
        }
    }


private: 
    int vertices;
};

#endif //HOMEWORK_1_PTRSGRAPH_H
