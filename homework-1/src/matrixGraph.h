
#ifndef HOMEWORK_1_MATRIXGRAPH_H
#define HOMEWORK_1_MATRIXGRAPH_H

#include "../graph.h"

template<typename T>
class MatrixGraph : public IGraph<T> {
public:
    virtual void AddEdge(int from, int to, T &&element) {
        *getMatrixCellFor(from, to) = new T(element);
    };

    MatrixGraph() {};

    MatrixGraph(IGraph<T> *_oth) {
        GraphConverter<T, MatrixGraph>().convertTo(_oth, this);
    };

    virtual int VerticesCount() const {
        int ans = 0;
        for (int from = 0; from < curMatrixSize; from++) {
            bool emptyVertex = true;
            for (int to = 0; to < curMatrixSize; to++) {
                if (matrix[from][to] != nullptr) {
                    emptyVertex = false;
                    break;
                }
            }
            if (!emptyVertex) {
                ans++;
            }
        }
        return ans;
    };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        for (int to = 0; to < curMatrixSize; to++) {
            if (matrix[vertex][to] != nullptr) {
                vertices.push_back(to);
            }
        }
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        for (int from = 0; from < curMatrixSize; from++) {
            if (matrix[from][vertex] != nullptr) {
                vertices.push_back(from);
            }
        }
    };

    virtual ~MatrixGraph() {
        freeMatrix(matrix, curMatrixSize);
    }

    void GetAllVertices(std::vector<int>& vertices) const override {
        for (int vertex = 0; vertex < curMatrixSize; vertex++) {
            vertices.push_back(vertex);
        }
    }

    T GetWeight(int from, int to) const override {
        return *matrix[from][to];
    }

private:
    T ***matrix = nullptr;
    int curMatrixSize = 0;

    void freeMatrix(T ***matrixForDelete, int matrixSize) {
        if (matrixForDelete != nullptr) {
            for (int i = 0; i < matrixSize; i++) {
                for (int j = 0; j < matrixSize; j++) {
                    T* weightObject = matrixForDelete[i][j];
                    if (weightObject != nullptr) {
                        delete weightObject;
                    }
                }
                delete[] matrixForDelete[i];
            }
            delete[] matrixForDelete;
        }
    }

    T*** copyMatrix(T ***oldMatrix, int oldMatrixSize, int newMatrixSize) {
        T ***result = new T**[newMatrixSize];
        for (int i = 0; i < newMatrixSize; i++) {
            result[i] = new T*[newMatrixSize];
            std::fill(&(result[i][0]), &(result[i][0]) + newMatrixSize, nullptr);
        }
        if (oldMatrix != nullptr) {
            for (int i = 0; i < std::min(oldMatrixSize, newMatrixSize); i++) {
                for (int j = 0; j < std::min(oldMatrixSize, newMatrixSize); j++) {
                    T* oldWeightPtr = oldMatrix[i][j];
                    if (oldWeightPtr != nullptr) {
                        result[i][j] = new T(*oldWeightPtr);
                    }
                }
            }
        }
        return result;
    }

    void resizeMatrix(int newMatrixSize) {
        T ***newMatrix = copyMatrix(matrix, curMatrixSize, newMatrixSize);
        freeMatrix(matrix, curMatrixSize);
        matrix = newMatrix;
        curMatrixSize = newMatrixSize;
    }

    void resizeIfSmaller(int requestedMinSize) {
        if (requestedMinSize > curMatrixSize) {
            resizeMatrix(requestedMinSize);
        }
    }

    T** getMatrixCellFor(int from, int to) {
        resizeIfSmaller(from + 1);
        resizeIfSmaller(to + 1);
        return &(matrix[from][to]);
    }

};

#endif //HOMEWORK_1_MATRIXGRAPH_H
