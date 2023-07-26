/**
 * The program first reads the matrix from the file and prints it to the console.
 * Then, it performs a column ordering operation on the matrix.
 * The column ordering operation finds the last column in which all elements are non-negative.
 * If such a column is found, it swaps this column with the first column of the matrix.
 */

#include <iostream>
#include <fstream>
#include <vector>

#define MAX_SIZE 25

void readMatrixFromFile(std::vector<std::vector<int>>& matrix, const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Unable to open file " << filename << std::endl;
        exit(1);
    }
    int rows, cols;
    file >> rows >> cols;
    matrix.resize(rows, std::vector<int>(cols));
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            file >> matrix[i][j];
        }
    }
    file.close();
    std::cout << "Finished reading matrix from file.\n";
}

void printMatrix(const std::vector<std::vector<int>>& matrix, int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "Finished printing matrix.\n";
}

void orderMatrixColumns(std::vector<std::vector<int>>& matrix, int rows, int cols) {
    int lastPositiveColumn = -1;
    for(int j = 0; j < cols; j++) {
        bool isPositive = true;
        for(int i = 0; i < rows; i++) {
            if(matrix[i][j] < 0) {
                isPositive = false;
                break;
            }
        }
        if(isPositive) {
            lastPositiveColumn = j;
        }
    }
    if(lastPositiveColumn != -1) {
        for(int i = 0; i < rows; i++) {
            std::swap(matrix[i][0], matrix[i][lastPositiveColumn]);
        }
    }
    std::cout << "Finished ordering matrix columns.\n";
}

int main() {
    int rows, cols;
    std::ifstream file("ujas3.dat");
    if (!file) {
        std::cerr << "Unable to open file ujas3.dat\n";
        return 1;
    }
    file >> rows >> cols;
    file.close();
    std::cout << "Read rows and cols from file: " << rows << ", " << cols << "\n";

    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));

    readMatrixFromFile(matrix, "ujas3.dat");
    printMatrix(matrix, rows, cols);
    orderMatrixColumns(matrix, rows, cols);
    printMatrix(matrix, rows, cols);

    return 0;
}
