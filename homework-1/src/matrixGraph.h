
#ifndef HOMEWORK_1_MATRIXGRAPH_H
#define HOMEWORK_1_MATRIXGRAPH_H


#include "../graph.h"
#include <stack>
#include <queue>
#include <utility>

template<typename T = void>
class MatrixGraph : public IGraph<T> {
public:
    void AddEdge(int from, int to, T &&element) override {
        
        int max = std::max(from, to);
        
        if (matrix.size() <= max)
        {
            Resize(max+1);
        }

        matrix[from][to] = std::pair<bool, T>(true, std::forward<T>(element));
    
    };

    void Resize(int size) {

        for (int i = 0; i < matrix.size(); i++) {
            matrix[i].resize(size, std::pair<bool, T>(false, T()) );
        }

        matrix.resize(size, std::vector< std::pair<bool, T> >(size, std::pair<bool, T>(false, T()) ));
    }

    MatrixGraph() : matrix(std::vector<std::vector<std::pair<bool,T>>>()) { }

    MatrixGraph(IGraph<T>* _oth) {
    
        for (std::tuple<int, int, T> tuple : _oth->__get_all_edges__()) {
            this->AddEdge(std::get<0>(tuple), std::get<1>(tuple), std::move(std::get<2>(tuple)));
        }
    };


    int VerticesCount() const override { return matrix.size(); };

    void GetNextVertices(int vertex, std::vector<int> &vertices) const override {
        
        for (size_t i = 0; i < matrix.size(); i++) {

            if (matrix[vertex][i].first) {
                vertices.push_back(i);
            }
        }
    };

    void GetPrevVertices(int vertex, std::vector<int>& vertices) const override {

        for (size_t i = 0; i < matrix.size(); i++) {

            if (matrix[i][vertex].first) {
                vertices.push_back(i);
            }
        }
    };

    void DeepFirstSearch(int vertex, std::vector<int> &vertices) const override {
        
        std::stack<int> stack;
        std::set<int> used;
        used.insert(vertex);
        vertices.push_back(vertex);
        stack.push(vertex);

        while (stack.size())
        {
            int current = stack.top();
            stack.pop();

            for (size_t i = 0; i < matrix.size(); i++) {

                if (matrix[current][i].first && used.insert(i).second) {
                    vertices.emplace_back(i);
                    stack.push(i);
                }
            }
        }
    };

    void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const override {

        std::queue<int> queue;
        std::set<int> used;
        used.insert(vertex);
        vertices.push_back(vertex);
        queue.push(vertex);

        while (queue.size())
        {
            int current = queue.front();
            queue.pop();

            for (size_t i = 0; i < matrix.size(); i++) {

                if (matrix[current][i].first && used.insert(i).second) {
                    vertices.emplace_back(i);
                    queue.push(i);
                }
            }
        }
    };

    std::vector<std::tuple<int, int, T>> __get_all_edges__() const override {

        std::vector<std::tuple<int, int, T>> result;
        
        for (size_t i = 0; i < this->VerticesCount(); i++) {

            for (size_t j = 0; j < this->VerticesCount(); j++) {

                if (matrix[i][j].first) {
                    result.push_back({ i, j, matrix[i][j].second });
                }
            }
        }

        return result;
    }

private: 
    std::vector<std::vector< std::pair<bool,T> >> matrix;
};

#endif //HOMEWORK_1_MATRIXGRAPH_H
