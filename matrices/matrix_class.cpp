/**
 * The Matrix class represents a mathematical matrix with the number of rows and columns. 
 * It provides functions to perform matrix addition, subtraction, and multiplication.
 * It also includes functions to calculate the norm and determinant of the matrix.
 */

#include<iostream>
#include<cmath>
using namespace std;

class Matrix {
    double** matrixValues;
    int numRows, numColumns;

public:
    Matrix(int numRows, int numColumns);
    Matrix(int numRows, int numColumns, double** matrixValues);
    Matrix(int size);
    Matrix(const Matrix& otherMatrix);
    ~Matrix();
    Matrix operator+(const Matrix& otherMatrix);
    Matrix operator-(const Matrix& otherMatrix);
    Matrix operator*(const Matrix& otherMatrix);
    Matrix operator*(double num);
    Matrix& operator=(const Matrix& otherMatrix);
    double norm();
    double det();
    void print(const char* name);
};

Matrix::Matrix(int numRows, int numColumns) {
    this->numRows = numRows;
    this->numColumns = numColumns;
    matrixValues = new double* [numRows];
    for (int i = 0; i < numRows; i++) {
        matrixValues[i] = new double[numColumns];
        for (int j = 0; j < numColumns; j++) {
            matrixValues[i][j] = 0.0;
        }
    }
}

Matrix::Matrix(int numRows, int numColumns, double** matrixValues) {
    this->numRows = numRows;
    this->numColumns = numColumns;
    this->matrixValues = new double* [numRows];
    for (int i = 0; i < numRows; i++) {
        this->matrixValues[i] = new double[numColumns];
        for (int j = 0; j < numColumns; j++) {
            this->matrixValues[i][j] = matrixValues[i][j];
        }
    }
}

Matrix::Matrix(int size) {
    numRows = size;
    numColumns = size;
    matrixValues = new double* [numRows];
    for (int i = 0; i < numRows; i++) {
        matrixValues[i] = new double[numColumns];
        for (int j = 0; j < numRows; j++) {
            matrixValues[i][j] = 0.0;
        }
    }
}

Matrix::Matrix(const Matrix& otherMatrix) {
    numRows = otherMatrix.numRows;
    numColumns = otherMatrix.numColumns;
    matrixValues = new double* [numRows];
    for (int i = 0; i < numRows; i++) {
        matrixValues[i] = new double[numColumns];
        for (int j = 0; j < numColumns; j++) {
            matrixValues[i][j] = otherMatrix.matrixValues[i][j];
        }
    }
}

Matrix::~Matrix() {
    for(int i = 0; i < numRows; i++) delete [] matrixValues[i];
    delete[] matrixValues;
}

Matrix Matrix::operator+(const Matrix& otherMatrix) {
    Matrix temp(numRows, numColumns);
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numColumns; j++) {
            temp.matrixValues[i][j] = matrixValues[i][j] + otherMatrix.matrixValues[i][j];
        }
    }
    return temp;
}

Matrix Matrix::Matrix::operator-(const Matrix& otherMatrix) {
    Matrix temp(numRows, numColumns);
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numColumns; j++) {
            temp.matrixValues[i][j] = matrixValues[i][j] - otherMatrix.matrixValues[i][j];
        }
    }
    return temp;
}

Matrix Matrix::operator*(const Matrix& otherMatrix) {
    Matrix temp(numRows, otherMatrix.numColumns);
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < otherMatrix.numColumns; j++) {
            temp.matrixValues[i][j] = 0;
            for (int k = 0; k < numColumns; k++) {
                temp.matrixValues[i][j] += matrixValues[i][k] * otherMatrix.matrixValues[k][j];
            }
        }
    }
    return temp;
}

Matrix Matrix::operator*(double num) {
    Matrix temp(numRows, numColumns);
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numColumns; j++) {
            temp.matrixValues[i][j] = matrixValues[i][j] * num;
        }
    }
    return temp;
}

Matrix& Matrix::operator=(const Matrix& otherMatrix) {
    if (this == &otherMatrix)
        return *this;

    for(int i = 0; i < numRows; i++)
        delete [] matrixValues[i];
    delete [] matrixValues;

    numRows = otherMatrix.numRows;
    numColumns = otherMatrix.numColumns;
    matrixValues = new double* [numRows];
    for (int i = 0; i < numRows; i++) {
        matrixValues[i] = new double[numColumns];
        for (int j = 0; j < numColumns; j++) {
            matrixValues[i][j] = otherMatrix.matrixValues[i][j];
        }
    }
    return *this;
}

double Matrix::norm() {
    double sum = 0;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numColumns; j++) {
            sum += matrixValues[i][j] * matrixValues[i][j];
        }
    }
    return sqrt(sum);
}

double Matrix::det() {
    if (numRows != numColumns) {
        cout << "Determinant of a non-square matrix is not defined.";
        return 0;
    }

    Matrix temp(*this);
    double d = 1.0;

    for (int i = 0; i < numRows; ++i) {
        d *= temp.matrixValues[i][i];
        for (int k = i + 1; k < numRows; ++k) {
            double u = temp.matrixValues[k][i] / temp.matrixValues[i][i];
            for (int j = i; j < numRows; ++j) {
                temp.matrixValues[k][j] -= temp.matrixValues[i][j] * u;
            }
        }
    }

    return d;
}

void Matrix::print(const char* name) {
    cout << "Matrix " << name << " is:" << endl;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numColumns; j++) {
            cout << matrixValues[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}