#include "arcGraph.h"

template <typename T>
ArcGraph<T>::ArcGraph() {}

template <typename T>
ArcGraph<T>::ArcGraph(IGraph<T> *_oth) {
    
}

template <typename T>
void ArcGraph<T>::AddEdge(int from, int to, T &&element) {
    edges.insert(std::make_tuple(from, to, element));
    verticeList.insert(to);
    verticeList.insert(from);
}

template <typename T>
int ArcGraph<T>::VerticesCount() const { 
    return static_cast<int>(verticeList.size());
}

template <typename T>
void ArcGraph<T>::GetNextVertices(int vertex, std::vector<int> &vertices) const {
    vertices.clear();
    for (const auto& edge: edges) {
        if (get<0>(edge) == vertex) {
            vertices.push_back(get<1>(edge));
        }
    }
}

template <typename T>
void ArcGraph<T>::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
    vertices.clear();
    for (const auto& edge: edges) {
        if (get<1>(edge) == vertex) {
            vertices.push_back(get<0>(edge));
        }
    }
}

template <typename T>
void ArcGraph<T>::DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
    vertices.clear();
    if (edges.find(vertex) == edges.end()) {
        return;
    }
    std::map<int, bool> used;
    std::functional<void(int)> dfs = [&](int current) {
        used[current] = true;
        vertices.push_back(current);
        auto it = getLbound(current);
        for (; (it != edges.end()) && (get<0>(*it) == current); ++it) {
            if (!used[get<1>(*it)]) {
                dfs(get<1>(*it));
            }
        }
    };
    dfs(vertex);
}

template <typename T>
void ArcGraph<T>::BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
    vertices.clear();
    if (edges.find(vertex) == edges.end()) {
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
        auto it = getLbound(current);
        for (; (it != edges.end()) && (get<0>(*it) == current); ++it) {
            if (!used[get<1>(*it)]) {
                continue;
            }
            used[get<1>(*it)] = true;
            bfs.push(get<1>(*it));
        }
    }
}


template <typename T>
auto ArcGraph<T>::getLbound(int vertex) const {
    return edges.lower_bound(std::make_tuple(vertex, 0, T()));
}