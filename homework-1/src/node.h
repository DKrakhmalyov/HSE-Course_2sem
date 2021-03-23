
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
    void dfs(std::vector<Node<T>*> &vertices, std::vector<bool> &used) {
        used[this->num()] = true;
        vertices.push_back(this);
        for (int i = 0; i < tops.size(); i++)
            if (!used[tops[i].first->num()])
                tops[i].first->dfs(vertices, used);
    };
    void bfs(std::vector<Node<T>*> &vertices, std::vector<bool> &used, std::queue<Node<T>*> &q){
        q.push(this);
        used[this->num()] = true;
        while (!q.empty()) {
            Node* v = q.front();
            q.pop();
            vertices.push_back(v);
            for (int i=0; i<v->tops.size(); ++i) {
                Node* to = v->tops[i].first;
                if (!used[to->num()]) {
                    used[to->num()] = true;
                    q.push (to);
                }
            }
        }
    };
    void reflag(){
        flagm = !flagm;
    }
    bool flag(){
        return flagm;
    }
    void renum(int a){
        numm = a;
    }
    int num(){
        return numm;
    }
private:
    std::vector<std::pair<Node<T>*, T>> tops, topsb;
    bool flagm = false;
    int numm = -1;
};

#endif //HOMEWORK_1_NODE_H
