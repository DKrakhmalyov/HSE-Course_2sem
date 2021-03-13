
#ifndef HOMEWORK_1_ARCGRAPH_H
#define HOMEWORK_1_ARCGRAPH_H

#include "../graph.h"

template<typename T = void>
class ArcGraph : public IGraph<T> {
public:
    ArcGraph() {};

    ArcGraph(IGraph<T> *_oth) {
        std::vector<std::vector<std::pair<bool, T>>> matrixg;
        std::unordered_map<int, int> bnum;
        _oth->givegraph(matrixg, bnum);
        this->getgraph(matrixg, bnum);
    };
    
    virtual void AddEdge(int from, int to, T &&element) 
    {
        arcg.push_back({from, to, element});
        _size.insert(from);
        _size.insert(to);
    };

    virtual void getgraph(std::vector<std::vector<std::pair<bool, T>>> &matrixg, std::unordered_map<int, int> &bnum)
    {
        arcg.resize(0);
        _size.clear();
        for(int i = 0; i < matrixg.size(); i++){
            for(int j = 0; j < matrixg[i].size(); j++){
                if (matrixg[i][j].first == true){
                    arcg.push_back({bnum[i], bnum[j], matrixg[i][j].second});
                    _size.insert(bnum[i]);
                    _size.insert(bnum[j]);
                }
            }
        }
    };

    virtual void givegraph(std::vector<std::vector<std::pair<bool, T>>> &matrixg, std::unordered_map<int, int> &bnum)
    {
        matrixg.resize(_size.size());
        for(int i = 0; i < _size.size(); i++){
            matrixg[i].resize(_size.size());
        }
        std::unordered_map<int, int> num;
        int k = 0;
        for(auto i = _size.cbegin(); i != _size.cend(); ++i) {
            bnum[k] = *i;
            num[*i] = k;
            k++;
        }
        for(auto i : arcg){
            matrixg[num[i.p]][num[i.n]] = {true, i.el};
        }
    };

    virtual int VerticesCount() const { 
        return _size.size();
    };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        for(auto i : arcg){
            if (i.p == vertex){
                vertices.push_back(i.n);
            }
        }
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        for(auto i : arcg){
            if (i.n == vertex){
                vertices.push_back(i.p);
            }
        }
    };

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
        std::unordered_map<int, bool> used;
        for(auto i: _size){
            used[i] = false;
        }
        dfs(vertex, vertices, used);
    };

    virtual void BreadthFirstSearch(int s, std::vector<int> &vertices) const {
        std::queue<int> q;
        q.push (s);
        std::unordered_map<int, bool> used;
        for(auto i : _size){
            used[i] = false;
        }
        used[s] = true;
        while (!q.empty()) {
            int v = q.front();
            vertices.push_back(v);
            q.pop();
            for(auto i: arcg){
                if (i.p == v && !used.at(i.n)) {
                    used.at(i.n) = true;
                    q.push (i.n);
                }
            }
        }
    };

    void dfs(int v, std::vector<int> &vertices, std::unordered_map<int, bool> &used) const {
        used[v] = true;
        vertices.push_back(v);
        for (int i = 0; i < arcg.size(); i++)
            if (!used[arcg[i].n] && (arcg[i].p == v))
                dfs(arcg[i].n, vertices, used);
    };

    private:
        struct high
        {
            int p;
            int n;
            T el;
        };
        std::vector<high> arcg;
        std::set<int> _size;
};

#endif //HOMEWORK_1_ARCGRAPH_H
