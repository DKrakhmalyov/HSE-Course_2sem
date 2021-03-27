
#ifndef HOMEWORK_1_ARCGRAPH_H
#define HOMEWORK_1_ARCGRAPH_H

#include "../graph.h"

template<typename T = void>
class ArcGraph : public IGraph<T> {
 public:
  virtual void AddEdge(int from, int to, T &&element) {
    edges.emplace_back(from, to, std::forward<T>(element));
  };

  ArcGraph() = default;
  ~ArcGraph() override = default;

  ArcGraph(IGraph<T> *_oth) {};

  virtual int VerticesCount() const {
    std::set<int> found_vertices;

    for (auto &edge : edges) {
      found_vertices.insert(std::get<0>(edge));
      found_vertices.insert(std::get<1>(edge));
    }

    return found_vertices.size();
  };

  virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
    for (auto &edge : edges) 
      if (std::get<0>(edge) == vertex)
        vertices.push_back(std::get<1>(edge));
  };

  virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
    for (auto &edge : edges) 
      if (std::get<1>(edge) == vertex)
        vertices.push_back(std::get<0>(edge));
  };

private:
  std::deque<std::tuple<int, int, T>> edges;
};

#endif //HOMEWORK_1_ARCGRAPH_H
