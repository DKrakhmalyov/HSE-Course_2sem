
#ifndef HOMEWORK_1_MATRIXGRAPH_H
#define HOMEWORK_1_MATRIXGRAPH_H


#include "../graph.h"

template<typename T>
struct MatrixEdge {
    bool isConnected;
    T element;

    MatrixEdge() :
        isConnected(0),
        element(T()) {
    }

    MatrixEdge(bool _isConnected, T &&_element) :
        isConnected(_isConnected),
        element(_element) {
    }

    MatrixEdge(const MatrixEdge<T> &edge) : 
        isConnected(edge.isConnected),
        element(edge.element) {
    }

    MatrixEdge<T> operator= (const MatrixEdge<T> &edge) {
        isConnected = edge.isConnected;
        element = edge.element;
        return *this;
    }
};

template<typename T = void>
class MatrixGraph : public IGraph<T> {
public:
    virtual void AddEdge(int from, int to, T &&element) {
        if(from >= g.size()) {
            g.resize(from + 1);
            for(int i = 0; i < g.size(); i++) {
                g[i].resize(from + 1);
            }
        }
        if(to >= g.size()) {
            g.resize(to + 1);
            for(int i = 0; i < g.size(); i++) {
                g[i].resize(to + 1);
            }
        }
        g[from][to] = MatrixEdge<T>{true, std::move(element)};
    };

    MatrixGraph() {};

    MatrixGraph(IGraph<T> *_oth) {
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

    MatrixGraph(const MatrixGraph &_oth) {
        g = _oth.g;
    }

    virtual int VerticesCount() const { 
        int count = 0;
        for(int i = 0; i < g.size(); i++) {
            bool isConnected = false;
            for(int j = 0; j < g[i].size(); j++) {
                isConnected |= g[i][j].isConnected;
            }
            if(isConnected) {
                count++;
            }
        }
        return count;
    };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        for(int to = 0; to < g[vertex].size(); to++) {
            if(g[vertex][to].isConnected) {
                vertices.push_back(to);
            }
        }
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        for(int from = 0; from < g.size(); from++) {
            if(g[from][vertex].isConnected) {
                vertices.push_back(from);
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
        for(int to = 0; to < g[vertex].size(); to++) {
            if(g[vertex][to].isConnected) {
                weights.push_back(T(g[vertex][to].element));
            }
        }
    }

private:
    std::vector<std::vector<MatrixEdge<T>>> g;

    void dfs(int vertex, std::vector<int> &vertices, std::vector<bool> &used) const {
        used[vertex] = true;
        vertices.push_back(vertex);
        std::vector<int> next;
        GetNextVertices(vertex, next);
        for(auto to : next) {
            if(!used[to]) {
                dfs(to, vertices, used);
            }
        }
    }
};

#endif //HOMEWORK_1_MATRIXGRAPH_H
