
#ifndef HOMEWORK_1_NODE_H
#define HOMEWORK_1_NODE_H

#include <vector>

template<typename T>
class Node {
public:
	void AddEdge(Node<T> *node, T &&weight) {
		edges.push_back(node);
		edgeW.push_back(std::forward<T>(weight));
	}

	const std::vector<Node<T> *> &GetEdges() const {
		return edges;
	}

	bool operator==(const Node &rhs) const {
		return edges == rhs.edges && edgeW == rhs.edges;
	}

private:
	std::vector<T> edgeW;
	std::vector<Node<T> *> edges;
};

#endif //HOMEWORK_1_NODE_H
