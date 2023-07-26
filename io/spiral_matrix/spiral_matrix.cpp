/**
 * This program reads a matrix from a file, and then prints the elements of the matrix in a spiral order.
 * The matrix is assumed to be square and of odd dimension.
 * The file is assumed to contain the dimension of the matrix followed by its elements.
 */

#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::ifstream file("gig.dat");
    if (!file) {
        std::cerr << "Unable to open file gig.dat";
        return 1;
    }

    int dimension;
    file >> dimension;

    std::vector<std::vector<int>> matrix(dimension, std::vector<int>(dimension));
    for(int i = 0; i < dimension; i++) {
        for(int j = 0; j < dimension; j++) {
            file >> matrix[i][j];
        }
    }

    int center = dimension / 2;
    std::cout << "Straightened spiral:\n";
    for(int i = 0; i <= center; i++) {
        for (int j = i; j < dimension - i; j++) std::cout << matrix[j][i] << " ";
        for (int j = i + 1; j < dimension - i; j++) std::cout << matrix[dimension - i - 1][j] << " ";
        for (int j = dimension - i - 2; j >= i; j--) std::cout << matrix[j][dimension - i - 1] << " ";
        for (int j = dimension - i - 2; j > i; j--) std::cout << matrix[i][j] << " ";
    }
    std::cout << matrix[center][center] << std::endl;

    return 0;
}
