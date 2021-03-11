
#ifndef HOMEWORK_1_ARCGRAPH_H
#define HOMEWORK_1_ARCGRAPH_H
#include <utility>
#include "../graph.h"

template<typename T = void>
class ArcGraph : public IGraph<T> {
public:
    ArcGraph(): _vCount(0) {};

    ArcGraph(IGraph<T> *_oth) {
        _vCount = 0;
        std::vector<std::pair<std::pair<int,int>, T>> edges;
        _oth->GetEdges(edges);
        for (auto edge : edges) {
            AddEdge(edge.first.first, edge.first.second, std::move(edge.second));
        }
    };

    ~ArcGraph() {
        for (T weight : _weights) {
            ObjectDeleter<T>::Delete(weight);
        }
    }
    
    virtual void AddEdge(int from, int to, T &&element) {
        _validate(from);
        _validate(to);
        from = _internalIndex[from];
        to = _internalIndex[to];
        _edges.emplace_back(from, to);
        _weights.emplace_back(std::forward<T>(element));
    };

    virtual int VerticesCount() const {
        return _vCount;
    };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        for (auto edge : _edges) {
            if (edge.first == _internalIndex.find(vertex)->second) {
                vertices.emplace_back(_externalIndex.find(edge.second)->second);
            }
        }
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        for (auto edge : _edges) {
            if (edge.second == _internalIndex.find(vertex)->second) {
                vertices.emplace_back(_externalIndex.find(edge.first)->second);
            }
        }
    };

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
        std::vector<bool> used(_vCount);
        _dfs(_internalIndex.find(vertex)->second, vertices, used);
    };

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
        bool *used = new bool[_vCount];
        std::queue<int> queue;
        vertex = _internalIndex.find(vertex)->second;
        queue.push(vertex);
        while (!queue.empty()) {
            vertex = queue.front();
            queue.pop();
            vertices.emplace_back(_externalIndex.find(vertex)->second);
            for (auto edge : _edges) {
                if (edge.first == vertex && !used[edge.second]) {
                    queue.push(edge.second);
                    used[edge.second] = true;
                }
            }
        }
        delete[] used;
    };

    virtual void GetEdges(std::vector<std::pair<std::pair<int,int>, T>> &edges) const {
        int v1, v2;
        for (int i = 0; i < _edges.size(); i++) {
            v1 = _externalIndex.find(_edges[i].first)->second, v2 = _externalIndex.find(_edges[i].second)->second;
            edges.emplace_back(std::make_pair(v1, v2), ObjectCreater<T>::Create(_weights[i]));
        }
    }

private:
    size_t _vCount;

    std::vector<std::pair<int, int>> _edges;
    std::vector<T> _weights;

    std::unordered_map<int, int> _internalIndex;
    std::unordered_map<int, int> _externalIndex;

    void _validate(int vertex) {
        if (_internalIndex.find(vertex) == _internalIndex.end()) {
            _externalIndex[_vCount] = vertex;
            _internalIndex[vertex] = _vCount++; 
        }
    }

    void _dfs(int vertex, std::vector<int> &vertices, std::vector<bool> &used) const {
        used[vertex] = true;
        vertices.emplace_back(_externalIndex.find(vertex)->second);
        for (auto edge : _edges) {
            if (edge.first == vertex && !used[edge.second]) {
                _dfs(edge.second, vertices, used);
            }
        }    
    }
};

#endif //HOMEWORK_1_ARCGRAPH_H
