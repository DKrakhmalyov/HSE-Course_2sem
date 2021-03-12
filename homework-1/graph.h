
#ifndef HOMEWORK_1_GRAPH_H
#define HOMEWORK_1_GRAPH_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <queue>
#include <utility>
#include <algorithm>
#include "src/node.h"

template<typename T>
class IGraph {
public:
    virtual ~IGraph() {}

    IGraph() {};

	IGraph(IGraph<T> *_oth) {
		for (auto from : _oth->GetVerts()) {
			std::vector<int> next_verts;
			_oth->GetNextVertices(from, next_verts);
			for (auto to : next_verts) {
				AddEdge(from, to, _oth->GetEdge);
			}
		}
	};

    virtual void AddEdge(int from, int to, T &&_obj) = 0;

    virtual int VerticesCount() const = 0;

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const = 0;

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const = 0;

	virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
		std::unordered_set<int> used;
		dfs(vertex, vertices, used);
	};

	virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
		std::queue<int> q;
		std::unordered_set<int> used;
		q.push(vertex);
		while (q.size() > 0) {
			int curr = q.front();
			q.pop();

			used.insert(curr);
			vertices.push_back(curr);

			std::vector<int> next;
			GetNextVertices(curr, next);

			for (auto it : next)
				if (!used.contains(it))
					q.push(it);
		}
	};

	virtual std::vector<int> GetVerts() const = 0;

	virtual T GetEdge(int from, int to) const = 0;

private:
	virtual void dfs(int vertex, std::vector<int> &vertices, std::unordered_set<int> &used) const {
		vertices.push_back(vertex);
		used.insert(vertex);

		std::vector<int> next;
		GetNextVertices(vertex, next);

		for (auto it : next)
			if (!used.contains(it))
				dfs(it, vertices, used);
	};
};

template<typename T = void>
class IPtrsGraph {
public:
    virtual ~IPtrsGraph() {}

    IPtrsGraph() {};

    virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) = 0;

    virtual int VerticesCount() const = 0;

    virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const = 0;

    virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const = 0;

	virtual void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
		std::unordered_set<Node<T> *> used;
		dfs(vertex, vertices, used);
	};

	virtual void BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
		std::queue<Node<T> *> q;
		std::unordered_set<Node<T> *> used;
		q.push(vertex);
		while (q.size() > 0) {
			Node<T> * curr = q.front();
			q.pop();

			used.insert(curr);
			vertices.push_back(curr);

			std::vector<Node<T> *> next;
			GetNextVertices(curr, next);

			for (auto it : next)
				if (!used.contains(it))
					q.push(it);
		}
	};
private:
	virtual void dfs(Node<T> *vertex, std::vector<Node<T> *> &vertices, std::unordered_set<Node<T> *> &used) const {
		vertices.push_back(vertex);
		used.insert(vertex);

		std::vector<Node<T> *> next;
		GetNextVertices(vertex, next);

		for (auto it : next)
			if (!used.contains(it))
				dfs(it, vertices, used);
	};
};

#endif //HOMEWORK_1_GRAPH_H
