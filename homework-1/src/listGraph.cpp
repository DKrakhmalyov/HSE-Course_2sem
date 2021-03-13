#include "arcGraph.h"
#include "matrixGraph.h"
#include "listGraph.h"

#include "graphConverter.h"

#include <queue>
#include <list>

template<typename T>
ListGraph<T>::ListGraph() noexcept = default;

template<typename T>
ListGraph<T>::ListGraph(IGraph<T>* oth) noexcept {
    if (this->valueIsNotEmpty()) {
        this->clearValue();
    }
    if (GraphConverter::isArcGraph(oth)) {
        ArcGraph<T>* arcGraph = GraphConverter::toArcGraph(oth);
        ListGraph<T>* other = GraphConverter::createListGraphFromArcGraph(arcGraph);
        int32_t size = other->listOfEdges.size();
        this->listOfEdges.resize(size);
        for (int32_t v = 0; v < size; v++) {
            for (const std::pair<int32_t, T*>& pair : other->listOfEdges[v]) {
                T* newWeight = new T(*pair.second);
                std::pair<int32_t, T*> newPair = std::pair(pair.first, newWeight);
                this->listOfEdges[v].push_back(newPair);
            }
        }
        delete other;
        return;
    }
    if (GraphConverter::isListGraph(oth)) {
        ListGraph<T>* other = GraphConverter::toListGraph(oth);
        int32_t size = other->listOfEdges.size();
        this->listOfEdges.resize(size);
        for (int32_t v = 0; v < size; v++) {
            for (const std::pair<int32_t, T*>& pair : other->listOfEdges[v]) {
                T* newWeight = new T(*pair.second);
                std::pair<int32_t, T*> newPair = std::pair(pair.first, newWeight);
                this->listOfEdges[v].push_back(newPair);
            }
        }
        return;
    }
    if (GraphConverter::isMatrixGraph(oth)) {
        MatrixGraph<T>* matrixGraph = GraphConverter::toMatrixGraph(oth);
        ListGraph<T>* other = GraphConverter::createListGraphFromMatrixGraph(matrixGraph);
        int32_t size = other->listOfEdges.size();
        this->listOfEdges.resize(size);
        for (int32_t v = 0; v < size; v++) {
            for (const std::pair<int32_t, T*>& pair : other->listOfEdges[v]) {
                T* newWeight = new T(*pair.second);
                std::pair<int32_t, T*> newPair = std::pair(pair.first, newWeight);
                this->listOfEdges[v].push_back(newPair);
            }
        }
        delete other;
        return;
    }
}

template<typename T>
ListGraph<T>::ListGraph(const ListGraph<T>& other) noexcept {
    if (this->valueIsNotEmpty()) {
        this->clearValue();
    }
    if (other.valueIsEmpty()) {
        return;
    }
    int32_t size = other.listOfEdges.size();
    this->listOfEdges.resize(size);
    for (int32_t v = 0; v < size; v++) {
        for (const std::pair<int32_t, T*>& pair : other.listOfEdges[v]) {
            T* newWeight = new T(*pair.second);
            std::pair<int32_t, T*> newPair = std::pair(pair.first, newWeight);
            this->listOfEdges[v].push_back(newPair);
        }
    }
}

template<typename T>
ListGraph<T>::~ListGraph() noexcept {
    if (this->valueIsEmpty()) {
        return;
    }
    this->clearValue();
}

template<typename T>
void ListGraph<T>::addEdge(const int32_t& from, const int32_t& to,T element) {
    if (this->listOfEdges.size() <= from) {
        this->listOfEdges.resize(from + 1);
    }
    if (this->listOfEdges.size() <= to) {
        this->listOfEdges.resize(to + 1);
    }
    T* weight = new T(element);
    std::pair<int32_t, T*> newEdge = std::pair<int32_t, T*>(to, weight);
    this->listOfEdges[from].push_back(newEdge);
}

template<typename T>
int ListGraph<T>::verticesCount() {
    std::map<int32_t, bool> used;
    const int32_t size = this->listOfEdges.size();
    for (int32_t v = 0; v < size; v++) {
        for (const std::pair<int32_t, T*> pair : this->listOfEdges[v]) {
            used[v] = true;
            used[pair.first] = true;
        }
    }
    return used.size();
}

template<typename T>
void ListGraph<T>::getNextVertices(const int32_t& vertex, std::vector<int32_t> &vertices) {
    vertices.clear();
    vertices.shrink_to_fit();
    for (const std::pair<int32_t, T*> pair : this->listOfEdges[vertex]) {
        vertices.push_back(pair.first);
    }
}

template<typename T>
void ListGraph<T>::getPrevVertices(const int32_t& vertex, std::vector<int32_t> &vertices) {
    vertices.clear();
    vertices.shrink_to_fit();
    const int32_t size = this->listOfEdges.size();
    for (int32_t v = 0; v < size; v++) {
        for (const std::pair<int32_t, T*> pair : this->listOfEdges[v]) {
            if (pair.first == vertex) {
                vertices.push_back(v);
            }
        }
    }
}

template<typename T>
void ListGraph<T>::deepFirstSearch(const int32_t& vertex, std::vector<int32_t> &vertices) {
    const int32_t size = this->listOfEdges.size();
    std::vector<bool> used = std::vector<bool>(size + 1, false);
    vertices.clear();
    vertices.shrink_to_fit();
    if (vertex >= size) {
        return;
    }
    this->dfs(vertex, used, vertices);
}

template<typename T>
void ListGraph<T>::breadthFirstSearch(const int32_t& vertex, std::vector<int32_t> &vertices) {
    vertices.clear();
    vertices.shrink_to_fit();
    if (vertex >= this->listOfEdges.size()) {
        return;
    }
    this->bfs(vertex, vertices);
}

template<typename T>
bool ListGraph<T>::valueIsEmpty() const noexcept {
    return this->listOfEdges.size() == 0;
}

template<typename T>
bool ListGraph<T>::valueIsNotEmpty() const noexcept {
    return !this->valueIsEmpty();
}

template<typename T>
void ListGraph<T>::clearValue() {
    int32_t size = this->listOfEdges.size();
    for (int32_t v = 0; v < size; v++) {
        for (std::pair<int32_t, T*>& pair : this->listOfEdges[v]) {
            delete pair.second;
        }
        this->listOfEdges[v].clear();
        this->listOfEdges[v].shrink_to_fit();
    }
    this->listOfEdges.clear();
    this->listOfEdges.shrink_to_fit();
}

template<typename T>
ListGraph<T>* ListGraph<T>::getCopy() const noexcept {
    ListGraph<T>* copy = new ListGraph<T>();
    int32_t size = this->listOfEdges.size();
    copy->listOfEdges.resize(size);
    for (int32_t v = 0; v < size; v++) {
        for (const std::pair<int32_t, T*>& pair : this->listOfEdges[v]) {
            T* newWeight = new T(*pair.second);
            std::pair<int32_t, T*> newPair = std::pair(pair.first, newWeight);
            copy->listOfEdges[v].push_back(newPair);
        }
    }
    return copy;
}

template<typename T>
void ListGraph<T>::dfs(const int32_t currentVertice, std::vector<bool>& used, std::vector<int32_t>& resultVector) const noexcept {
    used[currentVertice] = true;
    resultVector.push_back(currentVertice);
    for (const std::pair<int32_t, T*>& pair : this->listOfEdges[currentVertice]) {
        if (used[pair.first]) {
            continue;
        }
        dfs(pair.first, used, resultVector);
    }
}

template<typename T>
void ListGraph<T>::bfs(const int32_t startVertice, std::vector<int32_t>& resultVector) const noexcept {
    std::map<int32_t, bool> used;
    std::queue<int32_t, std::list<int32_t>> bfs;
    used[startVertice] = true;
    bfs.push(startVertice);
    while (!bfs.empty()) {
        int32_t currentVertice = bfs.front();
        bfs.pop();
        resultVector.push_back(currentVertice);
        for (const std::pair<int32_t, T*> pair : this->listOfEdges[currentVertice]) {
            if (used[pair.first]) {
                continue;
            }
            used[pair.first] = true;
            bfs.push(pair.first);
        }
    }
}

template<typename T>
std::vector<std::vector<std::pair<int32_t, T*>>> ListGraph<T>::getListOfEdges() const noexcept {
    return this->listOfEdges;
}