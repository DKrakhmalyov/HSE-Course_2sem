
#ifndef HOMEWORK_1_MATRIXGRAPH_H
#define HOMEWORK_1_MATRIXGRAPH_H

#include "../graph.h"
#include <queue>
#include <stack>

template<typename T = void>
class MatrixGraph : public IGraph<T> {
private:
  std::vector<std::vector<T>> matrix;

public:
  MatrixGraph() {}

  explicit MatrixGraph(IGraph<T> *oth) : IGraph<T>(oth) {
    if (oth == nullptr) return;

    for (int vtx = 0; vtx < oth->VerticesCount(); vtx++) {
      std::vector<int> adjacent;
      oth->GetNextVertices(vtx, adjacent);

      for (auto next: adjacent) {
        auto weightPointer = oth->GetWeight(vtx, next);
        if (weightPointer == nullptr) {
          throw std::logic_error(
              "Getting weight of the adjacent vtx " + std::to_string(next) + " of " + std::to_string(vtx) +
              " runs out with nullptr");
        }

        auto weight = *weightPointer;
        AddEdge(vtx, next, std::move(weight));
      }
    }
  }

  [[nodiscard]] int VerticesCount() const override {
    return matrix.size();
  }

  void GetNextVertices(int vertex, std::vector<int> &vertices) const override {
    if (vertex < 0 || vertex > matrix.size()) return;

    for (int i = 0; i < matrix[vertex].size(); i++) {
      if (matrix[vertex][i]) vertices.push_back(i);
    }
  }

  void GetPrevVertices(int vertex, std::vector<int> &vertices) const override {
    if (vertex < 0 || vertex > matrix.size()) return;

    for (int i = 0; i < matrix[vertex].size(); i++) {
      if (matrix[i][vertex]) vertices.push_back(i);
    }
  }

  void AddEdge(int from, int to, T &&element) override {
    if (from < 0 || to < 0) return;

    int maxVertexNumber = std::max(from, to);
    if (maxVertexNumber > matrix.size()) {
      matrix.resize(maxVertexNumber + 1);
      for (int i = 0; i < maxVertexNumber + 1; i++) matrix[i].resize(maxVertexNumber + 1);
    }

    matrix[from][to] = element;
  }

  const T *GetWeight(int from, int to) const override {
    if (from < 0 || from >= matrix.size()) return nullptr;
    if (to < 0 || to >= matrix.size()) return nullptr;

    return &matrix[from][to];
  }
};

#endif //HOMEWORK_1_MATRIXGRAPH_H
