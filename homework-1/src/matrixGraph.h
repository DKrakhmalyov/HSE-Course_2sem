//
// Created by dikson on 02.03.2021.
//

#ifndef HOMEWORK_1_MATRIXGRAPH_H
#define HOMEWORK_1_MATRIXGRAPH_H


#include "../graph.h"
#include <map>
#include <set>

using namespace std;

template<typename T = void>
class MatrixGraph : public IGraph<T> {
private:
    std::map<int, std::map<int, T> > matrix_graph;
    std::set<int> all_vertices;
public:
    virtual void AddEdge(int from, int to, T&& element);

    MatrixGraph();

    MatrixGraph(IGraph<T>* _oth);

    ~MatrixGraph();

    virtual int VerticesCount() const;

    virtual void GetNextVertices(int vertex, std::vector<int>& vertices);

    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices);

    virtual void DeepFirstSearch(int vertex, std::vector<int>& vertices);

    virtual void BreadthFirstSearch(int vertex, std::vector<int>& vertices);

    virtual void CopyEdges(std::vector<std::pair<int, std::pair<int, T> > >& edges);
};

template<typename T>
void MatrixGraph<T>::AddEdge(int from, int to, T&& element) {
    all_vertices.insert(from);
    all_vertices.insert(to);
    const_cast<T&>(matrix_graph[from][to]) = element;
}

template<typename T>
MatrixGraph<T>::MatrixGraph() {
}

template<typename T>
MatrixGraph<T>::MatrixGraph(IGraph<T>* _oth) {
    std::vector<std::pair<int, std::pair<int, T> > > edgescopy;
    _oth->CopyEdges(edgescopy);
    for (int i = 0; i < edgescopy.size(); i++) {
        T for_copy = edgescopy[i].second.second;
        this->AddEdge(edgescopy[i].first, edgescopy[i].second.first, std :: forward<T>(const_cast<T&>(for_copy)));
    }
};

template<typename T>
MatrixGraph<T>::~MatrixGraph() {
    matrix_graph.clear();
    all_vertices.clear();
};

template<typename T>
int MatrixGraph<T>::VerticesCount() const {
    return all_vertices.size();
};

template<typename T>
void MatrixGraph<T>::GetNextVertices(int vertex, std::vector<int>& vertices) {
    for (auto it : matrix_graph[vertex]) {
        vertices.push_back(it.first);
    }
};

template<typename T>
void MatrixGraph<T>::GetPrevVertices(int vertex, std::vector<int>& vertices) {
    for (auto it : matrix_graph) {
        for (auto it2 : matrix_graph[it.first]) {
            if (it2.first == vertex) {
                vertices.push_back(it.first);
            }
        }
    }
}

template<typename T>
void MatrixGraph<T>::DeepFirstSearch(int vertex, std::vector<int>& vertices) {
    vertices.push_back(vertex);
    for (auto it : matrix_graph[vertex]) {
        bool was_vertex = false;
        for (int i = 0; i < vertices.size() && !was_vertex; i++) {
            if (vertices[i] == it.first) {
                was_vertex = true;
            }
        }
        if (!was_vertex) {
            DeepFirstSearch(it.first, vertices);
        }
    }
};

template<typename T>
void MatrixGraph<T>::BreadthFirstSearch(int vertex, std::vector<int>& vertices) {
    std::queue<int> q;
    q.push(vertex);
    while (q.size() != 0) {
        int v = q.front();
        vertices.push_back(v);
        q.pop();
        for (auto it : matrix_graph[v]) {
            bool was_vertex = false;
            for (int i = 0; i < vertices.size() && !was_vertex; i++) {
                if (vertices[i] == it.first) {
                    was_vertex = true;
                }
            }
            if (!was_vertex) {
                q.push(it.first);
            }
        }
    }
};

template<typename T>
void MatrixGraph<T>::CopyEdges(std :: vector<std :: pair<int, std :: pair<int, T> > > &edges) {
    for (auto it : matrix_graph) {
        for (auto it2 : matrix_graph[it.first]) {
            edges.push_back(std::make_pair(it.first, std::make_pair(it2.first, it2.second)));
        }
    }
};

#endif //HOMEWORK_1_MATRIXGRAPH_H
