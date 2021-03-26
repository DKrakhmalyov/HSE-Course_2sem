
#ifndef HOMEWORK_1_ARCGRAPH_H
#define HOMEWORK_1_ARCGRAPH_H

#include "../graph.h"

template<typename T = void>
class ArcGraph : public IGraph<T> {
public:
    virtual void AddEdge(int from, int to, T &&element) {
        edges.push_back({from, to, std::move(element)});
        vertexes.insert(from);
        vertexes.insert(to);
    };

    ArcGraph() {
        edges = std::vector<std::tuple<int, int, T>>();
    };

    virtual void GetEdges(std::vector<std::tuple<int, int, T>>& _edges) const {
        _edges = edges;
    }

    ArcGraph(IGraph<T> *_oth) {
        std::vector<std::tuple<int, int, T>> _edges;
        _oth->GetEdges(_edges);
        edges = _edges;
    };

    virtual int VerticesCount() const { return static_cast<int>(vertexes.size()); };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        for(std::tuple<int, int, T> edge : edges){
            if(std::get<0>(edge) == vertex){
                vertices.push_back(std::get<1>(edge));
            }
        }
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        for(std::tuple<int, int, T> edge : edges){
            if(std::get<1>(edge) == vertex){
                vertices.push_back(std::get<0>(edge));
            }
        }
    };

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
        std::vector<bool> used(VerticesCount(), false);
        std::vector<std::map<int, T>> graph(VerticesCount());
        for(std::tuple<int, int, T> t : edges){
            graph[std::get<0>(t)][std::get<1>(t)] = std::get<2>(t);
        }
        _dfs(vertex, vertices, used, graph);

    };

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
        std::vector<bool> used(VerticesCount(), false);
        int maxi = 0;
        for(int i = 0; i < edges.size(); ++i){
            maxi = std::max(std::get<0>(edges[i]), std::get<1>(edges[i])) + 1;
        }
        std::vector<std::map<int, T>> graph(maxi);
        for(std::tuple<int, int, T> t : edges){
            graph[std::get<0>(t)][std::get<1>(t)] = std::get<2>(t);
        }
        std::queue<int> order;
        used[vertex] = true;
        vertices.push_back(vertex);
        order.push(vertex);
        int current = 0;
        while(!order.empty()){
            current = order.front();
            order.pop();
            for(std::pair<int, T> t : graph[current]){
                if(!used[t.first]){
                    vertices.push_back(t.first);
                    order.push(t.first);
                }
            }
        }
    };

protected:
    std::vector<std::tuple<int, int, T>> edges;
    std::set<int> vertexes;

    void _dfs(int vertex, std::vector<int> &vertices, std::vector<bool> &used,
              std::vector<std::map<int, T>>& graph) const {
        used[vertex] = true;
        vertices.push_back(vertex);
        for(size_t i = 0; i < VerticesCount(); ++i){
            if(!used[i]){
                _dfs(vertex, vertices, used, graph);
            }
        }
    }
};

#endif HOMEWORK_1_ARCGRAPH_H