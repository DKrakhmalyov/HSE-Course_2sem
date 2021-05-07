#ifndef HOMEWORK_1_GRAPH_TRAVELER_H
#define HOMEWORK_1_GRAPH_TRAVELER_H

#include "../graph.h"
#include <unordered_set>
#include <deque>

template<typename T, typename Vertex, typename GraphType>
class GraphTraveler {
public:
    explicit GraphTraveler(GraphType *graph) : graph(graph) {}

    virtual void DeepFirstSearch(Vertex vertex, std::vector<Vertex>& vertices) {
        usedVertices.clear();
        DeepFirstSearchInternal(vertex, vertices);
    }

    virtual void BreadthFirstSearch(Vertex vertex, std::vector<Vertex>& vertices) {
        usedVertices.clear();

        std::deque<Vertex> q;
        q.push_back(vertex);
        while (!q.empty()) {
            Vertex curVertex = q.front();
            q.pop_front();
            if (usedVertices.find(curVertex) == usedVertices.end()) {
                usedVertices.insert(curVertex);
                vertices.push_back(curVertex);
            }
            std::vector<Vertex> nextVertices;
            graph->GetNextVertices(curVertex, nextVertices);
            for (Vertex nextVertex:nextVertices) {
                q.push_back(nextVertex);
            }
        }
    }

private:
    GraphType *graph;
    std::unordered_set<Vertex> usedVertices;

    void DeepFirstSearchInternal(Vertex vertex, std::vector<Vertex>& vertices) {
        usedVertices.insert(vertex);
        vertices.push_back(vertex);
        std::vector<Vertex> nextVertices;
        graph->GetNextVertices(vertex, nextVertices);
        for (Vertex nextVertex:nextVertices) {
            if (usedVertices.find(nextVertex) == usedVertices.end()) {
                DeepFirstSearchInternal(nextVertex, vertices);
            }
        }
    }
};

#endif //HOMEWORK_1_GRAPH_TRAVELER_H