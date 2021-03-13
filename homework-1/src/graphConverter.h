#include <vector>
#include "../graph.h"

#ifndef HOMEWORK_1_GRAPH_CONVERTER
#define HOMEWORK_1_GRAPH_CONVERTER

template<typename T, typename ResultGraphType>
class GraphConverter {
public:
    void convertTo(IGraph<T> *sourceGraph, ResultGraphType *resultGraph) {
        std::vector<int> sourceVertices;
        sourceGraph->GetAllVertices(sourceVertices);
        for (int sourceVertex : sourceVertices) {
            std::vector<int> nextVertexes;
            sourceGraph->GetNextVertices(sourceVertex, nextVertexes);
            for (int nextVertex : nextVertexes) {
                resultGraph->AddEdge(sourceVertex, nextVertex, sourceGraph->GetWeight(sourceVertex, nextVertex));
            }
        }
    }
};
#endif