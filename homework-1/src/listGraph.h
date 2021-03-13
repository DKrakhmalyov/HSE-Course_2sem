
#ifndef HOMEWORK_1_LISTGRAPH_H
#define HOMEWORK_1_LISTGRAPH_H

#include "../graph.h"
#include <list>
#include <stack>
#include <queue>

template<typename T>
class ListGraph : public IGraph<T> {
public:
    void AddEdge(int from, int to, T&& element) override {

        int max = std::max(from, to);

        if (list.size() <= max)
        {
            Resize(max + 1);
        }

        if (!CheckEdgeExist(from, to, element)) {
            list[from].push_back(std::pair<size_t, T>(to, std::forward<T>(element)));
        }

    };

    bool CheckEdgeExist(int from, int to, T cost)
    {
        for (std::pair<size_t, T> pair : list[from]) {
            
            if (pair.first == to && pair.second == cost) {
                return true;
            }
        }
        return false;
    }

    void Resize(int size) {
        list.resize(size, std::list < std::pair<size_t, T> >());
    }

    ListGraph() : list(std::vector< std::list<std::pair<size_t, T>> >()) {};

    ListGraph(IGraph<T>* _oth) {

        for (std::tuple<int, int, T> tuple : _oth->__get_all_edges__()) {
            this->AddEdge(std::get<0>(tuple), std::get<1>(tuple), std::move(std::get<2>(tuple)));
        }
    };

    int VerticesCount() const override { return list.size(); };

    void GetNextVertices(int vertex, std::vector<int>& vertices) const override {

        for (std::pair<size_t, T> pair : list[vertex]) {
            
            vertices.push_back(pair.first);
        }
    }

    void GetPrevVertices(int vertex, std::vector<int>& vertices) const override {
    
        for (size_t i = 0; i < list.size(); i++)
        {
            for (std::pair<size_t, T> pair : list[i]) {

                if (pair.first == vertex) {
                    vertices.push_back(i);
                }
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

            for (std::pair<size_t, T> pair : list[current]) {

                if (used.insert(pair.first).second) {
                    vertices.emplace_back(pair.first);
                    stack.push(pair.first);
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

            for (std::pair<size_t, T> pair : list[current]) {

                if (used.insert(pair.first).second) {
                    vertices.emplace_back(pair.first);
                    queue.push(pair.first);
                }
            }
        }
    
    };

    std::vector<std::tuple<int, int, T>> __get_all_edges__() const override  {

        std::vector<std::tuple<int, int, T>> result;

        for (size_t i = 0; i < this->VerticesCount(); i++) {

            for (std::pair<size_t, T> pair : list[i]) {
                
                result.push_back({ i, pair.first, pair.second });
            }
        }

        return result;
    }

private:
    std::vector < std::list<std::pair<size_t, T>> > list;
};


#endif //HOMEWORK_1_LISTGRAPH_H
