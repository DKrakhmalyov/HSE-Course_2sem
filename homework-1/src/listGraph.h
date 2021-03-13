
#ifndef HOMEWORK_1_LISTGRAPH_H
#define HOMEWORK_1_LISTGRAPH_H

#include "../graph.h"


template<typename T>
class ListGraph : public IGraph<T> {
private:
  std::vector<std::map<int, T>> upwards;
  std::vector<std::map<int, T>> downwards;
  std::set<int> set;

public:
  void AddEdge(int from, int to, T &&element) override {
    if (upwards.size() <= from) upwards.resize(from + 1);
    if (downwards.size() <= to) downwards.resize(to + 1);

    upwards[from][to] = downwards[to][from] = element;
    set.insert(from);
    set.insert(to);
  };

  ListGraph() {};

  explicit ListGraph(IGraph<T> *oth) {
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

  [[nodiscard]] int VerticesCount() const override { return set.size(); };

  void GetNextVertices(int vertex, std::vector<int> &vertices) const override {
    if (vertex >= upwards.size()) return;
    for (const auto &data: upwards[vertex])
      vertices.push_back(data.first);
  };

  void GetPrevVertices(int vertex, std::vector<int> &vertices) const override {
    if (vertex >= downwards.size()) return;
    for (const auto &data: downwards[vertex])
      vertices.push_back(data.first);
  };

  const T *GetWeight(int from, int to) const override {
    if (from < 0 || from >= upwards.size()) return nullptr;
    auto find = upwards[from].find(to);
    if (find == upwards[from].end()) return nullptr;
    return &find->second;
  }
};


#endif //HOMEWORK_1_LISTGRAPH_H
