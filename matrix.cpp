#include "matrix.h"

#include <iostream>
#include <iomanip>

using namespace std;

///@TODO implement handling of memory allocation failures
void Matrix::allocateMemory() {
    data = new Number * [getDim()]; //allocate array of pointers (access vector)
    //allocate arrays of Numbers
    for (auto i = 0; i < getDim(); i++) {
        data[i] = new Number[getDim()];
    }
}

Matrix::Matrix(Number diag) {
    allocateMemory();
    std::cout << "Constructor" << std::endl;
    for (auto i = 0; i < getDim(); i++) {
        for (auto j = 0; j < getDim(); j++) {
            data[i][j] = i == j ? diag : 0;
        }
    }
}

void Matrix::copyMemory(const Matrix& src) {
    for (unsigned int i = 0; i < getDim(); i++) {
        for (unsigned int j = 0; j < getDim(); j++) {
            this->data[i][j] = src.data[i][j]; //deep copy
        }
    }
}

Matrix::Matrix(Matrix& other) {
    std::cout << "Copy constructor" << std::endl;
    allocateMemory();
    copyMemory(other);
}

Matrix::Matrix(Matrix&& other)
{
    cout << "Move constructor" << endl;
    this->data = other.data;
    other.data = nullptr;
}


//*this is left hand side
Matrix& Matrix::operator=(const Matrix& rhs) {
    cout << "assignment operator" << endl;
    if (this == &rhs) {
        return *this;
    }
    this->copyMemory(rhs);
    return *this;
}

Matrix& Matrix::operator=(Matrix&& rhs)
{
    cout << "move assignment operator" << endl;
    if (this == &rhs)
    {
        return *this; // will not steal from myself
    }
    this->releaseMemory();
    this->data = rhs.data; //shallow copy
    rhs.data = nullptr;
    return *this;
}

void Matrix::releaseMemory() {
    for (auto i = 0; i < getDim(); i++) {
        delete[] data[i];
    }
    delete[] data;
    data = nullptr;
}

Matrix::~Matrix() {
    std::cout << "Destructor" << std::endl;
    if (data) {
        releaseMemory();
    }
   
}

Number& Matrix::operator()(unsigned int i, unsigned int j) {
    //i--;
    //j--;
    if (i >= getDim() || i >= getDim()) {
        throw std::out_of_range("Index out of range");
    }
    return data[i][j];
}


ostream& operator<<(ostream& os, Matrix& m) {
    for (unsigned int i = 0; i < m.getDim(); i++) {
        for (unsigned int j = 0; j < m.getDim(); j++) {
            os << setw(8) << setprecision(7) << m(i, j) << "\t";
        }
        os << endl;
    }
    return os;
}

Matrix operator+(Matrix& a, Matrix& b) {
    Matrix c;
    for (unsigned int i = 0; i < a.getDim(); i++) {
        for (unsigned int j = 0; j < b.getDim(); j++) {
            c(i, j) = a(i, j) + b(i, j);
        }
    }
    return c;
}

Matrix operator*(Matrix& a, Matrix& b)
{
    Matrix c;
    for (unsigned int i = 0; i < a.getDim(); i++) {
        for (unsigned int j = 0; j < b.getDim(); j++) {
            c(i, j) = 0;
            for (unsigned int n = 0; n < a.getDim(); n++)
            c(i, j) += a(i, n) * b(n, j);
        }
    }
    return c;
}

Matrix operator*(Number alpha, Matrix& m)
{
    Matrix c;
    for (unsigned int i = 0; i < m.getDim(); i++) {
        for (unsigned int j = 0; j < m.getDim(); j++) {
            c(i, j) = alpha * m(i, j);
        }
    }
    return c;
}

Matrix operator*(Matrix& m, Number alpha)
{
    Matrix c;
    for (unsigned int i = 0; i < m.getDim(); i++) {
        for (unsigned int j = 0; j < m.getDim(); j++) {
            c(i, j) = m(i,j) * alpha;
        }
    }
    return c;
}

bool operator==(Matrix& a, Matrix& b)
{
    if (a.getDim() == b.getDim()) {
        for (unsigned int i = 0; i < a.getDim(); i++) {
            for (unsigned int j = 0; j < b.getDim(); j++) {
                if (a(i, j) != b(i, j)) {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

bool operator!=(Matrix& a, Matrix& b)
{
    if (a.getDim() == b.getDim()) {
        for (unsigned int i = 0; i < a.getDim(); i++) {
            for (unsigned int j = 0; j < b.getDim(); j++) {
                if (a(i, j) != b(i, j)) {
                    return true;
                }
            }
        }
        return false;
    }
    return true;
}

Number operator~(Matrix& m)
{
    Number c;
    c = 0;
    for (unsigned int i = 0; i < m.getDim(); i++) {
        c += m(i, i);
    }
    return c;
}