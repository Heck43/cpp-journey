#pragma once
#include <iostream>
using namespace std;

class Matrix
{
private:
    int rows;
    int cols;
    int** data;

    void allocate();
    void freeMemory();
    void copyFrom(const Matrix& other);
    void checkSameSize(const Matrix& other) const;

public:
    Matrix(int rows = 1, int cols = 1);
    Matrix(const Matrix& other);
    ~Matrix();

    Matrix& operator=(const Matrix& other);

    int getRows() const;
    int getCols() const;

    int& operator()(int row, int col);
    int operator()(int row, int col) const;

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;

    Matrix operator*(int value) const;

    Matrix operator!() const;

    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;

    friend Matrix operator* (int value, const Matrix& matrix);
    friend ostream& operator<<(ostream& os, const Matrix& matrix);
    friend istream& operator>>(istream& is, Matrix& matrix);
};

