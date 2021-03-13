#include <vector>

#ifndef HOMEWORK_1_NODE_H
#define HOMEWORK_1_NODE_H

template<typename T>
class Node {
public: 
	std::vector<std::pair<Node*,T>> next;

	Node() : next(std::vector< std::pair< Node<T>*, T> >()) { }
};

#endif //HOMEWORK_1_NODE_H
