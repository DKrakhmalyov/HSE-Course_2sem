
#ifndef HOMEWORK_1_LISTGRAPH_H
#define HOMEWORK_1_LISTGRAPH_H

#include "../graph.h"


template<typename T>
class ListGraph : public IGraph<T> {
public:
    virtual void AddEdge(int from, int to, T &&element) {
        int maxi = std::max(from, to) + 1;
        if(graph.size() < maxi){
            graph.resize(maxi, std::map<int, T>());
        }
        if(reversed_graph.size() < maxi){
            reversed_graph.resize(maxi, std::map<int, T>());
        }
        graph[from][to] = element;
        reversed_graph[to][from] = graph[from][to];
        vertices_.insert(from);
        vertices_.insert(to);
    };

    ListGraph() = default;

    virtual void GetEdges(std::vector<std::tuple<int, int, T>>& edges) const {
        for(size_t i = 0; i < graph.size(); ++i){
            for(std::pair<int, T> t : graph[i]){
                edges.emplace_back(i,t.first, t.second);
            }
        }
    }

    ListGraph(IGraph<T> *_oth) {
        std::vector<std::tuple<int, int, T>> edges;
        _oth->GetEdges(edges);
        int maxi = 0;
        for(std::tuple<int, int, T> t : edges){
            maxi = std::max(get<0>(t), get<1>(t)) + 1;
            vertices_.insert(std::get<0>(t));
            vertices_.insert(std::get<1>(t));
        }
        graph = std::vector<std::map<int, T>>(maxi);
        reversed_graph = std::vector<std::map<int, T>>(maxi);
        for(std::tuple<int, int, T> t : edges){
            graph[std::get<0>(t)][std::get<1>(t)] = std::get<2>(t);
            reversed_graph[std::get<1>(t)][std::get<0>(t)] = std::get<2>(t);
        }
    };

    virtual int VerticesCount() const { return static_cast<int>(vertices_.size()); };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        for(std::pair<int, T> t : graph[vertex]){
            vertices.push_back(t.first);
        }
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        for(std::pair<int, T> t : reversed_graph[vertex]){
            vertices.push_back(t.first);
        }
    };

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
        std::vector<bool> used(graph.size(), false);
        _dfs(vertex, vertices, used);
    };

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
        std::queue<int> order;
        std::vector<bool> used(graph.size(), false);
        used[vertex] = true;
        order.push(vertex);
        int current = 0;
        while(!order.empty()){
            current = order.front();
            order.pop();
            for(std::pair<int, T> t : graph[current]){
                if(!used[t.first]){
                    used[t.first] = true;
                    vertices.push_back(t.first);
                    order.push(t.first);
                }
            }
        }
    };

protected:
    std::vector<std::map<int, T>> graph;
    std::vector<std::map<int, T>> reversed_graph;
    std::set<int> vertices_;

    void _dfs(int vertex, std::vector<int>& vertices, std::vector<bool>& used) const{
        used[vertex] = true;
        vertices.push_back(vertex);
        for(std::pair<int, T> t : graph[vertex]){
            if(!used[t.first]){
                _dfs(t.first,vertices,used);
            }
        }
    }
};


#endif //HOMEWORK_1_LISTGRAPH_H