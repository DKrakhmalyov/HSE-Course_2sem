#pragma once

#include <memory>

template <typename EdgeCostType>
class IGraphBuilder {
 public:
  virtual void Init() = 0;
  virtual void AddEdge(int vertex, int to, EdgeCostType&& edge_cost) = 0;
  virtual ~IGraphBuilder() = default;
};

template <typename GraphType>
class ConcreteGraphBuilder
    : public IGraphBuilder<typename GraphType::EdgeCostType> {
 public:
  void Init() override { m_graph = std::make_unique<GraphType>(); }

  void AddEdge(int vertex, int to,
               typename GraphType::EdgeCostType&& edge_cost) override {
    m_graph->AddEdge(vertex, to, std::move(edge_cost));
  }

  std::unique_ptr<GraphType> Build() {
    if (!m_graph) {
      throw std::domain_error(
          "Cannot build: Builder is not initialized. Call Init() first");
    }
    return std::move(m_graph);
  }

  ~ConcreteGraphBuilder() override {
    if (m_graph) {
      m_graph.reset();
    }
  }

 protected:
  std::unique_ptr<GraphType> m_graph;
};
