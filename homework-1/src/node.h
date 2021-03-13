
#ifndef HOMEWORK_1_NODE_H
#define HOMEWORK_1_NODE_H

template<typename T>
class Node {
public:
    void AddEdge(Node<T> *to, T &&_obj) {
        tops.push_back({to, _obj});
    };
    void AddEdgeb(Node<T> *to, T &&_obj) {
        topsb.push_back({to, _obj});
    };
    void GetNextVertices(std::vector<Node<T> *> &vertices){
        for(auto i : tops){
            vertices.push_back(i.first);
        }
    };
    void GetPrevVertices(std::vector<Node<T> *> &vertices){
        for(auto i : topsb){
            vertices.push_back(i.first);
        }
    };
    Node<T>* getobj(int i){
        return tops[i].first;
    }
    void dfs(std::vector<Node<T>*> &vertices, std::unordered_map<Node<T>*, bool> &used) {
        used[this] = true;
        vertices.push_back(this);
        for (int i = 0; i < tops.size(); i++)
            if (!used[tops[i].first])
                tops[i].first->dfs(vertices, used);
    };
    void bfs(std::vector<Node<T>*> &vertices, std::unordered_map<Node<T>*, bool> &used, std::queue<Node<T>*> &q){
        q.push(this);
        used[this] = true;
        while (!q.empty()) {
            Node* v = q.front();
            q.pop();
            vertices.push_back(v);
            for (int i=0; i<v->tops.size(); ++i) {
                Node* to = v->tops[i].first;
                if (!used[to]) {
                    used[to] = true;
                    q.push (to);
                }
            }
        }
    };
private:
    std::vector<std::pair<Node<T>*, T>> tops, topsb;
};

#endif //HOMEWORK_1_NODE_H
