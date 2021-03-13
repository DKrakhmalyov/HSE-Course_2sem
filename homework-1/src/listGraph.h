
#ifndef HOMEWORK_1_LISTGRAPH_H
#define HOMEWORK_1_LISTGRAPH_H

#include "../graph.h"


template<typename T>
class ListGraph : public IGraph<T> {

private:
    std::map<int, std::vector<std::pair<int, T>>> lists;
    std::unordered_set<int> existingV;

public:
    virtual void getWeightOf(int from, int to, T& var) {
        for (auto x: lists[from]) {
            if (x.first == to) {
                var = x.second;
            }
        }
    };
    virtual void AddEdge(int from, int to, T &&element) {
        existingV.insert(from);
        existingV.insert(to);
        lists[from].push_back(std::make_pair(to, element));
    };
    virtual void GetEdges(std::vector<std::pair<int, int>> &v) {
        for (auto x: lists) {
            for (auto y: lists[x.first]) {
                v.push_back(std::make_pair(x.first, y.first));
            }
        }
    };

    ListGraph() {};

    ListGraph(IGraph<T> *_oth) {};

    virtual int VerticesCount() const { return existingV.size(); };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        if (lists.count(vertex)) {
            for (int i = 0; i < lists.at(vertex).size(); i++) {
                vertices.push_back(lists.at(vertex)[i].first);
            }
        }
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        for (auto x: lists) {
            for (auto y: x.second) {
                if (y.first == vertex) {
                    vertices.push_back(x.first);
                    break;
                }
            }
        }
    };


};


#endif //HOMEWORK_1_LISTGRAPH_H
