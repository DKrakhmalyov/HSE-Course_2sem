
#ifndef HOMEWORK_1_LISTGRAPH_H
#define HOMEWORK_1_LISTGRAPH_H

#include "../graph.h"

template<typename T>
class ListGraph : public IGraph<T> {
public:
    virtual void AddEdge(int from, int to, T &&element) {
		graph[from].push_back({ to, std::forward<T>(element) });
		verts.insert(from);
		verts.insert(to);
	};

    ListGraph() {};

    ListGraph(IGraph<T> *_oth) {};

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
		for (auto &[a, b] : graph) {
			if (std::find_if(b.begin(), b.end(), [vertex](const std::pair<int, int> &i) { return i.first == vertex; }) != b.end()) {
				vertices.push_back(a);
			}
		}
	};

	virtual std::vector<int> GetVerts() const {
		return std::vector<int>(verts.begin(), verts.end());
	};

	virtual T GetEdge(int from, int to) const {
		return std::find_if(graph.at(from).begin(), graph.at(from).end(), [to](const std::pair<int, int> &i) { return i.first == to; })->second;
	}

private:
	std::unordered_set<int> verts;
	std::unordered_map<int, std::list<std::pair<int, int> > > graph;
};


#endif //HOMEWORK_1_LISTGRAPH_H
