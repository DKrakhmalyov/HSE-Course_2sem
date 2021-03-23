
#ifndef HOMEWORK_1_GRAPH_H
#define HOMEWORK_1_GRAPH_H

#include <vector>
#include <list>
#include "src/node.h"

template<typename T>
class IGraph {
public:
    virtual ~IGraph() {}

    IGraph() {};

    IGraph(IGraph *_oth) {};

    virtual void AddEdge(int from, int to, T &&_obj) = 0;

    virtual int VerticesCount() const = 0;

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const = 0;

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const = 0;

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const = 0;

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const = 0;

protected:
    /*
     * __get__next__ нужен для того, чтобы вернуть список смежных вершин с весами
     * это служебный метод, который используется для того, чтобы сохранить веса
     * при использовании конструктора копирования - стандартный
     * GetNextVertices возвращает только смежные вершины без весов
     */
    virtual std::list<std::pair<int, T>> __get__next__(int vertex) const = 0;
    /*
     * Далее идёт метод __call__get__next__. для чего он? это трюк, чтобы из наследников можно
     * было вызывать protected метод __get__next__ у других наследников.
     * Таким образом, static метод в базовом классе позволяет обращаться к защищенным методам
     * из наследников (в противном случае оно не работает)
      */
    static std::list<std::pair<int, T>> __call__get__next__(IGraph<T> *base, int vertex) {
        return base->__get__next__(vertex);
    }

    virtual void __dfs__(int vertex, std::vector<int> &vertices, std::vector<bool> &used) const = 0;
};

template<typename T = void>
class IPtrsGraph {
public:
    virtual ~IPtrsGraph() {}

    IPtrsGraph() {};

    virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) = 0;

    virtual int VerticesCount() const = 0;

    virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const = 0;

    virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const = 0;

    virtual void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const = 0;

    virtual void BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const = 0;
};

#endif //HOMEWORK_1_GRAPH_H
