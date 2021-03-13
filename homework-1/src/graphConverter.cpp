#include "graphConverter.h"

template<typename T>
bool GraphConverter::isArcGraph(IGraph<T>* graph) noexcept {
    ArcGraph<T>* arcGraph = dynamic_cast<ArcGraph<T>*>(graph);
    return arcGraph != nullptr;
}

template<typename T>
bool GraphConverter::isListGraph(IGraph<T>* graph) noexcept {
    ListGraph<T>* listGraph = dynamic_cast<ListGraph<T>*>(graph);
    return listGraph != nullptr;
}

template<typename T>
bool GraphConverter::isMatrixGraph(IGraph<T>* graph) noexcept {
    MatrixGraph<T>* matrixGraph = dynamic_cast<MatrixGraph<T>*>(graph);
    return matrixGraph != nullptr;
}

template<typename T>
ListGraph<T>* GraphConverter::toListGraph(IGraph<T>* graph) {
    if (!GraphConverter::isListGraph(graph)) {
        throw std::invalid_argument("Can't convert no list graph to list graph. Use checkers to check what type of graph is!");
    }
    ListGraph<T>* resultGraph = dynamic_cast<ListGraph<T>*>(graph);
    return resultGraph;
}

template<typename T>
ArcGraph<T>* GraphConverter::toArcGraph(IGraph<T>* graph) {
    if (!GraphConverter::isArcGraph(graph)) {
        throw std::invalid_argument("Can't convert no arc graph to arc graph. Use checkers to check what type of graph is!");
    }
    ArcGraph<T>* resultGraph = dynamic_cast<ArcGraph<T>*>(graph);
    return resultGraph;
}

template<typename T>
MatrixGraph<T>* GraphConverter::toMatrixGraph(IGraph<T>* graph) {
    if (!GraphConverter::isMatrixGraph(graph)) {
        throw std::invalid_argument("Can't convert no matrix graph to matrix graph. Use checkers to check what type of graph is!");
    }
    MatrixGraph<T>* resultGraph = dynamic_cast<MatrixGraph<T>*>(graph);
    return resultGraph;
}

template<typename T>
ArcGraph<T>* GraphConverter::createArcGraphFromListGraph(ListGraph<T>* listGraph) {
    ArcGraph<T>* base = GraphConverter::createBaseFromListGraph(listGraph);
    return base;
}

template<typename T>
ArcGraph<T>* GraphConverter::createArcGraphFromMatrixGraph(MatrixGraph<T>* matrixGraph) {
    ArcGraph<T>* base = GraphConverter::createBaseFromMatrixGraph(matrixGraph);
    return base;
}

template<typename T>
ListGraph<T>* GraphConverter::createListGraphFromArcGraph(ArcGraph<T>* arcGraph) {
    ArcGraph<T>* base = new ArcGraph<T>(*arcGraph);
    return GraphConverter::convertBaseToListGraph(base);
}

template<typename T>
ListGraph<T>* GraphConverter::createListGraphFromMatrixGraph(MatrixGraph<T>* matrixGraph) {
    ArcGraph<T>* base = GraphConverter::createBaseFromMatrixGraph(matrixGraph);
    return GraphConverter::convertBaseToListGraph(base);
}

template<typename T>
MatrixGraph<T>* GraphConverter::createMatrixGraphFromListGraph(ListGraph<T>* listGraph) {
    ArcGraph<T>* base = GraphConverter::createBaseFromListGraph(listGraph);
    return GraphConverter::convertBaseToMatrixGraph(base);
}

template<typename T>
MatrixGraph<T>* GraphConverter::createMatrixGraphFromArcGraph(ArcGraph<T>* arcGraph) {
    ArcGraph<T>* base = new ArcGraph<T>(*arcGraph);
    return GraphConverter::convertBaseToMatrixGraph(base);
}

template<typename T>
ArcGraph<T>* GraphConverter::createBaseFromListGraph(ListGraph<T>* listGraph) {
    std::vector<std::vector<std::pair<int32_t, T*>>> edges = listGraph->getListOfEdges();
    const int32_t size = edges.size();
    ArcGraph<T>* resultGraph = new ArcGraph<T>();
    for (int32_t v = 0; v < size; v++) {
        for (const std::pair<int32_t, T*> pair : edges[v]) {
            resultGraph->addEdge(v, pair.first, *pair.second);
        }
    }
    return resultGraph;
}

template<typename T>
ArcGraph<T>* GraphConverter::createBaseFromMatrixGraph(MatrixGraph<T>* matrixGraph) {
    std::vector<std::map<int32_t, T>> edges = matrixGraph->getMatrix();
    const int32_t size = edges.size();
    ArcGraph<T>* resultGraph = new ArcGraph<T>();
    for (int32_t v = 0; v < size; v++) {
        for (auto pair : edges[v]) {
            resultGraph->addEdge(v, pair.first, pair.second);
        }
    } 
    return resultGraph;
}

template<typename T>
ListGraph<T>* GraphConverter::convertBaseToListGraph(ArcGraph<T>* base) {
    std::vector<NodePair<T>*> edges = base->getListOfEdges();
    const int32_t size = edges.size();
    ListGraph<T>* resultGraph = new ListGraph<T>();
    for (const NodePair<T>* edge : edges) {
        resultGraph->addEdge(edge->getFirstNode(), edge->getSecondNode(), edge->getWeight());
    }
    return resultGraph;
}

template<typename T>
MatrixGraph<T>* GraphConverter::convertBaseToMatrixGraph(ArcGraph<T>* base) {
    std::vector<NodePair<T>*> edges = base->getListOfEdges();
    const int32_t size = edges.size();
    MatrixGraph<T>* resultGraph = new MatrixGraph<T>();
    for (const NodePair<T>* edge : edges) {
        resultGraph->addEdge(edge->getFirstNode(), edge->getSecondNode(), edge->getWeight());
    }
    return resultGraph;
}