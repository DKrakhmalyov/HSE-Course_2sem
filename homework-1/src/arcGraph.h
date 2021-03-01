
#ifndef HOMEWORK_1_ARCGRAPH_H
#define HOMEWORK_1_ARCGRAPH_H

#include "../graph.h"

template<typename T = void>
class ArcGraph : public IGraph<T> {
public:
    ArcGraph(): _vCount(0) {};

    ArcGraph(IGraph<T> *_oth) {};
    
    virtual void AddEdge(int from, int to, T &&element) {
        if (from >= _vCount || to >= _vCount || from < 0 || to < 0) {
            throw "Error: incorrect node";
        }
        _edges.push_back({from, to});
        _weights.push_back(element);
    };

    void AddNode() {
        _vCount++;
    }

    virtual int VerticesCount() const {
        return _vCount;
    };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        for (auto edge : _edges) {
            if (edge.first == vertex) {
                vertices.push_back(edge.second);
            }
        }
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        for (auto edge : _edges) {
            if (edge.second == vertex) {
                vertices.push_back(edge.first);
            }
        }
    };

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
        bool *used = new bool[_vCount];
        _dfs(vertex, vertices, used);
        delete[] used;
    };

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
        bool *used = new bool[_vCount];
        std::queue<int> queue;
        queue.push(vertex);
        while (!queue.empty()) {
            vertex = queue.front();
            queue.pop();
            vertices.push_back(vertex);
            for (auto edge : _edges) {
                if (edge.first == vertex && !used[edge.second]) {
                    queue.push(edge.second);
                    used[edge.second] = true;
                }
            }
        }
        delete[] used;
    };

private:
    size_t _vCount;

    std::vector<std::pair<int, int>> _edges;
    std::vector<T> _weights;

    void _dfs(int vertex, std::vector<int> &vertices, bool* used) const {
        used[vertex] = true;
        vertices.push_back(vertex);
        for (auto edge : _edges) {
            if (edge.first == vertex && !used[edge.second]) {
                _dfs(edge.second, vertices, used);
            }
        }    
    }
};

#endif //HOMEWORK_1_ARCGRAPH_H
