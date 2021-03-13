#include <iostream>
#include "graph.h"
#include "gtest/gtest.h"

#include "src/listGraph.h"
#include "src/matrixGraph.h"
#include "src/arcGraph.h"
#include "src/ptrsGraph.h"

#include "src/arcGraph.cpp"
#include "src/listGraph.cpp"
#include "src/matrixGraph.cpp"
#include "src/ptrsGraph.cpp"

#include "src/nodePair.cpp"
#include "src/node.cpp"

#include "src/graphConverter.cpp"

template<typename T>
int32_t Node<T>::minAvailableId = 1;

TEST(IGraph, Creating) {
    IGraph<int> *listGr = new ListGraph<int>;
    IGraph<int> *arcGr = new ArcGraph<int>;
    IGraph<int> *matGr = new MatrixGraph<int>;
    IPtrsGraph<int> *pGraph = new PtrsGraph<int>;

    delete listGr;
    delete arcGr;
    delete matGr;
    delete pGraph;
}

// Simple linear graph
// 1 --> 2 --> 3 --> 4
TEST(ListGraph, Simple) {
    std::shared_ptr<IGraph<int>> listGr = std::dynamic_pointer_cast<IGraph<int>>(std::make_shared<ListGraph<int>>());
    listGr->addEdge(1, 2, 10);
    listGr->addEdge(2, 3, 20);
    listGr->addEdge(3, 4, 30);

    std::vector<int> res;
    listGr->deepFirstSearch(1, res);
    EXPECT_EQ(res.back(), 4);
    EXPECT_EQ(res.size(), 4);

    std::vector<int> res2;
    listGr->getPrevVertices(3, res2);
    EXPECT_EQ(res2.front(), 2);
    EXPECT_EQ(res2.size(), 1);

}

// Cycled graph
// 1 --> 2 --> 3000 --> 1
TEST(MatrixGraph, Cycled) {
    std::shared_ptr<IGraph<int>> matGr = std::dynamic_pointer_cast<IGraph<int>>(std::make_shared<MatrixGraph<int>>());
    matGr->addEdge(1, 2, 10);
    matGr->addEdge(2, 3000, 20);
    matGr->addEdge(3000, 1, 30);

    std::vector<int> res;
    matGr->deepFirstSearch(1, res);
    EXPECT_EQ(res.back(), 3000);
    EXPECT_EQ(res.size(), 3);

    std::vector<int> res2;
    matGr->getPrevVertices(3000, res2);
    EXPECT_EQ(res2[0], 2);
    EXPECT_EQ(res2.size(), 1);
}

// Tree graph
// 1 --> 2 --> 3
//   \
//     -> 4 --> 5
//        \
//          ->6
TEST(ArcGraph, Cycled) {
    std::shared_ptr<IGraph<int>> arcGr = std::dynamic_pointer_cast<IGraph<int>>(std::make_shared<ArcGraph<int>>());
    arcGr->addEdge(1, 2, 10);
    arcGr->addEdge(2, 3, 20);
    arcGr->addEdge(1, 4, 30);
    arcGr->addEdge(4, 5, 40);
    arcGr->addEdge(4, 6, 50);

    std::vector<int> res;
    arcGr->breadthFirstSearch(4, res);
    EXPECT_EQ(res.size(), 3);

    std::vector<int> res2;
    arcGr->getNextVertices(1, res2);
    EXPECT_EQ(res2.size(), 2);
}

// Cycled graph
// 1 --> 2 --> 3 --> 1
TEST(PtrsGraph, Cycled) {
    std::shared_ptr<IPtrsGraph<int>> ptrGr = std::dynamic_pointer_cast<IPtrsGraph<int>>(
            std::make_shared<PtrsGraph<int>>());
    Node<int> *first = new Node<int>;
    Node<int> *second = new Node<int>;
    Node<int> *third = new Node<int>;
    ptrGr->addEdge(first, second, 10);
    ptrGr->addEdge(second, third, 20);
    ptrGr->addEdge(third, first, 30);

    std::vector<Node<int> *> res;
    ptrGr->deepFirstSearch(first, res);
    EXPECT_EQ(res.back(), third);
    EXPECT_EQ(res.size(), 3);

    std::vector<Node<int> *> res2;
    ptrGr->getPrevVertices(third, res2);
    EXPECT_EQ(res2.size(), 1);

    delete first;
    delete second;
    delete third;
}

// Cycled graph
// 1 --> 2 --> 3000 --> 1
TEST(IGraph, Copying) {
    IGraph<int> *matGr = new MatrixGraph<int>;
    matGr->addEdge(1, 2, 10);
    matGr->addEdge(2, 3000, 20);
    matGr->addEdge(3000, 1, 30);

    IGraph<int> *listGr = new ListGraph<int>(matGr);
    IGraph<int> *arcGr = new ArcGraph<int>(listGr);
    IGraph<int> *mat2Gr = new MatrixGraph<int>(arcGr);

    delete matGr;
    delete listGr;
    delete arcGr;
    delete mat2Gr;
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}