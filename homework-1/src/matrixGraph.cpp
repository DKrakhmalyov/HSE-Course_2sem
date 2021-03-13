#include "arcGraph.h"
#include "matrixGraph.h"
#include "listGraph.h"

#include "graphConverter.h"

template<typename T>
MatrixGraph<T>::MatrixGraph() = default;

template<typename T>
MatrixGraph<T>::MatrixGraph(IGraph<T> *oth) {
    if (this->valueIsNotEmpty()) {
        this->clearValue();
    }
    if (GraphConverter::isArcGraph(oth)) {
        ArcGraph<T>* arcGraph = GraphConverter::toArcGraph(oth);
        MatrixGraph<T>* other = GraphConverter::createMatrixGraphFromArcGraph(arcGraph);
        const int32_t size = other->matrix.size();
        this->matrix.resize(size);
        for (int32_t v = 0; v < size; v++) {
            for (auto pair : matrix[v]) {
                this->matrix[v][pair.first] = other->matrix[v][pair.first];
            }
        }
        delete other;
        return;
    }
    if (GraphConverter::isMatrixGraph(oth)) {
        MatrixGraph<T>* other = GraphConverter::toMatrixGraph(oth);
        const int32_t size = other->matrix.size();
        this->matrix.resize(size);
        for (int32_t v = 0; v < size; v++) {
            for (auto pair : matrix[v]) {
                this->matrix[v][pair.first] = other->matrix[v][pair.first];
            }
        }
        return;
    }
    if (GraphConverter::isListGraph(oth)) {
        ListGraph<T>* listGraph = GraphConverter::toListGraph(oth);
        MatrixGraph<T>* other = GraphConverter::createMatrixGraphFromListGraph(listGraph);
        const int32_t size = other->matrix.size();
        this->matrix.resize(size);
        for (int32_t v = 0; v < size; v++) {
            for (auto pair : matrix[v]) {
                this->matrix[v][pair.first] = other->matrix[v][pair.first];
            }
        }
        delete other;
        return;
    }
}

template<typename T>
MatrixGraph<T>::MatrixGraph(const MatrixGraph<T>& other) {
    if (this->valueIsNotEmpty()) {
        this->clearValue();
    }
    if (other.valueIsEmpty()) {
        return;
    }
    const int32_t size = other.matrix.size();
    this->matrix.resize(size);
    for (int32_t v = 0; v < size; v++) {
        for (auto pair : matrix[v]) {
            this->matrix[v][pair.first] = other.matrix[v][pair.first];
        }
    }
}

template<typename T>
MatrixGraph<T>::~MatrixGraph() {
    if (this->valueIsNotEmpty()) {
        this->clearValue();
    }
}

template<typename T>
void MatrixGraph<T>::addEdge(const int32_t& from, const int32_t& to,T element) {
    const int32_t currentSize = this->matrix.size();
    const int32_t maxVertex = std::max(from, to);
    if (maxVertex >= currentSize) {
        this->matrix.resize(maxVertex + 1);
    }
    matrix[from][to] = element;
}

template<typename T>
int MatrixGraph<T>::verticesCount() {
    const int32_t size = this->matrix.size();
    std::map<int32_t, bool> used;
    for (int32_t v = 0; v < size; v++) {
        for (auto pair : matrix[v]) {
            used[pair.first] = true;
        }
    }
    return used.size();
}

template<typename T>
void MatrixGraph<T>::getNextVertices(const int32_t& vertex, std::vector<int32_t> &vertices) {
    if (vertex >= this->matrix.size()) {
        return;
    }
    const int32_t size = this->matrix.size();
    for (auto pair : matrix[vertex]) {
        vertices.push_back(pair.first);
    }
}

template<typename T>
void MatrixGraph<T>::getPrevVertices(const int32_t& vertex, std::vector<int32_t> &vertices) {
    if (vertex >= this->matrix.size()) {
        return;
    }
    const int32_t size = this->matrix.size();
    for (int32_t v = 0; v < size; v++) {
        for (auto pair : matrix[v]) {
            if (pair.first == vertex) {
                vertices.push_back(v);
            }
        }
    }
}

template<typename T>
void MatrixGraph<T>::deepFirstSearch(const int32_t& vertex, std::vector<int32_t> &vertices) {
    ListGraph<T>* listGraphCopy = GraphConverter::createListGraphFromMatrixGraph(this);
    listGraphCopy->deepFirstSearch(vertex, vertices);
    delete listGraphCopy;
}

template<typename T>
void MatrixGraph<T>::breadthFirstSearch(const int32_t& vertex, std::vector<int32_t> &vertices) {
    ListGraph<T>* listGraphCopy = GraphConverter::createListGraphFromMatrixGraph(this);
    listGraphCopy->breadthFirstSearch(vertex, vertices);
    delete listGraphCopy;
}

template<typename T>
std::vector<std::map<int32_t, T>> MatrixGraph<T>::getMatrix() const noexcept {
    return this->matrix;
}

template<typename T>
void MatrixGraph<T>::clearValue() {
}

template<typename T>
bool MatrixGraph<T>::valueIsEmpty() const noexcept {
    return !this->valueIsNotEmpty();
}

template<typename T>
bool MatrixGraph<T>::valueIsNotEmpty() const noexcept {
    return false;
}

template<typename T>
MatrixGraph<T>* MatrixGraph<T>::getCopy() const noexcept {
    MatrixGraph<T>* copy = new MatrixGraph();
    const int32_t size = this->matrix.size();
    for (int32_t v = 0; v < size; v++) {
        for (auto pair : matrix[v]) {
            copy->matrix[v][pair.first] = pair.second;
        }
    }
    return copy;
}