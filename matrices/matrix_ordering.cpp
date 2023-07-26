/**
 * @file matrix_ordering.cpp
 * @brief This file contains functions to order rows of a 2D matrix.
 */

#include <iostream>
#include <vector>

// Reads a matrix from the console
void readMatrixFromConsole(std::vector<std::vector<int>>& matrix, int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            std::cout << "Enter element at position (" << i+1 << "," << j+1 << "): ";
            std::cin >> matrix[i][j];
        }
    }
}

// Prints the matrix to the console
void printMatrix(const std::vector<std::vector<int>>& matrix, int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

// Orders the matrix rows
void orderMatrixRows(std::vector<std::vector<int>>& matrix, int rows, int cols) {
    for(int i = 0; i < rows-1; i++) {
        for(int j = i+1; j < rows; j++) {
            if(matrix[i][0] > matrix[j][0]) {
                std::swap(matrix[i], matrix[j]);
            }
        }
    }
}

int main() {
    int rows, cols;
    std::cout << "Enter the dimensions of the matrix (rows cols): ";
    std::cin >> rows >> cols;

    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));

    readMatrixFromConsole(matrix, rows, cols);
    printMatrix(matrix, rows, cols);
    orderMatrixRows(matrix, rows, cols);
    std::cout << "\nOrdered matrix:\n";
    printMatrix(matrix, rows, cols);

    return 0;
}
