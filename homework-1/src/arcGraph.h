
#ifndef HOMEWORK_1_ARCGRAPH_H
#define HOMEWORK_1_ARCGRAPH_H

#include "../graph.h"

template<typename T = void>
class ArcGraph : public IGraph<T> {
public:
    virtual void AddEdge(int from, int to, T &&element) {
        graph.emplace_back(std::pair<std::pair<int, int>, T>(std::pair<int, int>(from, to), std::move(element)));
    }

    ArcGraph() = default;

    ArcGraph(IGraph<T> *_oth) {
        int count = _oth->VerticesCount();
        for(int i = 0; i < count; i++){
            for (std::pair<int, T>& edge : this->__call__get__next__(_oth, i)){
                graph.emplace_back(std::pair<std::pair<int, int>, T>(std::pair<int, int>(i, edge.first),
                        std::move(edge.second)));
            }
        }
    }

    virtual int VerticesCount() const {
        int answer = 0;
        for(const std::pair<std::pair<int, int>, T>& edge : graph){
            answer = std::max(answer, std::max(edge.first.first, edge.first.second));
        }
        return answer + 1;
    }

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        for(const std::pair<std::pair<int, int>, T>& edge : graph){
            if(edge.first.first == vertex) {
                vertices.push_back(edge.first.second);
            }
        }
    }

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        for(const std::pair<std::pair<int, int>, T>& edge : graph){
            if(edge.first.second == vertex) {
                vertices.push_back(edge.first.first);
            }
        }
    }

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
        std::vector<bool> used = std::vector<bool>(VerticesCount());
        __dfs__(vertex, vertices, used);
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

protected:
    std::vector<std::pair<std::pair<int, int>, T>> graph;

    virtual std::list<std::pair<int, T>> __get__next__(int vertex) const {
        std::list<std::pair<int, T>> answer;
        for(const std::pair<std::pair<int, int>, T>& edge : graph){
            if(edge.first.first == vertex) {
                answer.push_back(std::pair<int, T>(edge.first.second, edge.second));
            }
        }
        return answer;
    }

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

#endif //HOMEWORK_1_ARCGRAPH_H
