
#ifndef HOMEWORK_1_LISTGRAPH_H
#define HOMEWORK_1_LISTGRAPH_H

#include "../graph.h"


template<typename T>
class ListGraph : public IGraph<T> {
public:

    ListGraph() = default;

    virtual ~ListGraph() = default;

    ListGraph(const ListGraph<T> &other) = default;

    ListGraph(ListGraph<T> &&other) = default;

    ListGraph(IGraph<T> *_oth) {
        std::multiset<std::tuple<int, int, T>> _graph;
        _oth->ConvertToArcGraph(_graph);
        ConvertFromArcGraph(_graph);
    }

    ListGraph<T>& operator=(const ListGraph<T> &other) {
        if (this != &other) {
            toList = other.toList;
            fromList = other.fromList;
        }
        return *this;
    }

    ListGraph<T>& operator=(ListGraph<T> &&other) {
        if (this != &other) {
            toList = std::move(other.toList);
            fromList = std::move(other.fromList);
        }
        return *this;
    }

    virtual void AddEdge(int from, int to, T &&element) override final {
        toList[from].push_back(std::make_pair(to, element));
        fromList[to].push_back(std::make_pair(from, element));
    }

    virtual int VerticesCount() const override final { 
        return static_cast<int>(toList.size());
    }

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const override final {
        vertices.clear();
        for (const auto& to: toList[vertex]) {
            vertices.push_back(to.first);
        }
    }

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const override final {
        vertices.clear();
        for (const auto& from: fromList[vertex]) {
            vertices.push_back(from.first);
        }
    }

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const override final {
        vertices.clear();
        if (toList.find(vertex) == toList.end()) {
            return;
        }
        std::map<int, bool> used;
        std::function<void(int)> dfs = [&](int current) {
            used[current] = true;
            vertices.push_back(current);
            for (const auto& to: toList[current]) {
                if (!used[to.first]) {
                    dfs(to.first);
                }
            }
        };
        dfs(vertex);
    }

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const override final {
        vertices.clear();
        if (toList.find(vertex) == toList.end()) {
            return;
        }
        std::map<int, bool> used;
        std::queue<int, std::list<int>> bfs;
        used[vertex] = true;
        bfs.push(vertex);
        while (!bfs.empty()) {
            int current = bfs.front();
            bfs.pop();
            vertices.push_back(current);
            for (const auto& to: toList[current]) {
                if (used[to.first]) {
                    continue;
                }
                used[to.first] = true;
                bfs.push(to.first);
            }
        }
    }

    virtual void ConvertToArcGraph(std::multiset<std::tuple<int, int, T>>& _graph) override final {
        _graph.clear();
        for (const auto& currVert: toList) {
            for (const auto& to: currVert.second) {
                _graph.insert(std::make_tuple(
                    currVert.first,
                    to.first,
                    to.second
                ));
            }
        }
    }

    virtual void ConvertFromArcGraph(std::multiset<std::tuple<int, int, T>>& _graph) override final {
        for (auto edge: _graph) {
            AddEdge(std::get<0>(edge), std::get<1>(edge), std::move(std::get<2>(edge)));
        }
    }

private:

    mutable std::map<int, std::list<std::pair<int, T>>> toList;

    mutable std::map<int, std::list<std::pair<int, T>>> fromList;
};


#endif //HOMEWORK_1_LISTGRAPH_H
