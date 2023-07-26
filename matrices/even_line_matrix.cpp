/**
 * This program reads a matrix from the user, and then finds the last row that contains only even numbers.
 * If there is no such row, it prints 0.
 * The dimensions of the matrix are also input by the user.
 */

#include <iostream>
#include <vector>

void inputMatrix(std::vector<std::vector<int>>& matrix, int rows, int cols) {
    std::cout << "\nInput array's elements\n";
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            std::cout << "Input element (" << i + 1 << "," << j + 1 << "): ";
            std::cin >> matrix[i][j];
        }
    }
}

void outputMatrix(const std::vector<std::vector<int>>& matrix, int rows, int cols) {
    std::cout << "\n";
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

int findLastEvenRow(const std::vector<std::vector<int>>& matrix, int rows, int cols) {
    for(int i = rows - 1; i >= 0; i--) {
        bool allEven = true;
        for(int j = 0; j < cols; j++) {
            if(matrix[i][j] % 2 != 0) {
                allEven = false;
                break;
            }
        }
        if(allEven) {
            return i + 1;
        }
    }
    return 0;
}

int main() {
    std::cout << "\nAn integer matrix of size MxN is given.\nFind number of last line, containing only even numbers.\nIf there are not such lines - print 0.\n";

    int rows, cols;
    std::cout << "\nEnter array's dimensions (MxN):\n";
    std::cin >> rows >> cols;

    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));
    inputMatrix(matrix, rows, cols);
    outputMatrix(matrix, rows, cols);

    int lastEvenRow = findLastEvenRow(matrix, rows, cols);
    if(lastEvenRow == 0) {
        std::cout << "\nThere is no line with all even numbers.\n";
    } else {
        std::cout << "\nThe " << lastEvenRow << "-th line is the last line with all even numbers.\n";
    }

    return 0;
}
