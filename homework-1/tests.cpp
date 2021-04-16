#include <iostream>
#include "graph.h"
#include "gtest/gtest.h"

#include "src/listGraph.h"
#include "src/matrixGraph.h"
#include "src/arcGraph.h"
#include "src/ptrsGraph.h"

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
    listGr->AddEdge(1, 2, 10);
    listGr->AddEdge(2, 3, 20);
    listGr->AddEdge(3, 4, 30);

    std::vector<int> res;
    listGr->DeepFirstSearch(1, res);
    EXPECT_EQ(res.back(), 4);
    EXPECT_EQ(res.size(), 4);

    std::vector<int> res2;
    listGr->GetPrevVertices(3, res2);
    EXPECT_EQ(res2.front(), 2);
    EXPECT_EQ(res2.size(), 1);

}

// Cycled graph
// 1 --> 2 --> 3000 --> 1
TEST(MatrixGraph, Cycled) {
    std::shared_ptr<IGraph<int>> matGr = std::dynamic_pointer_cast<IGraph<int>>(std::make_shared<MatrixGraph<int>>());
    matGr->AddEdge(1, 2, 10);
    matGr->AddEdge(2, 3000, 20);
    matGr->AddEdge(3000, 1, 30);

    std::vector<int> res;
    matGr->DeepFirstSearch(1, res);
    EXPECT_EQ(res.back(), 3000);
    EXPECT_EQ(res.size(), 3);

    std::vector<int> res2;
    matGr->GetPrevVertices(3000, res2);
    EXPECT_EQ(res2[0], 2);
    EXPECT_EQ(res2.size(), 1);
}

// // Tree graph
// // 1 --> 2 --> 3
// //   \
// //     -> 4 --> 5
// //        \
// //          ->6
TEST(ArcGraph, Cycled) {
    std::shared_ptr<IGraph<int>> arcGr = std::dynamic_pointer_cast<IGraph<int>>(std::make_shared<ArcGraph<int>>());
    arcGr->AddEdge(1, 2, 10);
    arcGr->AddEdge(2, 3, 20);
    arcGr->AddEdge(1, 4, 30);
    arcGr->AddEdge(4, 5, 40);
    arcGr->AddEdge(4, 6, 50);

    std::vector<int> res;
    arcGr->BreadthFirstSearch(4, res);
    EXPECT_EQ(res.size(), 3);

    std::vector<int> res2;
    arcGr->GetNextVertices(1, res2);
    EXPECT_EQ(res2.size(), 2);
}

// // Cycled graph
// // 1 --> 2 --> 3 --> 1
TEST(PtrsGraph, Cycled) {
    std::shared_ptr<IPtrsGraph<int>> ptrGr = std::dynamic_pointer_cast<IPtrsGraph<int>>(
            std::make_shared<PtrsGraph<int>>());
    Node<int> *first = new Node<int>;
    Node<int> *second = new Node<int>;
    Node<int> *third = new Node<int>;
    ptrGr->AddEdge(first, second, 10);
    ptrGr->AddEdge(second, third, 20);
    ptrGr->AddEdge(third, first, 30);

    std::vector<Node<int> *> res;
    ptrGr->DeepFirstSearch(first, res);
    EXPECT_EQ(res.back(), third);
    EXPECT_EQ(res.size(), 3);

    std::vector<Node<int> *> res2;
    ptrGr->GetPrevVertices(third, res2);
    EXPECT_EQ(res2.size(), 1);

    // Возможно, лучше не удалять объекты вершин, а передавать владение сразу графу
    // Решите точно в реализации и удалите строки, если что
    delete first;
    delete second;
    delete third;
}

// // Cycled graph
// // 1 --> 2 --> 3000 --> 1
TEST(IGraph, Copying) {
    IGraph<int> *matGr = new MatrixGraph<int>;
    matGr->AddEdge(1, 2, 10);
    matGr->AddEdge(2, 3000, 20);
    matGr->AddEdge(3000, 1, 30);

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
