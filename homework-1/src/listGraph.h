
#ifndef HOMEWORK_1_LISTGRAPH_H
#define HOMEWORK_1_LISTGRAPH_H

#include "../graph.h"
#include <vector>
#include <map>
#include <queue>

template<typename T>
class ListGraph : public IGraph<T> {
public:
    virtual void AddEdge(int from, int to, T &&element) {
        if (!private_number[from]) {
            ++vc;
            public_number[vc] = from;
            private_number[from] = vc;
            graph.push_back(std::vector <std::pair <int, T> > ());
        }
        if (!private_number[to]) {
            ++vc;
            public_number[vc] = to;
            private_number[to] = vc;
            graph.push_back(std::vector <std::pair <int, T> > ());
        }
        graph[private_number[from]].push_back({private_number[to], element});
    };

    ListGraph() {
        graph.push_back(std::vector <std::pair <int, T> > ());
    };

    ListGraph(IGraph<T> *_oth) {
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

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {       
        int v = prnumber(vertex);
        for (int i = 0; i < graph[v].size(); ++i) {
            vertices.push_back(pubnumber(graph[v][i]).first);
        }
    };
    int prnumber (int v) {
        return private_number[v];
    }
    int pubnumber (int v) {
        return public_number[v];
    }
    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        int v = prnumber(vertex);
        for (int i = 1; i <= vc; ++i) {
            for (int j = 0; j < graph[v].size(); ++j) {
                if (graph[i][j] == v)
                    vertices.push_back(pubnumber(i));
            }
        }
    }

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

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {  
        std::queue <int> waiting;
        std::vector <int> visited(vc + 1);
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
        T inf = m.second;
        std::vector <std::vector <T> > matrix = m.first;
        matrix.resize(vc, std::vector <T> (vc, inf));
        for (int i = 0; i < graph.size(); ++i) {
            for (int j = 0; j < graph[i].size(); ++j) {
                matrix[i][graph[i][j].first] = graph[i][j].second;
            }
        }
        m = {matrix, inf};
    }

private:
    std::vector< std::vector < std::pair <int, T> > > graph;
    std::map <int, int> private_number, public_number;
    int vc = 0;
};


#endif //HOMEWORK_1_LISTGRAPH_H
