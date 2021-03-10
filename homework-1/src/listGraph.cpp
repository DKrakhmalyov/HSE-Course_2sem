#include "listGraph.h"

template <typename T> 
ListGraph<T>::ListGraph() {}

template <typename T> 
ListGraph<T>::ListGraph(IGraph<T> *_oth) {
    
}

template <typename T> 
int ListGraph<T>::VerticesCount() const { 
    return static_cast<int>(toList.size());
}

template <typename T> 
void ListGraph<T>::AddEdge(int from, int to, T &&element) {
    toList[from].push_back(std::make_pair(to, element));
    fromList[to].push_back(std::make_pair(from, element));
}

template <typename T> 
void ListGraph<T>::GetNextVertices(int vertex, std::vector<int> &vertices) const {
    vertices.clear();
    for (const auto& to: toList[vertex]) {
        vertices.push_back(to.first);
    }
}

template <typename T> 
void ListGraph<T>::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
    vertices.clear();
    for (const auto& from: fromList[vertex]) {
        vertices.push_back(from.first);
    }
}

template <typename T> 
void ListGraph<T>::DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
    vertices.clear();
    if (toList.find(vertex) == toList.end()) {
        return;
    }
    std::map<int, bool> used;
    std::functional<void(int)> dfs = [&](int current) {
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

template <typename T> 
void ListGraph<T>::BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
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
