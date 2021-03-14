
#ifndef HOMEWORK_1_PTRSGRAPH_H
#define HOMEWORK_1_PTRSGRAPH_H

#include "node.h"
#include "../graph.h"
#include <vector>
#include <queue>
#include <map>

template<typename T = void>
class PtrsGraph : public IPtrsGraph<T> {

public:
    virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) {
        from->edges.push_back({to, _obj});
        to->redges.push_back({from, _obj});
        if (!private_number[from]) {
            ++vc;
            private_number[from] = vc;
            public_number[vc] = from;
        }
        if (!private_number[to]) {
            ++vc;
            private_number[to] = vc;
            public_number[vc] = to;
        }
    };

    // PtrsGraph() {};

    virtual int VerticesCount() const { return vc; };

    int prnumber (Node<T>* v) {
        return private_number[v];
    }
    
    Node<T>* pubnumber (int v) {
        return public_number[v];
    }

    virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        for(int i = 0; i < vertex->edges.size(); ++i) {
            vertices.push_back(vertex->edges[i].first);
        }
    };

    virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        for(int i = 0; i < vertex->redges.size(); ++i) {
            vertices.push_back(vertex->redges[i].first);
        }
    };

    virtual void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T>*> &vertices) const {
        std::vector <Node<T>* > waiting;
        std::vector <int> visited(vc + 1);
        waiting.push_back(vertex);

        while(!waiting.empty()) {
            Node<T>* cur = waiting.back();
            vertices.push_back(cur);
            visited[prnumber(cur)] = true;
            waiting.pop_back();
            std::vector <int> next;
            GetNextVertices(cur, next);
            for (int i = 0; i < next.size(); ++i) {
                if (visited[prnumber(next[i])]) 
                    continue;
                waiting.push_back(next[i]);
            }
        }
    };

    virtual void BreadthFirstSearch(Node<T>* vertex, std::vector<Node<T>*> &vertices) const {
        std::queue <Node<T>* > waiting;
        std::vector <int> visited(vc + 1);
        waiting.push(vertex);

        while(!waiting.empty()) {
            Node<T>* cur = waiting.front();
            vertices.push_back(cur);
            visited[prnumber(cur)] = true;
            waiting.pop();
            std::vector <int> next;
            GetNextVertices(cur, next);
            for (int i = 0; i < next.size(); ++i) {
                if (visited[prnumber(next[i])])
                    continue;
                waiting.push(next[i]);
            }
        }
    };

private:
    Node<T> graph;
    std::map <Node<T>*, int> private_number;
    std::map <int, Node<T>*> public_number;
    int vc = 0;
};

#endif //HOMEWORK_1_PTRSGRAPH_H
