/**
 * This program reads a MxN matrix from the user, finds the row with the maximum element,
 * and duplicates that row in the matrix.
 */

#include <iostream>
#include <vector>

void readMatrix(std::vector<std::vector<int>>& matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << "Enter element [" << i + 1 << "] [" << j + 1 << "]: ";
            std::cin >> matrix[i][j];
        }
    }
}

void writeMatrix(const std::vector<std::vector<int>>& matrix, int rows, int cols) {
    std::cout << "Matrix after transformation:\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void duplicateMaxRow(std::vector<std::vector<int>>& matrix, int rows, int cols) {
    int maxElementRow = 0;
    int maxElement = matrix[0][0];

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] > maxElement) {
                maxElement = matrix[i][j];
                maxElementRow = i;
            }
        }
    }

    for (int j = 0; j < cols; ++j) {
        matrix[rows][j] = matrix[maxElementRow][j];
    }
}

int main() {
    int rows, cols;

    std::cout << "Enter a matrix of size MxN.\n";
    std::cout << "A row containing the maximum element will be duplicated.\n";

    do {
        std::cout << "Enter matrix dimensions M and N (both greater than 0):\n";
        std::cin >> rows >> cols;
        if (rows < 1 || cols < 1) {
            std::cout << "Error! Dimensions M and N must be greater than 0.\n";
        }
    } while (rows < 1 || cols < 1);

    std::vector<std::vector<int>> matrix(rows + 1, std::vector<int>(cols));

    readMatrix(matrix, rows, cols);
    duplicateMaxRow(matrix, rows, cols);
    writeMatrix(matrix, rows + 1, cols);

    return 0;
}