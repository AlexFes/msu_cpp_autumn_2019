/*
Нужно написать класс-матрицу, тип элементов int. В конструкторе задается количество рядов и строк.
Поддерживаются оперции: получить количество строк(rows)/столбцов(columns),
получить конкретный элемент,
умножить на число(*=),
сравнение на равенство/неравенство.
*/

#include <iostream>

class Proxy {
public:
    Proxy(int* p, int matrixColumns): pointer(p), cols(matrixColumns) {};

    int& operator[](int m) {
        if (m > cols) {
            std::out_of_range("Columns number out of range");
        }

        return *(pointer + m);
    }

private:
    int* pointer;
    int cols;
};

class Matrix {
public:
    Matrix(int n, int m): rows(n), cols(m) {
        pointer = new int[n * m];
    };

    ~Matrix() {
        delete[] pointer;
    };

    Proxy operator[](int n) {
        if (n > rows) {
            std::out_of_range("Rows number out of range");
        }

        return Proxy(pointer + n*cols, cols);
    };

    void operator*=(int val) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                *(pointer + i*cols + j) *= val;
            }
        }
    }

    bool operator==(Matrix m) {
        if (m.cols != cols || m.rows != rows) {
            return false;
        } else {
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    if (*(pointer + i*cols + j) != m[i][j]) {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    int getRows() {
        return this->rows;
    };

    int getColumns() {
        return this->cols;
    }

private:
    int rows;
    int cols;
    int* pointer;
};

// int main(int argc, char** argv) {
//     Matrix m(2, 3);
//     m[0][0] = 1;
//     m[0][1] = 2;
//     m[0][2] = 3;
//     m[1][0] = 1;
//     m[1][1] = 2;
//     m[1][2] = 3;
//
//     m*=3;
//
//     std::cout << m[0][0] << "\n";
//     std::cout << m[0][1] << "\n";
//     std::cout << m[0][2] << "\n";
//
//     return 0;
// }
