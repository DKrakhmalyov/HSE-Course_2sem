
#ifndef HOMEWORK_1_MATRIXGRAPH_H
#define HOMEWORK_1_MATRIXGRAPH_H


#include "../graph.h"

template<typename T = void>
class MatrixGraph : public IGraph<T> {
public:
    virtual void AddEdge(int from, int to, T &&element) {
    if (!num.contains(from)){
        matrixg.resize(matrixg.size()+1);
        for(int i = 0; i < matrixg.size(); i++){
            matrixg[i].resize(matrixg.size());
        }
        num[from]=matrixg.size()-1;
        bnum[matrixg.size()-1] = from;
    }
    if (!num.contains(to)){
        matrixg.resize(matrixg.size()+1);
        for(int i = 0; i < matrixg.size(); i++){
            matrixg[i].resize(matrixg.size());
        }
        num[to]=matrixg.size()-1;
        bnum[matrixg.size()-1] = to;
    }
    matrixg[num[from]][num[to]] = {true, element};
    };

    MatrixGraph() {};

    MatrixGraph(IGraph<T> *_oth) {
        std::vector<std::vector<std::pair<bool, T>>> matrixg;
        std::unordered_map<int, int> bnum;
        _oth->givegraph(matrixg, bnum);
        this->getgraph(matrixg, bnum);
    };

    virtual void getgraph(std::vector<std::vector<std::pair<bool, T>>> &matrixg1,
     std::unordered_map<int, int> &bnum1){
         matrixg = matrixg1;
         bnum = bnum1;
        for(auto [key, val]: bnum){
            num[val]=key;
        }
     };

    virtual void givegraph(std::vector<std::vector<std::pair<bool, T>>> &matrixg1,
     std::unordered_map<int, int> &bnum1){
        matrixg1 = matrixg;
        bnum1 = bnum;
     };

    virtual int VerticesCount() const {
        return num.size();
    };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        for(int i = 0; i < matrixg[num.at(vertex)].size(); i++){
            if (matrixg[num.at(vertex)][i].first){
                vertices.push_back(bnum.at(i));
            }
        }
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        for(int i = 0; i < matrixg.size(); i++){
            if (matrixg[i][num.at(vertex)].first){
                vertices.push_back(bnum.at(i));
            }
        }
    };

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
        std::unordered_map<int, bool> used;
        for(auto [key, val]: num){
            used[key] = false;
        }
        dfs(vertex, vertices, used);
    };

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
        int s = num.at(vertex);
        std::queue<int> q;
        q.push (s);
        std::vector<bool> used (matrixg.size());
        used[s] = true;
        while (!q.empty()) {
            int v = q.front();
            vertices.push_back(bnum.at(v));
            q.pop();
            for (size_t i=0; i<matrixg.size(); ++i) {
                if (!used[i] && matrixg[v][i].first) {
                    used[i] = true;
                    q.push(i);
                }
            }
        }
    };

    void dfs(int v, std::vector<int> &vertices, std::unordered_map<int, bool> &used) const {
        used[v] = true;
        vertices.push_back(v);
        for (int i = 0; i < matrixg.size(); i++)
            if (!used.at(bnum.at(i)) && matrixg[num.at(v)][i].first)
                dfs (bnum.at(i), vertices, used);
    };

private:
    std::vector<std::vector<std::pair<bool, T>>> matrixg;
    std::unordered_map<int, int> num, bnum;
};

#endif //HOMEWORK_1_MATRIXGRAPH_H
