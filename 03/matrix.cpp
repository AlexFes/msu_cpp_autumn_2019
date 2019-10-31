/*
Нужно написать класс-матрицу, тип элементов int. В конструкторе задается количество рядов и строк.
Поддерживаются оперции: получить количество строк(rows)/столбцов(columns),
получить конкретный элемент,
умножить на число(*=),
сравнение на равенство/неравенство.
*/

#include <iostream>
#include "matrix.h"

Proxy::Proxy(int* p, int matrixColumns) {
    pointer = p;
    cols = matrixColumns;
}

int& Proxy::operator[](int m) {
    if (m > cols) {
        std::out_of_range("Columns number out of range");
    }

    return *(pointer + m);
}

Matrix::Matrix(int n, int m) {
    rows = n;
    cols = m;
    pointer = new int[n * m];
}

Matrix::~Matrix() {
    delete[] pointer;
}

Proxy Matrix::operator[](int n) const{
    if (n > rows) {
        std::out_of_range("Rows number out of range");
    }

    return Proxy(pointer + n*cols, cols);
}

void Matrix::operator*=(int val) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            *(pointer + i*cols + j) *= val;
        }
    }
}

bool Matrix::operator==(const Matrix& m) {
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

bool Matrix::operator!=(const Matrix& m) {
    if (m.cols != cols || m.rows != rows) {
        return true;
    } else {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (*(pointer + i*cols + j) != m[i][j]) {
                    return true;
                }
            }
        }
    }

    return false;
}

int Matrix::getRows() {
    return this->rows;
}

int Matrix::getColumns() {
    return this->cols;
}
