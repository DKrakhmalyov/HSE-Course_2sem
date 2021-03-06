
#ifndef HOMEWORK_1_LISTGRAPH_H
#define HOMEWORK_1_LISTGRAPH_H

#include "../graph.h"
#include<bits/stdc++.h>

template<typename T>
struct Edge {
    int v;
    T element;
    bool isReversedEdge;

    Edge() = default;

    Edge(int _v, bool _isReversedEdge, T &&_element) :
        v(_v),
        element(_element),
        isReversedEdge(_isReversedEdge) {
    }

    Edge(const Edge<T> &edge) : 
        v(edge.v),
        element(edge.element),
        isReversedEdge(edge.isReversedEdge) {}
};

template<typename T>
class ListGraph : public IGraph<T> {
public:
    virtual void AddEdge(int from, int to, T &&element) {
        resizeGraph(from);
        resizeGraph(to);
        g[from].push_back(Edge<T>{to, 0, std::move(element)});
        g[to].push_back(Edge<T>{from, 1, std::move(element)});
    };

    ListGraph() = default;

    ListGraph(IGraph<T> *_oth) {
        g.clear();
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

    ListGraph(const ListGraph &oth) {
        g = oth.g;
    }

    virtual int VerticesCount() const { return g.size(); };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        for(auto &v : g[vertex]) {
            if(!v.isReversedEdge) {
                vertices.push_back(v.v);
            }
        }
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        for(auto &v : g[vertex]) {
            if(v.isReversedEdge) {
                vertices.push_back(v.v);
            }
        }
    };

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
        std::vector<bool> used(g.size());
        dfs(vertex, vertices, used);
    };

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
        std::vector<bool> used(g.size());
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
        resizeGraph(vertex);
        
        for(auto &to : g[vertex]) {
            if(!to.isReversedEdge) {
                weights.push_back(T(to.element));
            }
        }
    };

private:
    std::vector<std::vector<Edge<T>>> g;

    void resizeGraph(int v) {
        if(v >= g.size()) {
            g.resize(v + 1);
        }
    }

    void dfs(int vertex, std::vector<int> &vertices, std::vector<bool> &used) const {
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


#endif //HOMEWORK_1_LISTGRAPH_H
