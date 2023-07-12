/**
 * This program reads two files containing square matrices, performs matrix multiplication
 * and writes the result into a new file. The matrices are assumed to be square and of the same size.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

int main() {
    std::ifstream fileA("matrixA.dat"), fileB("matrixB.dat");
    std::ofstream fileC("matrixC.dat");

    if (!fileA.is_open() || !fileB.is_open() || !fileC.is_open()) {
        std::cout << "Error opening files.\n";
        return 1;
    }

    std::cout << "Reading two files containing elements of square matrices.\n"
              << "Creating a new file with the result of matrix multiplication.\n";

    std::string line;
    std::getline(fileA, line);
    std::istringstream iss(line);
    int size = 0, temp;
    while (iss >> temp) size++;

    fileA.clear();
    fileA.seekg(0);

    std::vector<std::vector<int>> matrixA(size, std::vector<int>(size));
    std::vector<std::vector<int>> matrixB(size, std::vector<int>(size));
    std::vector<std::vector<int>> matrixC(size, std::vector<int>(size, 0));

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            fileA >> matrixA[i][j];
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            fileB >> matrixB[i][j];
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            fileC << matrixC[i][j] << ' ';
        }
        fileC << '\n';
    }

    std::cout << "Matrix multiplication completed and result written to file.\n";

    return 0;
}
