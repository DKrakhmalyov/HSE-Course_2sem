
#ifndef HOMEWORK_1_ARCGRAPH_H
#define HOMEWORK_1_ARCGRAPH_H

#include "../graph.h"

template<typename T = void>
class ArcGraph : public IGraph<T> {
private:

    std::vector<std::pair<int, int>> pairs;
    std::map<std::pair<int, int>, T> weight;
    std::unordered_set<int> existingV;

public:
    virtual T getWeightOf(int from, int to) {
        return weight[std::make_pair(from, to)];
    };

    virtual void AddEdge(int from, int to, T &&element) {
        pairs.push_back(std::make_pair(from, to));
        weight[pairs.back()] = element;
        existingV.insert(from);
        existingV.insert(to);
    };
    virtual void GetEdges(std::vector<std::pair<int, int>> v) {
        for (auto x: pairs) {
            v.push_back(std::make_pair(x.first, x.second));
            
        }
    };

    ArcGraph() {};

    ArcGraph(IGraph<T> *_oth) {};

    virtual int VerticesCount() const { return existingV.size(); };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        for (auto x: pairs) {
            if (x.first == vertex) {
                vertices.push_back(x.second);
            }
        }
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        for (auto x: pairs) {
            if (x.second == vertex) {
                vertices.push_back(x.first);
            }
        }
    };

};

#endif //HOMEWORK_1_ARCGRAPH_H
