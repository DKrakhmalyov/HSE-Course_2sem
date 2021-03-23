
#ifndef HOMEWORK_1_MATRIXGRAPH_H
#define HOMEWORK_1_MATRIXGRAPH_H


#include "../graph.h"

template<typename T = void>
class MatrixGraph : public IGraph<T> {
public:
    virtual void AddEdge(int from, int to, T &&element) {
        int max_from_to = std::max(from, to);
        if (VerticesCount() < max_from_to + 1){
            for (std::vector<std::pair<bool, T>>& i : graph){
                i.resize(max_from_to + 1, std::pair<bool, T>(false, T()));
            }
            graph.resize(std::max(from, to) + 1, std::vector<std::pair<bool, T>>(max_from_to + 1,
                    std::pair<bool, T>(false, T())));
        }
        graph[from][to] = std::pair<bool, T>(true, std::move(element));
    }

    MatrixGraph() {
        graph = std::vector<std::vector<std::pair<bool, T>>>();
    }

    MatrixGraph(IGraph<T> *_oth) {
        graph = std::vector<std::vector<std::pair<bool, T>>>(_oth->VerticesCount(),
                                                             std::vector<std::pair<bool, T>>(_oth->VerticesCount(),
                                                                     std::pair<bool, T>(false, T())));
        for(int i = 0; i < _oth->VerticesCount(); i++){
            for (std::pair<int, T>& edge : this->__call__get__next__(_oth, i)){
                graph[i][edge.first] = std::pair<bool, T>(true, std::move(edge.second));
            }
        }
    }

    virtual int VerticesCount() const { return graph.size(); }

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        for (int i = 0; i < VerticesCount(); i++){
            if(graph[vertex][i].first != false){
                vertices.push_back(i);
            }
        }
    }

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        for(int i = 0; i < VerticesCount(); i++){
            if(graph[i][vertex].first != false){
                vertices.push_back(i);
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
    std::vector<std::vector<std::pair<bool, T>>> graph;

    virtual std::list<std::pair<int, T>> __get__next__(int vertex) const {
        std::list<std::pair<int, T>> answer;
        for(int i = 0; i < VerticesCount(); i++){
            if (graph[vertex][i].first) {
                answer.push_back(std::pair<int, T>(i, graph[vertex][i].second));
            }
        }
        return answer;
    }

    virtual void __dfs__(int vertex, std::vector<int> &vertices, std::vector<bool> &used) const {
        used[vertex] = true;
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

#endif //HOMEWORK_1_MATRIXGRAPH_H
