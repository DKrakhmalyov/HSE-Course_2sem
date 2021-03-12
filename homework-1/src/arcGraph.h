
#ifndef HOMEWORK_1_ARCGRAPH_H
#define HOMEWORK_1_ARCGRAPH_H

#include "../graph.h"

template<typename T = void>
class ArcGraph : public IGraph<T> {
public:
    virtual void AddEdge(int from, int to, T &&element) {
		graph.emplace_back(from, to, std::forward<T>(element));
		verts.insert(from);
		verts.insert(to);
	};

    ArcGraph() {};

    ArcGraph(IGraph<T> *_oth) {};

	virtual int VerticesCount() const {
		return verts.size();
	};

	virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
		for (auto &[i, j, k] : graph) {
			if (i == vertex) {
				vertices.push_back(j);
			}
		}
	};

	virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
		for (auto &[i, j, k] : graph) {
			if (j == vertex) {
				vertices.push_back(i);
			}
		}
	};

	std::vector<int> GetVerts() const {
		return std::vector<int>(verts.begin(), verts.end());
	}

	T GetEdge(int from, int to) const {
		for (auto &[i, j, k] : graph) {
			if (from == i && to == j) {
				return k;
			}
		}
	}

private:
	std::unordered_set<int> verts;
	std::vector<std::tuple<int, int, T>> graph;
};

#endif //HOMEWORK_1_ARCGRAPH_H
