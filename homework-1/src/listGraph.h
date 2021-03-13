
#ifndef HOMEWORK_1_LISTGRAPH_H
#define HOMEWORK_1_LISTGRAPH_H

#include "../graph.h"

template<typename T>
class ListGraph : public IGraph<T> {
public:
    virtual void AddEdge(int from, int to, T &&element) 
    {
        listg[from].push_back({to, element});
        _size.insert(from);
        _size.insert(to);
    };

    ListGraph() {};

    ListGraph(IGraph<T> *_oth) {
        std::vector<std::vector<std::pair<bool, T>>> matrixg;
        std::unordered_map<int, int> bnum;
        _oth->givegraph(matrixg, bnum);
        this->getgraph(matrixg, bnum);
    };

    virtual void getgraph(std::vector<std::vector<std::pair<bool, T>>> &matrixg,
     std::unordered_map<int, int> &bnum){
         for(int i = 0; i < matrixg.size(); i++){
             for(int j = 0; j < matrixg.size(); j++){
                 if (matrixg[i][j].first){
                    listg[bnum[i]].push_back({bnum[j], matrixg[i][j].second});
                 }
             }
             _size.insert(bnum[i]);
         }
     };

    virtual void givegraph(std::vector<std::vector<std::pair<bool, T>>> &matrixg,
     std::unordered_map<int, int> &bnum){
         int k = 0;
         std::unordered_map<int, int> bnum1;
         for(auto i : _size){
            bnum1[i] = k;
            bnum[k] = i;
            k++;
         }
         matrixg.resize(_size.size());
         for(int i = 0; i < _size.size(); i++){
             matrixg[i].resize(_size.size());
         }
         for(auto [key, val]: listg){
             for(auto j: val){
                 matrixg[bnum1[key]][bnum1[j.first]] = {true, j.second};
             }
         }
     };

    virtual int VerticesCount() const { 
        return _size.size();
    };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        for(auto i : listg.at(vertex)){
            vertices.push_back(i.first);
        }
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        for(auto [key, val]: listg){
             for(auto j: val){
                 if (j.first == vertex){
                    vertices.push_back(key);
                 }
             }
         }
    };

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
        std::unordered_map<int, bool> used;
        for(auto i : _size){
            used[i] = false;
        }   
        dfs(vertex, vertices, used);
    };

    virtual void BreadthFirstSearch(int s, std::vector<int> &vertices) const {
        std::queue<int> q;
        q.push (s);
        std::unordered_map<int, bool> used;
        for(auto i:_size){
            used[i] = false;
        }
        used[s] = true;
        while (!q.empty()) {
            int v = q.front();
            vertices.push_back(v);
            q.pop();
            if (listg.contains(v)){
                for (int i=0; i<listg.at(v).size(); ++i) {
                    int to = listg.at(v)[i].first;
                    if (!used[to]) {
                        used[to] = true;
                        q.push (to);
                    }
                }
            }
        }
    };

    void dfs(int v, std::vector<int> &vertices, std::unordered_map<int, bool> &used) const{
        used[v] = true;
        vertices.push_back(v);
        if (listg.contains(v))
            for (auto [i, j]: listg.at(v))
                if (!used[i])
                    dfs(i, vertices, used);
    };
    
private:
    std::unordered_map<int, std::vector<std::pair<int, T>>> listg;
    std::set<int> _size;
};


#endif //HOMEWORK_1_LISTGRAPH_H
