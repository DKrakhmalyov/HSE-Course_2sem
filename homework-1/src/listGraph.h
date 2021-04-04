//
// Created by dikson on 02.03.2021.
//

#ifndef HOMEWORK_1_LISTGRAPH_H
#define HOMEWORK_1_LISTGRAPH_H

#include "../graph.h"
#include <map>
#include <vector>
#include <set>


template<typename T = void>
class ListGraph : public IGraph<T> {
private:
    std::map<int, std::vector<std :: pair<int, T> > > list_graph;
    std::set<int> all_vertices;
public:
    virtual void AddEdge(int from, int to, T&& _obj);

    ListGraph();

    ListGraph(IGraph<T>* _oth);

    ~ListGraph();

    virtual int VerticesCount() const;

    virtual void GetNextVertices(int vertex, std::vector<int>& vertices);

    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices);

    virtual void DeepFirstSearch(int vertex, std::vector<int>& vertices);

    virtual void BreadthFirstSearch(int vertex, std::vector<int>& vertices);

    virtual void CopyEdges(std::vector<std::pair<int, std::pair<int, T> > >& edges);
};


template<typename T>
void ListGraph<T>::AddEdge(int from, int to, T&& element) {
    list_graph[from].push_back(std::make_pair(to, element));
    all_vertices.insert(from);
    all_vertices.insert(to);
};

template<typename T>
ListGraph<T>::ListGraph() {};

template<typename T>
ListGraph<T>::ListGraph(IGraph<T>* _oth) {
    std::vector<std::pair<int, std::pair<int, T> > > edgescopy;
    _oth->CopyEdges(edgescopy);
    for (int i = 0; i < edgescopy.size(); i++) {
        this->AddEdge(edgescopy[i].first, edgescopy[i].second.first, std::forward<T>(const_cast<T&>(edgescopy[i].second.second)));
    }
};

template<typename T>
ListGraph<T>::~ListGraph() {
    all_vertices.clear();
    list_graph.clear();
};

template<typename T>
int ListGraph<T>::VerticesCount() const { 
    return all_vertices.size();
};

template<typename T>
void ListGraph<T>::GetNextVertices(int vertex, std::vector<int>& vertices) {
    for (int i = 0; i < list_graph[vertex].size(); i++) {
        vertices.push_back(list_graph[vertex][i].first);
    }
};

template<typename T>
void ListGraph<T>::GetPrevVertices(int vertex, std::vector<int>& vertices) {
    for (auto it : all_vertices) {
        for (int i = 0; i < list_graph[it].size(); i++) {
            if (list_graph[it][i].first == vertex) {
                vertices.push_back(it);
            }
        }
    }
};

template<typename T>
void ListGraph<T>::DeepFirstSearch(int vertex, std::vector<int>& vertices) {
    vertices.push_back(vertex);
    for (int i = 0; i < list_graph[vertex].size(); i++) {
        bool was_vertex = false;
        for (int j = 0; j < vertices.size(); j++) {
            if (vertices[j] == list_graph[vertex][i].first) {
                was_vertex = true;
                break;
            }
        }
        if (!was_vertex) {
            DeepFirstSearch(list_graph[vertex][i].first, vertices);
        }
    }
};

template<typename T>
void ListGraph<T>::BreadthFirstSearch(int vertex, std::vector<int>& vertices) {
    std::queue<int> q;
    q.push(vertex);
    while (q.size() != 0) {
        int v = q.front();
        q.pop();
        vertices.push_back(v);
        for (int i = 0; i < list_graph[v].size(); i++) {
            bool was_vertex = false;
            for (int j = 0; j < vertices.size(); j++) {
                if (vertices[j] == list_graph[v][i].first) {
                    was_vertex = true;
                    break;
                }
            }
            if (!was_vertex) {
                q.push(list_graph[v][i].first);
            }
        }
    }
};

template<typename T>
void ListGraph<T>::CopyEdges(std::vector<std::pair<int, std::pair<int, T> > >& edges) {
   for (auto it : list_graph) {
       for (int i = 0; i < it.second.size(); i++) {
           edges.push_back(std::make_pair(it.first, std::make_pair(it.second[i].first, it.second[i].second)));
       }
   }
};
#endif //HOMEWORK_1_LISTGRAPH_H
