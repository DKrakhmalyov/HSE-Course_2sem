
#ifndef HOMEWORK_1_PTRSGRAPH_H
#define HOMEWORK_1_PTRSGRAPH_H

#include "node.h"
#include "../graph.h"

template<typename T = void>
class PtrsGraph : public IPtrsGraph<T> {
public:

    PtrsGraph() = default;    

    virtual ~PtrsGraph() = default;

    PtrsGraph(const PtrsGraph<T> &other) = default;

    PtrsGraph(PtrsGraph<T> &&other) = default;

    PtrsGraph<T>& operator=(const PtrsGraph<T> &other) {
        if (this != &other) {
            have = other.have;
        }
        return *this;
    }

    PtrsGraph<T>& operator=(PtrsGraph<T> &&other) {
        if (this != &other) {
            have = std::move(other.have);
        }
        return *this;
    }

    virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) override final {
        AddVertex(from);
        AddVertex(to);
        from->toList.push_back(std::make_pair(to, _obj));
        to->fromList.push_back(std::make_pair(from, _obj));
    }

    virtual int VerticesCount() const override final { 
        return static_cast<int>(have.size());
    }

    virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const override final {
        vertices.clear();
        for (auto to: vertex->toList) {
            vertices.push_back(to.first);
        }
    }

    virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const override final {
        vertices.clear();
        for (auto from: vertex->fromList) {
            vertices.push_back(from.first);
        }
    }

    virtual void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const override final {
        vertices.clear();
        if (have.find(vertex) == have.end()) {
            return;
        }
        std::unordered_map<Node<T>*, bool> used;
        std::function<void(Node<T>*)> dfs = [&](Node<T> *current) {
            used[current] = true;
            vertices.push_back(current);
            for (auto to: current->toList) {
                if (!used[to.first]) {
                    dfs(to.first);
                }
            }
        };
        dfs(vertex);
    }

    virtual void BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const override final {
        vertices.clear();
        if (have.find(vertex) == have.end()) {
            return;
        }
        std::unordered_map<Node<T>*, bool> used;
        std::queue<Node<T>*, std::list<Node<T>*>> bfs;
        used[vertex] = true;
        bfs.push(vertex);
        while (!bfs.empty()) {
            auto current = bfs.front();
            bfs.pop();
            vertices.push_back(current);
            for (auto to: current->toList) {
                if (used[to.first]) {
                    continue;
                }
                used[to.first] = true;
                bfs.push(to.first);
            }
        }
    }

private:

    std::unordered_set<Node<T>*> have;

    void AddVertex(Node<T> *vertex) {
        if (have.find(vertex) != have.end()) {
            return;
        }
        have.insert(vertex);
    }
};

#endif //HOMEWORK_1_PTRSGRAPH_H
