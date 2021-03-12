
#ifndef HOMEWORK_1_PTRSGRAPH_H
#define HOMEWORK_1_PTRSGRAPH_H

#include "node.h"
#include "../graph.h"

template<typename T = void>
class PtrsGraph : public IPtrsGraph<T> {
public:
	virtual void AddEdge(Node<T> *from, Node<T> *to, T &&weight) {
		verts.insert(from);
		verts.insert(to);
		from->AddEdge(to, std::forward<T>(weight));
	};

    PtrsGraph() {};

	virtual int VerticesCount() const {
		return verts.size();
	};

	virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
		vertices = vertex->GetEdges();
	};

	virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
		for (auto vert : verts) {
			for (auto edge : vert->GetEdges()) {
				if (edge == vertex) {
					vertices.push_back(vert);
				}
			}
		}
	};

private:
	std::unordered_set<Node<T> *> verts;
};

#endif //HOMEWORK_1_PTRSGRAPH_H
