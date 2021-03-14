
#ifndef HOMEWORK_1_MATRIXGRAPH_H
#define HOMEWORK_1_MATRIXGRAPH_H

#include "../graph.h"
#include <vector>
#include <map>
#include <queue> 

template<typename T = void>
class MatrixGraph : public IGraph<T> {
public:
    virtual void AddEdge(int from, int to, T &&element) {
        if (!private_number[from]) {
            ++vc;
            public_number[vc] = from;
            private_number[from] = vc;
            for(int i = 0; i < vc - 1; ++i) 
                graph[i].push_back(inf);
            graph.push_back(std::vector <int> (vc, inf));
        }
        if (!private_number[to]) {
            ++vc;
            public_number[vc] = to;
            private_number[to] = vc;
            for(int i = 0; i < vc - 1; ++i) 
                graph[i].push_back(inf);
            graph.push_back(std::vector <int> (vc, inf));
        }
        graph[private_number[from]][private_number[to]] = element;
    };

    MatrixGraph() {
        graph.push_back(std::vector <T> (1, inf));
    };
    MatrixGraph(IGraph<T> *_oth) {
        std::pair <std::vector < std::vector<T> >, T > m;
        _oth->ToMatrixGraph(m);
        T inf = m.second;
        std::vector < std::vector <T> > matrix = m.first;
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix.size(); ++j) {
                if (matrix[i][j] != inf)
                    AddEdge(i, j, matrix[i][j]);
            }
        }
    };

    virtual int VerticesCount() const { return vc; };

    int prnumber (int v) {
        return private_number[v];
    }
    int pubnumber (int v) {
        return public_number[v];
    }

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        int v = prnumber(vertex);
        for (int i = 1; i <= vc; ++i) {
            if (graph[v][i] != inf)
                vertices.push_back(pubnumber(i));
        }
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        int v = prnumber(vertex);
        for (int i = 1; i <= vc; ++i) {
            if (graph[i][v] != inf)
                vertices.push_back(pubnumber(i));
        }
    };

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
        std::vector <int> waiting, visited(vc + 1);
        waiting.push_back(prnumber(vertex));

        while(!waiting.empty()) {
            int cur = waiting.back();
            vertices.push_back(pubnumber(cur));
            visited[cur] = true;
            waiting.pop_back();
            std::vector <int> next;
            GetNextVertices(pubnumber(cur), next);
            for (int i = 0; i < next.size(); ++i) {
                if (visited[prnumber(next[i])])
                    continue;
                waiting.push_back(prnumber(next[i]));
            }
        }
    };

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) {  
        std::queue <int> waiting;
        std::vector <int> visited(vc + 1, 0);
        waiting.push(prnumber(vertex));

        while(!waiting.empty()) {
            int cur = waiting.front();
            vertices.push_back(pubnumber(cur));
            visited[cur] = true;
            waiting.pop();
            std::vector <int> next;
            GetNextVertices(pubnumber(cur), next);
            for (int i = 0; i < next.size(); ++i) {
                if (visited[prnumber(next[i])])
                    continue;
                waiting.push(prnumber(next[i]));
            }
        }
    };
    virtual void ToMatrixGraph(std::pair< std::vector <std::vector <T> >, T> & m) {
        m = {graph, inf};
    }
    

private:
    T inf;
    std::vector< std::vector <T> > graph;
    std::map <int, int> private_number, public_number;
    int vc = 0;
};

#endif //HOMEWORK_1_MATRIXGRAPH_H
