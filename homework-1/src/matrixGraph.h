
#ifndef HOMEWORK_1_MATRIXGRAPH_H
#define HOMEWORK_1_MATRIXGRAPH_H

#include <algorithm>
#include <deque>
#include <vector>
#include <memory>
#include <utility>
#include "../graph.h"


template<typename T = void>
class MatrixGraph : public IGraph<T> {
 public:
  MatrixGraph() = default;
  ~MatrixGraph() override = default;

  MatrixGraph(IGraph<T> *_oth) {
    this->simple_copy_build(_oth);
  };

  virtual void AddEdge(int from, int to, T &&element) override {
    if (int max_vert = std::max(from, to) + 1; edges_matrix.size() < max_vert) {
      edges_matrix.resize(max_vert);
      for (auto &row : edges_matrix)
        row.resize(max_vert);
    }
    edges_matrix[from][to] = std::make_pair(true, std::forward<T>(element));;
  };

  virtual void GetEdges(std::vector<std::tuple<int, int, T>>& edges) const {
    for (int i = 0; i < edges_matrix.size(); ++i) 
      for (int j = 0; j < edges_matrix.size(); ++j) 
        if (edges_matrix[i][j].first) 
          edges.emplace_back(i, j, edges_matrix[i][j].second);
  };

  virtual int VerticesCount() const override {
    std::set<int> found_vertices;

    for (int i = 0; i < edges_matrix.size(); ++i) {
      for (int j = 0; j < edges_matrix.size(); ++j) {
        if (edges_matrix[i][j].first) {
          found_vertices.insert(i);
          found_vertices.insert(j);
        }
      }
    }

    return found_vertices.size();
  };

  virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const override {
    for (int to = 0; to < edges_matrix.size(); ++to)
      if (edges_matrix[vertex][to].first)
        vertices.push_back(to);
  };

  virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const override {
    for (int from = 0; from < edges_matrix.size(); ++from)
      if (edges_matrix[from][vertex].first)
        vertices.push_back(from);
  };

 protected:
  std::deque<std::deque<std::pair<bool, T>>> edges_matrix;
};

#endif //HOMEWORK_1_MATRIXGRAPH_H
