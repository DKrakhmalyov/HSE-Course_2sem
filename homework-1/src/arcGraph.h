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
    std :: vector<std :: pair<int, std :: pair<int, T> > > arc_graph;
    bool was_vertex(int vertex) {
        for(int i = 0; i < arc_graph.size(); i++) {
            if(arc_graph[i].first == vertex) {
                return true;
            }
            if(arc_graph[i].second.first == vertex) {
                return true;
            }
        }
        return false;
    }
public:

    virtual void AddEdge(int from, int to, T &&element) {
        if(was_vertex(from)) {
            counter++;
        }
        if(was_vertex(to)) {
            counter++;
        }
        arc_graph.push_back(std :: make_pair(from, std :: make_pair(to, element)));
    };

    ArcGraph() {
        counter = 0;
    };

    ArcGraph(IGraph<T> *_oth) {
        _oth->Convert(this);
    }

    virtual int VerticesCount() const { return counter; };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        for(int i = 0; i < arc_graph.size(); i++) {
            if(arc_graph[i].first == vertex) {
                vertices.push_back(arc_graph[i].second.first);
            }
        }
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        for(int i = 0; i < arc_graph.size(); i++) {
            if(arc_graph[i].second.first == vertex) {
                vertices.push_back(arc_graph[i].first);
            }
        }
    };

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
        vertices.push_back(vertex);
        for(int i = 0; i < arc_graph.size(); i++) {
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

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
        std :: queue<int> q;
        q.push(vertex);
        vertices.push_back(vertex);
        while(q.size() != 0) {
            vertex = q.front();
            q.pop();
            for(int i = 0; i < arc_graph.size(); i++) {
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

    virtual void Convert(IGraph<T> *Gr)  {
        for(int i = 0; i < arc_graph.size(); i++) {
            Gr->AddEdge(arc_graph[i].first, arc_graph[i].second.first, std :: forward<T>(arc_graph[i].second.second));
        }
    };
};

#endif //HOMEWORK_1_ARCGRAPH_H
