
#ifndef HOMEWORK_1_ARCGRAPH_H
#define HOMEWORK_1_ARCGRAPH_H

#include "../graph.h"
#include <stack>
#include <queue>

template<typename T = void>
class ArcGraph : public IGraph<T> {
public:
    void AddEdge(int from, int to, T&& element) override {
        pairs.emplace_back(from, to, element);
        max_pair_elem = std::max(max_pair_elem, std::max(from, to));
    };

    ArcGraph() : max_pair_elem(0), pairs(std::vector<std::tuple<int,int,T>>()) {};

    ArcGraph(IGraph<T>* _oth) { 
        for (std::tuple<int, int, T> tuple : _oth->__get_all_edges__()) {
            this->AddEdge(std::get<0>(tuple), std::get<1>(tuple), std::move(std::get<2>(tuple)));
        }
    };

    int VerticesCount() const override { return max_pair_elem; };

    void GetNextVertices(int vertex, std::vector<int>& vertices) const override { 
        
        for (std::tuple<int, int, T> tuple : pairs)
        {
            if (std::get<0>(tuple) == vertex) {
                vertices.push_back(std::get<1>(tuple));
            }
        }
    };

    void GetPrevVertices(int vertex, std::vector<int>& vertices) const override {

        for (std::tuple<int, int, T> tuple : pairs)
        {
            if (std::get<1>(tuple) == vertex) {
                vertices.push_back(std::get<0>(tuple));
            }
        }
    };

    void DeepFirstSearch(int vertex, std::vector<int>& vertices) const override {

        std::stack<int> stack;
        std::set<int> used;
        used.insert(vertex);
        vertices.push_back(vertex);
        stack.push(vertex);

        while (stack.size())
        {
            int current = stack.top();
            stack.pop();

            std::vector<int> nexts;
            this->GetNextVertices(current, nexts);

            for (int vert : nexts) {

                if (used.insert(vert).second) {
                    vertices.emplace_back(vert);
                    stack.push(vert);
                }
            }
        }
    };

    void BreadthFirstSearch(int vertex, std::vector<int>& vertices) const override {
    
        std::queue<int> queue;
        std::set<int> used;
        used.insert(vertex);
        vertices.push_back(vertex);
        queue.push(vertex);

        while (queue.size())
        {
            int current = queue.front();
            queue.pop();

            std::vector<int> nexts;
            this->GetNextVertices(current, nexts);

            for (int vert : nexts) {

                if (used.insert(vert).second) {
                    vertices.emplace_back(vert);
                    queue.push(vert);
                }
            }
        }
    };

    std::vector<std::tuple<int, int, T>> __get_all_edges__() const override {
        return pairs;
    }

private: 
    std::vector<std::tuple<int, int, T>> pairs;
    int max_pair_elem;
};

#endif //HOMEWORK_1_ARCGRAPH_H
