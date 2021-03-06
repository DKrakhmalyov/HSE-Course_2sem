
#ifndef HOMEWORK_1_ARCGRAPH_H
#define HOMEWORK_1_ARCGRAPH_H

#include "../graph.h"

template<typename T>
struct ArcEdge {
    int from;
    int to;
    T element;

    ArcEdge() = default;

    ArcEdge(int _from, int _to, T &&_element) :
        from(_from),
        to(_to),
        element(_element) {
    }

    ArcEdge(const ArcEdge<T> &edge) : 
        from(edge.from),
        to(edge.to),
        element(edge.element) {
    }

    ArcEdge<T> operator= (const ArcEdge<T> &edge) {
        from = edge.from;
        to = edge.to;
        element = edge.element;
        return *this;
    }
};

template<typename T = void>
class ArcGraph : public IGraph<T> {
public:
    virtual void AddEdge(int from, int to, T &&element) {
        g.push_back(ArcEdge<T>{from, to, std::move(element)});
        vertices.insert(from);
        vertices.insert(to);
    };

    ArcGraph() = default;

    ArcGraph(IGraph<T> *_oth) {
        g.clear();
        vertices.clear();
        int size = _oth->VerticesCount();
        for(int from = 0; from < size; from++) {
            std::vector<int> next;
            std::vector<T> nextWeights;  
            _oth->GetNextWeights(from, nextWeights);
            _oth->GetNextVertices(from, next);
            for(int i = 0; i < next.size(); i++) {
                AddEdge(from, next[i], std::move(nextWeights[i]));
            }
        }
    };

    ArcGraph(const ArcGraph &_oth) {
        g = _oth.g;
        vertices = _oth.vertices;
    }

    virtual int VerticesCount() const { 
        return vertices.size(); 
    };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        for(int i = 0; i < g.size(); i++) {
            if(g[i].from == vertex) {
                vertices.push_back(g[i].to);
            }
        }
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        for(int i = 0; i < g.size(); i++) {
            if(g[i].to == vertex) {
                vertices.push_back(g[i].from);
            }
        }
    };

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
        std::map<int, bool> used;
        dfs(vertex, vertices, used);
    };

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
        std::map<int, bool> used;
        std::queue<int> q;
        q.push(vertex);
        used[vertex] = true;
        while(!q.empty()) {
            int from = q.front();
            q.pop();
            vertices.push_back(q.front());
            std::vector<int> next;
            GetNextVertices(vertex, next);
            for(auto to : next) {
                if(!used[to]) {
                    used[to] = true;
                    q.push(to);
                }
            }
        }
    };

    virtual void GetNextWeights(int vertex, std::vector<T> &weights) {
        for(int i = 0; i < g.size(); i++) {
            if(g[i].from == vertex) {
                weights.push_back(T(g[i].element));
            }
        }
    }

private:
    std::vector<ArcEdge<T>> g;
    std::set<int> vertices;

    void dfs(int vertex, std::vector<int> &vertices, std::map<int, bool> &used) const {
        vertices.push_back(vertex);
        used[vertex] = true;
        std::vector<int> next;
        GetNextVertices(vertex, next);
        for(auto v : next) {
            if(!used[v]) {
                dfs(v, vertices, used);
            }
        }
    }
};

#endif //HOMEWORK_1_ARCGRAPH_H
