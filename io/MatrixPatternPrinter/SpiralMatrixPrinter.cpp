/**
 * This program reads a square matrix from a file, then prints the elements of the matrix in a spiral pattern:
 * all elements of the first row, all elements of the last column, all elements of the last row (in reverse order),
 * all elements of the first column (in reverse order), and so on, spiraling inward.
 * The pattern is printed both to the console and appended to the input file.
 */

#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::ifstream inputFile("matrix1.dat");
    std::ofstream outputFile("matrix1.dat", std::ios_base::app);
    if (!inputFile || !outputFile) {
        std::cerr << "Error opening file.\n";
        return 1;
    }

    int matrixSize;
    inputFile >> matrixSize;

    std::vector<std::vector<int>> matrix(matrixSize, std::vector<int>(matrixSize));
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            inputFile >> matrix[i][j];
        }
    }

    outputFile << "\nMatrix entered in a spiral pattern:\n";
    std::cout << "Matrix entered in a spiral pattern:\n";
    int startRow = 0, endRow = matrixSize;
    int startCol = 0, endCol = matrixSize;
    while (startRow < endRow && startCol < endCol) {
        for (int i = startCol; i < endCol; ++i) {
            outputFile << matrix[startRow][i] << ' ';
            std::cout << matrix[startRow][i] << ' ';
        }
        startRow++;

        for (int i = startRow; i < endRow; ++i) {
            outputFile << matrix[i][endCol - 1] << ' ';
            std::cout << matrix[i][endCol - 1] << ' ';
        }
        endCol--;

        if (startRow < endRow) {
            for (int i = endCol - 1; i >= startCol; --i) {
                outputFile << matrix[endRow - 1][i] << ' ';
                std::cout << matrix[endRow - 1][i] << ' ';
            }
            endRow--;
        }

        if (startCol < endCol) {
            for (int i = endRow - 1; i >= startRow; --i) {
                outputFile << matrix[i][startCol] << ' ';
                std::cout << matrix[i][startCol] << ' ';
            }
            startCol++;
        }
    }
    outputFile << '\n';
    std::cout << '\n';

    return 0;
}
