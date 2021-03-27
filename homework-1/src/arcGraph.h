
#ifndef HOMEWORK_1_ARCGRAPH_H
#define HOMEWORK_1_ARCGRAPH_H

#include "../graph.h"
#include <deque>
#include <vector>
#include <memory>
#include <utility>


template<typename T = void>
class ArcGraph : public IGraph<T> {
 public:

  ArcGraph() = default;
  ~ArcGraph() override = default;

  ArcGraph(IGraph<T> *_oth) {
    std::vector<std::tuple<int, int, T>> edges;
    _oth->GetEdges(edges);
    for (auto edge : edges)
      AddEdge(std::get<0>(edge), std::get<1>(edge), std::move(std::get<2>(edge)));
  };

  virtual void AddEdge(int from, int to, T &&element) override {
    edges_.emplace_back(from, to, std::forward<T>(element));
  };

  virtual void GetEdges(std::vector<std::tuple<int, int, T>>& edges) const override {
    for (auto &edge : edges_)
      edges.push_back(edge);
  };

  virtual int VerticesCount() const override {
    std::set<int> found_vertices;

    for (auto &edge : edges_) {
      found_vertices.insert(std::get<0>(edge));
      found_vertices.insert(std::get<1>(edge));
    }

    return found_vertices.size();
  };

  virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const override {
    for (auto &edge : edges_) 
      if (std::get<0>(edge) == vertex)
        vertices.push_back(std::get<1>(edge));
  };

  virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const override {
    for (auto &edge : edges_) 
      if (std::get<1>(edge) == vertex)
        vertices.push_back(std::get<0>(edge));
  };

private:
  std::deque<std::tuple<int, int, T>> edges_;
};

#endif //HOMEWORK_1_ARCGRAPH_H
