#pragma once

class Proxy {
public:
    Proxy(int* p, int matrixColumns);
    int& operator[](int m);

private:
    int* pointer;
    int cols;
};

class Matrix {
public:
    Matrix(int n, int m);
    ~Matrix();
    Proxy operator[](int n) const;
    void operator*=(int val);
    bool operator==(const Matrix& m);
    bool operator!=(const Matrix& m);
    int getRows();
    int getColumns();

private:
    int rows;
    int cols;
    int* pointer;
};
