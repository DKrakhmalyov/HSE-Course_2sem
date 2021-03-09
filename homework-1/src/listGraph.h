
#ifndef HOMEWORK_1_LISTGRAPH_H
#define HOMEWORK_1_LISTGRAPH_H

#include "../graph.h"
#include <queue>

template<typename T>
class ListGraph : public IGraph<T> {
public:
    virtual void AddEdge(int from, int to, T &&element) {
        if(graph.size() < std::max(from, to) + 1){
            graph.resize(std::max(from, to) + 1);
        }
        graph[from].emplace_back(std::pair<int, T&&>(to, std::move(element)));
    }

    ListGraph() = default;

    ListGraph(IGraph<T> *_oth) {
        graph = std::vector<std::list<std::pair<int, T>>>();
        for (int i = 0; i < _oth->VerticesCount(); i++){
            graph.emplace_back(std::move(_oth->__get__next__(i)));
        }
    }

    virtual int VerticesCount() const { return graph.size(); }

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        for (const std::pair<int, T> &i: graph[vertex]){
            vertices.push_back(i.first);
        }
    }

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        for(int i = 0; i < graph.size(); i++){
            for (const std::pair<int, T> &j: graph[i]){
                if (j.first == vertex){
                    vertices.push_back(i);
                    break;
                }
            }
        }
    }

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
        __dfs__(vertex, vertices, std::vector<bool>(VerticesCount(), 0));
    }

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
        std::queue<int> ord;
        std::vector<bool> used(VerticesCount(), 0);
        ord.push(vertex);
        used[vertex] = true;
        while(!ord.empty()){
            int current = ord.front();
            ord.pop();
            vertices.push_back(current);
            std::vector<int> temp;
            GetNextVertices(current, temp);
            for (int i : temp){
                if(!used[i]){
                    used[i] = true;
                    ord.push(i);
                }
            }
        }
    }

    virtual std::list<std::pair<int, T>> __get__next__(int vertex) const {
        return graph[vertex];
    }

protected:
    std::vector<std::list<std::pair<int, T>>> graph;
    
    virtual void __dfs__(int vertex, std::vector<int> &vertices, std::vector<bool> &used) const {
        used[vertex] = 1;
        vertices.push_back(vertex);
        std::vector<int> temp;
        GetNextVertices(vertex, temp);
        for (int i : temp){
            if(!used[i]){
                __dfs__(i, vertices, used);
            }
        }
    }
};


#endif //HOMEWORK_1_LISTGRAPH_H
