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
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}