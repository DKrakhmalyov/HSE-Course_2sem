
#ifndef HOMEWORK_1_MATRIXGRAPH_H
#define HOMEWORK_1_MATRIXGRAPH_H


#include "../graph.h"

template<typename T = void>
class MatrixGraph : public IGraph<T> {
public:
	virtual void AddEdge(int from, int to, T &&element) {
		graph[from][to] = std::move(element);
		verts.insert(from);
		verts.insert(to);
	};

	MatrixGraph() {};

	MatrixGraph(IGraph<T> *_oth) {};

	virtual int VerticesCount() const {
		return verts.size();
	};

	virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
		auto it = graph.find(vertex);
		if (it != graph.end()) {
			for (auto const &[a, b] : it->second) {
				vertices.push_back(a);
			}
		}
		return;
	};

	virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
		for (auto const &[a, b] : graph) {
			if (b.find(vertex) != b.end()) {
				vertices.push_back(a);
			}
		}
	};

	std::vector<int> GetVerts() const {
		return std::vector<int>(verts.begin(), verts.end());
	}

	T GetEdge(int from, int to) const {
		return graph.at(from).at(to);
	}

private:
	std::unordered_set<int> verts;
	std::unordered_map<int, std::unordered_map<int, T>> graph;
};
#endif //HOMEWORK_1_MATRIXGRAPH_H
