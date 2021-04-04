//
// Created by dikson on 02.03.2021.
//

#ifndef HOMEWORK_1_ARCGRAPH_H
#define HOMEWORK_1_ARCGRAPH_H

#include "../graph.h"


template<typename T = void>
class ArcGraph : public IGraph<T> {
private:
    int counter_vertices = 0;
    int counter_edges = 0;
    std :: vector<std::pair<int, std::pair<int, T> > > arc_graph;
    bool was_vertex(const int vertex) const;
public:
    virtual void AddEdge(int from, int to, T&& element);

    ArcGraph();

    ArcGraph(IGraph<T>* _oth);

    virtual int VerticesCount() const;

    virtual void GetNextVertices(int vertex, std::vector<int>& vertices);

    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices);

    virtual void DeepFirstSearch(int vertex, std::vector<int>& vertices);

    virtual void BreadthFirstSearch(int vertex, std::vector<int>& vertices);

    virtual void CopyEdges(std::vector<std::pair<int, std::pair<int, T> > >& edges);
};

template<typename T>
void ArcGraph<T>::AddEdge(int from, int to, T&& element) {
    if (!was_vertex(from)) {
        counter_vertices++;
    }
    if (!was_vertex(to)) {
        counter_vertices++;
    }
    arc_graph.push_back(std::make_pair(from, std::make_pair(to, element)));
    counter_edges++;
};

template<typename T>
bool ArcGraph<T>::was_vertex(const int vertex) const {
    for (int i = 0; i < counter_edges; i++) {
        if (arc_graph[i].first == vertex) {
            return true;
        }
        if (arc_graph[i].second.first == vertex) {
            return true;
        }
    }
    return false;
}

template<typename T>
ArcGraph<T>::ArcGraph() {
    counter_vertices = 0;
    counter_edges = 0;
};

template<typename T>
ArcGraph<T>::ArcGraph(IGraph<T>* _oth) {
    counter_vertices = 0;
    counter_edges = 0;
    std::vector<std::pair<int, std::pair<int, T> > > edgescopy;
    _oth->CopyEdges(edgescopy);
    for (int i = 0; i < edgescopy.size(); i++) {
        this->AddEdge(edgescopy[i].first, edgescopy[i].second.first, std::forward<T>(const_cast<T&>(edgescopy[i].second.second)));
    }
}

template<typename T>
void ArcGraph<T>::GetNextVertices(int vertex, std::vector<int>& vertices) {
    for (int i = 0; i < counter_edges; i++) {
        if (arc_graph[i].first == vertex) {
            vertices.push_back(arc_graph[i].second.first);
        }
    }
};

template<typename T>
void ArcGraph<T>::GetPrevVertices(int vertex, std::vector<int>& vertices){
    for (int i = 0; i < counter_edges; i++) {
        if (arc_graph[i].second.first == vertex) {
            vertices.push_back(arc_graph[i].first);
        }
    }
};

template<typename T>
int ArcGraph<T>::VerticesCount() const { return counter_vertices; };

template<typename T>
void ArcGraph<T>::DeepFirstSearch(int vertex, std::vector<int>& vertices) {
    vertices.push_back(vertex);
    for (int i = 0; i < counter_edges; i++) {
        if (arc_graph[i].first == vertex) {
            bool used = false;
            for (int j = 0; j < vertices.size(); j++) {
                if (vertices[j] == arc_graph[i].second.first) {
                    used = true;
                }
            }
            if (!used) {
                DeepFirstSearch(arc_graph[i].second.first, vertices);
            }
        }
    }
};

template<typename T>
void ArcGraph<T>::BreadthFirstSearch(int vertex, std::vector<int>& vertices) {
    std::queue<int> q;
    q.push(vertex);
    vertices.push_back(vertex);
    while (q.size() != 0) {
        vertex = q.front();
        q.pop();
        for (int i = 0; i < counter_edges; i++) {
            if (arc_graph[i].first == vertex) {
                bool used = false;
                for (int j = 0; j < vertices.size(); j++) {
                    if (arc_graph[i].second.first == vertices[j]) {
                        used = true;
                    }
                }
                if (!used) {
                    q.push(arc_graph[i].second.first);
                    vertices.push_back(arc_graph[i].second.first);
                }
            }
        }
    }
};

template<typename T>
void ArcGraph<T>::CopyEdges(std::vector<std::pair<int, std::pair<int, T> > >& edges) {
    for (int i = 0; i < counter_edges; i++) {
        edges.push_back(std::make_pair(arc_graph[i].first, std::make_pair(arc_graph[i].second.first, 
            arc_graph[i].second.second)));
    }
};
#endif //HOMEWORK_1_ARCGRAPH_H
