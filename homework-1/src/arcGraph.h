//
// Created by dikson on 02.03.2021.
//

#ifndef HOMEWORK_1_ARCGRAPH_H
#define HOMEWORK_1_ARCGRAPH_H

#include "../graph.h"


template<typename T = void>
class ArcGraph : public IGraph<T> {
private:
    int counter = 0;
    const static int max_size = 100000;
    int counter_edges = 0;
    std :: pair<int, std :: pair<int, T> > arc_graph[max_size];
    bool was_vertex(const int vertex) const;
public:
    virtual void AddEdge(int from, int to, T &&element) const;

    ArcGraph();

    ArcGraph(IGraph<T> *_oth);

    virtual int VerticesCount() const;

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const;

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const;

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const;

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const;

    virtual void Convert(IGraph<T> *Gr) const;
};

template<typename T>
void ArcGraph<T>::AddEdge(int from, int to, T &&element) const {
    if(!was_vertex(from)) {
        const_cast<int&>(counter)++;
    }
    if(!was_vertex(to)) {
        const_cast<int&>(counter)++;
    }
    const_cast<int&>(arc_graph[counter_edges].first) = from;
    const_cast<int&>(arc_graph[counter_edges].second.first) = to;
    const_cast<T&>(arc_graph[counter_edges].second.second) = element;
    const_cast<int&>(counter_edges)++;
};

template<typename T>
bool ArcGraph<T>::was_vertex(const int vertex) const {
    for(int i = 0; i < counter_edges; i++) {
        if(arc_graph[i].first == vertex) {
            return true;
        }
        if(arc_graph[i].second.first == vertex) {
            return true;
        }
    }
    return false;
}

template<typename T>
ArcGraph<T>::ArcGraph() {
    counter = 0;
    counter_edges = 0;
};

template<typename T>
ArcGraph<T>::ArcGraph(IGraph<T> *_oth) {
    counter = 0;
    counter_edges = 0;
    _oth->Convert(this);
}

template<typename T>
void ArcGraph<T>::GetNextVertices(int vertex, std::vector<int> &vertices) const {
    for(int i = 0; i < counter_edges; i++) {
        if(arc_graph[i].first == vertex) {
            vertices.push_back(arc_graph[i].second.first);
        }
    }
};

template<typename T>
void ArcGraph<T>::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
    for(int i = 0; i < counter_edges; i++) {
        if(arc_graph[i].second.first == vertex) {
            vertices.push_back(arc_graph[i].first);
        }
    }
};

template<typename T>
int ArcGraph<T>::VerticesCount() const { return counter; };

template<typename T>
void ArcGraph<T>::DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
    vertices.push_back(vertex);
    for(int i = 0; i < counter_edges; i++) {
        if(arc_graph[i].first == vertex) {
            bool used = false;
            for(int j = 0; j < vertices.size(); j++) {
                if(vertices[j] == arc_graph[i].second.first) {
                    used = true;
                }
            }
            if(!used) {
                DeepFirstSearch(arc_graph[i].second.first, vertices);
            }
        }
    }
};

template<typename T>
void ArcGraph<T>::BreadthFirstSearch(int vertex, std::vector<int> &vertices) const{
    std :: queue<int> q;
    q.push(vertex);
    vertices.push_back(vertex);
    while(q.size() != 0) {
        vertex = q.front();
        q.pop();
        for(int i = 0; i < counter_edges; i++) {
            if(arc_graph[i].first == vertex) {
                bool used = false;
                for(int j = 0; j < vertices.size(); j++) {
                    if(arc_graph[i].second.first == vertices[j]) {
                        used = true;
                    }
                }
                if(!used) {
                    q.push(arc_graph[i].second.first);
                    vertices.push_back(arc_graph[i].second.first);
                }
            }
        }
    }
};

template<typename T>
void ArcGraph<T>::Convert(IGraph<T> *Gr) const{
    for(int i = 0; i < counter_edges; i++) {
        const T xx = arc_graph[i].second.second;
        Gr->AddEdge(arc_graph[i].first, arc_graph[i].second.first, std :: forward<T>(const_cast<T&>(xx)));
    }
};
#endif //HOMEWORK_1_ARCGRAPH_H