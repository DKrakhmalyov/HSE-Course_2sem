
#ifndef HOMEWORK_1_LISTGRAPH_H
#define HOMEWORK_1_LISTGRAPH_H

#include "../graph.h"

#include <map>
#include <list>
#include <memory>
#include <utility>


template<typename T>
class ListGraph : public IGraph<T> {
 public:
  virtual void AddEdge(int from, int to, T &&element) override {
    edges[from].emplace_back(to, std::forward<T>(element));
    // check if "to" is existing node
    if (edges.find(to) == edges.end())
      edges.emplace(to, std::list<std::pair<int, T>> {});
  };

  ListGraph() = default;
  ~ListGraph() override = default;

  ListGraph(IGraph<T> *_oth) {};

  virtual int VerticesCount() const override {
    return edges.size();
  };

  virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const override {
    if (auto node = edges.find(vertex); node != edges.end())
      for (auto &name : node->second)
        vertices.push_back(name.first);
  };

  virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const override {
    for (auto &node : edges)
      for (auto &list_node : node.second)
        if (list_node.first == vertex)
          vertices.push_back(node.first);
  };

 private:
  std::map<int, std::list<std::pair<int, T>>> edges;
};


#endif //HOMEWORK_1_LISTGRAPH_H
