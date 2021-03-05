
#ifndef HOMEWORK_1_MATRIXGRAPH_H
#define HOMEWORK_1_MATRIXGRAPH_H

#include "../graph.h"

template <typename T = void>
class MatrixGraph : public IGraph<T> {
 public:
  MatrixGraph(unsigned int vertices_count)
      : m_cost(vertices_count, std::vector<std::vector<T>>(vertices_count)),
        m_edges_count(vertices_count, std::vector<int>(vertices_count)),
        m_size(vertices_count) {}

  MatrixGraph(IGraph<T> *other) {
    MatrixGraphBuilder builder(other->VerticesCount());
    other->BuildCopy(builder);
    auto ptr = builder.Build().release();
    MatrixGraph(std::move(*ptr));
    delete ptr;
  };

  MatrixGraph(MatrixGraph &&other)
      : m_cost(std::move(other.m_cost)),
        m_edges_count(std::move(other.m_edges_count)),
        m_size(other.m_size) {}

  void AddEdge(int from, int to, T &&element) override {
    if (from < 0 || to < 0 || from >= m_size || to >= m_size) {
      throw std::out_of_range("Graph has size " + std::to_string(m_size) + "x" +
                              std::to_string(m_size));
    }
    m_cost[from][to].push_back(element);
    m_edges_count[from][to]++;
  };

  int VerticesCount() const override { return m_size; }

  void GetNextVertices(int vertex, std::vector<int> &vertices) const override {
    vertices.clear();
    for (int i = 0; i < m_size; ++i) {
      for (int k = 0; k < m_edges_count[vertex][i]; ++k) {
        vertices.push_back(i);
      }
    }
  };

  void GetPrevVertices(int vertex, std::vector<int> &vertices) const override {
    vertices.clear();
    for (int i = 0; i < m_size; ++i) {
      for (int k = 0; k < m_edges_count[i][vertex]; ++k) {
        vertices.push_back(i);
      }
    }
  };

  void BuildCopy(IGraphBuilder<T> &builder) override {
    builder.Init();
    for (int i = 0; i < m_size; ++i) {
      for (int j = 0; j < m_size; ++j) {
        for (int k = 0; k < m_edges_count[i][j]; ++k) {
          builder.AddEdge(i, j, T(m_cost[i][j][k]));
        }
      }
    }
  }

 private:
  class MatrixGraphBuilder : public IGraphBuilder<T> {
   public:
    MatrixGraphBuilder(int size) : m_size(size) {}

    void Init() override { m_graph = std::make_unique<MatrixGraph>(m_size); }

    void AddEdge(int from, int to, T &&cost) override {
      m_graph->AddEdge(from, to, std::move(cost));
    }

    std::unique_ptr<MatrixGraph> Build() {
      if (!m_graph) {
        throw std::domain_error(
            "Cannot build: Builder is not initialized. Call Init() first");
      }
      return std::move(m_graph);
    }

   private:
    std::unique_ptr<MatrixGraph> m_graph;
    int m_size;
  };

 private:
  std::vector<std::vector<std::vector<T>>> m_cost;
  std::vector<std::vector<int>> m_edges_count;
  unsigned int m_size;
};

#endif  // HOMEWORK_1_MATRIXGRAPH_H
