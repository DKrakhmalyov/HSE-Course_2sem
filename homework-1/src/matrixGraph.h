
#ifndef HOMEWORK_1_MATRIXGRAPH_H
#define HOMEWORK_1_MATRIXGRAPH_H


#include "../graph.h"

template<typename T = void>
class MatrixGraph : public IGraph<T> {
public:

    MatrixGraph(unsigned int vertices_count){
        graph.resize(vertices_count);
        for(int i = 0; i < graph.size(); ++i){
            graph[i].resize(vertices_count);
        }
    }

    virtual void AddEdge(int from, int to, T &&element) {
        int maxi = std::max(from, to) + 1;
        if(graph.size() <= maxi){
            graph.resize(maxi);
            for(int i = 0; i < graph.size(); ++i){
                graph[i].resize(maxi, nullptr);
            }
        }
        graph[from][to] = new T(element);

    };

    virtual void GetEdges(std::vector<std::tuple<int, int, T>>& edges) const{
        for(size_t i = 0; i < VerticesCount(); ++i){
            for(size_t j = 0; j < VerticesCount(); ++j){
                if(graph[i][j] != nullptr){
                    edges.push_back({i,j, *graph[i][j]});
                }
            }
        }
    }

    MatrixGraph(){
        graph = std::vector<std::vector<T*>>();
    }

    MatrixGraph(IGraph<T> *_oth) {
        std::vector<std::tuple<int, int, T>> edges;
        _oth->GetEdges(edges);
        for(auto edge : edges){
            AddEdge(get<0>(edge), get<1>(edge), std::move(get<2>(edge)));
        }
    };

    virtual int VerticesCount() const { return graph.size(); };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        for(size_t i = 0; i < VerticesCount(); ++i){
            if(graph[vertex][i] != nullptr) {
                vertices.push_back(i);
            }
        }
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        for(size_t i = 0; i < VerticesCount(); ++i){
            if(graph[i][vertex] != nullptr) {
                vertices.push_back(i);
            }
        }
    };

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
        std::vector<bool> used(graph.size(), false);
        _dfs(vertex, vertices, used);
    };

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
        std::queue<int> order;
        std::vector<bool> used(VerticesCount(), false);
        used[vertex] = true;
        order.push(vertex);
        int current = 0;
        while(!order.empty()){
            current = order.front();
            order.pop();
            for(size_t i = 0; i < VerticesCount(); ++i){
                if(!used[i] && graph[current][i] != nullptr){
                    vertices.push_back(i);
                    order.push(i);
                }
            }
        }
    };


protected:
    std::vector<std::vector<T*>> graph;

    void _dfs(int vertex, std::vector<int> &vertices, std::vector<bool> &used) const {
        used[vertex] = true;
        vertices.push_back(vertex);
        std::cout << vertex << std::endl;
        for(int i = 0; i < VerticesCount(); ++i){
            if(!used[i] && graph[vertex][i] != nullptr){
                _dfs(i, vertices, used);
            }
        }

    }

};

#endif //HOMEWORK_1_MATRIXGRAPH_H