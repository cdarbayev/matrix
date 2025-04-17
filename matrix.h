#ifndef MATRIX_H
#define MATRIX_H

#include "datatype.h"

#include <iostream>

class Matrix
{
    enum { DIM = 3 };
    //const static unsigned int DIM;
    Number** data;
    void allocateMemory();
    void copyMemory(const Matrix& src);
    void releaseMemory();
public:
    Matrix(Number diag = 0);
    Matrix(Matrix& other); //copy constructor
    Matrix(Matrix&& other); //move constructor
    ~Matrix();
    unsigned int getDim() const {
        return DIM;
    }
    //call operator
    Number& operator()(unsigned int i, unsigned int j);
    //assignment operator
    Matrix& operator=(const Matrix& rhs);
    //move operator
    Matrix& operator=(Matrix&& rhs);
};

Matrix operator+(Matrix& a, Matrix& b);
Matrix operator*(Matrix& a, Matrix& b);
Matrix operator*(Number alpha, Matrix& m);
Matrix operator*(Matrix& m, Number alpha);
bool operator==(Matrix& a, Matrix& b);
bool operator!=(Matrix& a, Matrix& b);
Number operator~(Matrix& m); //calculate trace of the Matrix

std::ostream& operator<<(std::ostream& os,
    Matrix& m);

#endif // MATRIX_H
