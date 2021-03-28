
#ifndef HOMEWORK_1_LISTGRAPH_H
#define HOMEWORK_1_LISTGRAPH_H

#include <map>
#include <list>
#include <vector>
#include <memory>
#include <utility>
#include "../graph.h"


template<typename T>
class ListGraph : public IGraph<T> {
 public:
  ListGraph() = default;
  ~ListGraph() override = default;

  ListGraph(IGraph<T> *_oth) {
    this->simple_copy_build(_oth);
  };
  
  virtual void AddEdge(int from, int to, T &&element) override {
    edges_[from].emplace_back(to, std::forward<T>(element));
    // check if "to" is existing node
    if (edges_.find(to) == edges_.end())
      edges_.emplace(to, std::list<std::pair<int, T>> {});
  };

  virtual void GetEdges(std::vector<std::tuple<int, int, T>>& edges) const {
    for (auto &node : edges_)
      for (auto &list_node : node.second)
        edges.emplace_back(node.first, list_node.first, list_node.second);
  };

  virtual int VerticesCount() const override {
    return edges_.size();
  };

  virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const override {
    if (auto node = edges_.find(vertex); node != edges_.end())
      for (auto &name : node->second)
        vertices.push_back(name.first);
  };

  virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const override {
    for (auto &node : edges_)
      for (auto &list_node : node.second)
        if (list_node.first == vertex)
          vertices.push_back(node.first);
  };

 protected:
  std::map<int, std::list<std::pair<int, T>>> edges_;
};


#endif //HOMEWORK_1_LISTGRAPH_H
