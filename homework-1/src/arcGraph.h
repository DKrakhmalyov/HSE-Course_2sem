
#ifndef HOMEWORK_1_ARCGRAPH_H
#define HOMEWORK_1_ARCGRAPH_H

#include "../graph.h"

template<typename T = void>
class ArcGraph : public IGraph<T> {
public:

    ArcGraph() = default;

    virtual ~ArcGraph() = default;

    ArcGraph(const ArcGraph<T> &other) = default;

    ArcGraph(ArcGraph<T> &&other) = default;

    ArcGraph(IGraph<T> *_oth) {
        std::multiset<std::tuple<int, int, T>> _graph;
        _oth->ConvertToArcGraph(_graph);
        ConvertFromArcGraph(_graph);
    }

    ArcGraph<T>& operator=(const ArcGraph<T> &other) {
        if (this != &other) {
            verticeList = other.verticeList;
            edges = other.edges;
        }
        return *this;
    }

    ArcGraph<T>& operator=(ArcGraph<T> &&other) {
        if (this != &other) {
            verticeList = std::move(other.verticeList);
            edges = std::move(other.edges);
        }
        return *this;
    }

    virtual void AddEdge(int from, int to, T &&element) override final {
        edges.insert(std::make_tuple(from, to, element));
        verticeList.insert(to);
        verticeList.insert(from);
    }

    virtual int VerticesCount() const override final { 
        return static_cast<int>(verticeList.size());
    }

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const override final {
        vertices.clear();
        for (const auto& edge: edges) {
            if (std::get<0>(edge) == vertex) {
                vertices.push_back(std::get<1>(edge));
            }
        }
    }

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const override final {
        vertices.clear();
        for (const auto& edge: edges) {
            if (std::get<1>(edge) == vertex) {
                vertices.push_back(std::get<0>(edge));
            }
        }
    }

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const override final {
        vertices.clear();
        if (verticeList.find(vertex) == verticeList.end()) {
            return;
        }
        std::unordered_map<int, bool> used;
        std::function<void(int)> dfs = [&](int current) {
            used[current] = true;
            vertices.push_back(current);
            auto it = getLbound(current);
            for (; (it != edges.end()) && (std::get<0>(*it) == current); ++it) {
                if (!used[std::get<1>(*it)]) {
                    dfs(std::get<1>(*it));
                }
            }
        };
        dfs(vertex);
    }

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const override final {
        vertices.clear();
        if (verticeList.find(vertex) == verticeList.end()) {
            return;
        }
        std::unordered_map<int, bool> used;
        std::queue<int, std::list<int>> bfs;
        used[vertex] = true;
        bfs.push(vertex);
        while (!bfs.empty()) {
            int current = bfs.front();
            bfs.pop();
            vertices.push_back(current);
            auto it = getLbound(current);
            for (; (it != edges.end()) && (std::get<0>(*it) == current); ++it) {
                if (used[std::get<1>(*it)]) {
                    continue;
                }
                used[std::get<1>(*it)] = true;
                bfs.push(std::get<1>(*it));
            }
        }
    }

    virtual void ConvertToArcGraph(std::multiset<std::tuple<int, int, T>>& _graph) override final {
        _graph = edges;
    }

    virtual void ConvertFromArcGraph(std::multiset<std::tuple<int, int, T>>& _graph) override final {
        for (auto edge: _graph) {
            AddEdge(std::get<0>(edge), std::get<1>(edge), std::move(std::get<2>(edge)));
        }
    }

private:

    std::set<int> verticeList;

    std::multiset<std::tuple<int, int, T>> edges;

    // std::multiset<std::tuple<int, int, T>>::iterator
    auto getLbound(int vertex) const {
        return edges.lower_bound(std::make_tuple(vertex, -1, T()));
    }
};

#endif //HOMEWORK_1_ARCGRAPH_H
