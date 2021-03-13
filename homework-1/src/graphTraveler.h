#ifndef HOMEWORK_1_GRAPH_TRAVELER_H
#define HOMEWORK_1_GRAPH_TRAVELER_H

#include "../graph.h"
#include <unordered_set>
#include <deque>

template<typename T>
class GraphTraveler {
public:
    explicit GraphTraveler(IGraph<T> *graph) : graph(graph) {}

    virtual void DeepFirstSearch(int vertex, std::vector<int>& vertices) {
        usedVertices.clear();
        DeepFirstSearchInternal(vertex, vertices);
    }

    virtual void BreadthFirstSearch(int vertex, std::vector<int>& vertices) {
        usedVertices.clear();

        std::deque<int> q;
        q.push_back(vertex);
        while (!q.empty()) {
            int curVertex = q.front();
            q.pop_front();
            if (usedVertices.find(curVertex) == usedVertices.end()) {
                usedVertices.insert(curVertex);
                vertices.push_back(curVertex);
            }
            std::vector<int> nextVertices;
            graph->GetNextVertices(curVertex, nextVertices);
            for (int nextVertex:nextVertices) {
                q.push_back(nextVertex);
            }
        }
    }

private:
    IGraph<T> *graph;
    std::unordered_set<int> usedVertices;

    void DeepFirstSearchInternal(int vertex, std::vector<int>& vertices) {
        usedVertices.insert(vertex);
        vertices.push_back(vertex);
        std::vector<int> nextVertices;
        graph->GetNextVertices(vertex, nextVertices);
        for (int nextVertex:nextVertices) {
            if (usedVertices.find(nextVertex) == usedVertices.end()) {
                DeepFirstSearchInternal(nextVertex, vertices);
            }
        }
    }
};

#endif //HOMEWORK_1_GRAPH_TRAVELER_H