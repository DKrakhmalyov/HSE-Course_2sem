
#ifndef HOMEWORK_1_ARCGRAPH_H
#define HOMEWORK_1_ARCGRAPH_H

#include "../graph.h"

template<typename T = void>
class ArcGraph : public IGraph<T> {
private:
  struct Arc {
    int from;
    int to;
    T data;

    Arc(int from, int to) : from(from), to(to) {}

    Arc(int from, int to, T data) : from(from), to(to), data(data) {}

    bool operator<(const Arc &o) const {
      if (from != o.from) return from < o.from;
      if (to != o.to) return to < o.to;
      return false;
    }

    bool operator>(const Arc &o) const {
      if (from != o.from) return from > o.from;
      if (to != o.to) return to > o.to;
      return false;
    }
  };

  std::set<Arc> arcSetUp;
  std::set<Arc> arcSetDown;
  std::set<int> vertex;

public:
  void AddEdge(int from, int to, T &&element) override {
    arcSetUp.insert({from, to, element});
    arcSetDown.insert({to, from, element});
    vertex.insert(from);
    vertex.insert(to);
  };

  ArcGraph() {};

  explicit ArcGraph(IGraph<T> *oth) : IGraph<T>(oth) {
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
    return vertex.size();
  };

  void GetNextVertices(int vtx, std::vector<int> &vertices) const override {
    if (vtx < 0 || vtx >= arcSetUp.size()) return;
    auto lowerBound = arcSetUp.template lower_bound({vtx, 0});
    if (lowerBound->from != vtx) return;

    auto upperBound = arcSetUp.template upper_bound({vtx + 1, -1});
    for (auto it = lowerBound; it != upperBound; it++) {
      vertices.push_back(it->to);
    }
  }

  void GetPrevVertices(int vtx, std::vector<int> &vertices) const override {
    if (vtx < 0 || vtx >= arcSetUp.size()) return;
    auto lowerBound = arcSetDown.template lower_bound({vtx, 0});
    if (lowerBound->from != vtx) return;

    auto upperBound = arcSetDown.template upper_bound({vtx + 1, -1});
    for (auto it = lowerBound; it != upperBound; it++) {
      vertices.push_back(it->to);
    }
  };

  const T *GetWeight(int from, int to) const override {
    if (from < 0) return nullptr;
    if (to < 0) return nullptr;
    auto found = arcSetUp.template find({from, to});
    if (found == arcSetUp.end()) return nullptr;
    return &found->data;
  }
};

#endif //HOMEWORK_1_ARCGRAPH_H
