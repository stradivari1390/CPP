/**
 * @file finding_max_element.cpp
 * @brief This file contains functions for matrix operations such as input, output, and finding the maximum element.
 */

#include <iostream>
#include <vector>

/**
 * @brief Function to input elements into a matrix.
 * @param matrix The matrix to input elements into.
 * @param rows The number of rows in the matrix.
 * @param cols The number of columns in the matrix.
 */
void inputMatrix(std::vector<std::vector<double>>& matrix, int rows, int cols){
    double element;
    std::cout << "\nPlease input the elements of the matrix:\n";
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++){
            std::cout << "Input element at position (" << i+1 << ", " << j+1 << "): ";
            std::cin >> element;
            matrix[i][j] = element;
        }
}

/**
 * @brief Function to output a matrix to the console.
 * @param matrix The matrix to output.
 * @param rows The number of rows in the matrix.
 * @param cols The number of columns in the matrix.
 */
void outputMatrix(const std::vector<std::vector<double>>& matrix, int rows, int cols){
    std::cout << "\nMatrix:\n";
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++)
            std::cout << " " << matrix[i][j] << " ";
        std::cout << "\n";
    }
}

/**
 * @brief Function to find the maximum element in a matrix.
 * @param matrix The matrix to find the maximum element in.
 * @param rows The number of rows in the matrix.
 * @param cols The number of columns in the matrix.
 * @return The maximum element in the matrix.
 */
double maxMatrix(const std::vector<std::vector<double>>& matrix, int rows, int cols){
    double maxElement = matrix[0][0];
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            if(matrix[i][j] > maxElement) maxElement = matrix[i][j];
    return maxElement;
}

int main(){
    int rows, cols;
    std::cout << "\nCalculating the maximum element of a matrix.\n";
    std::cout << "Please, input the number of rows: ";
    std::cin >> rows;
    std::cout << "Please, input the number of columns: ";
    std::cin >> cols;

    std::vector<std::vector<double>> matrix(rows, std::vector<double>(cols));
    inputMatrix(matrix, rows, cols);
    outputMatrix(matrix, rows, cols);
    double maxElement = maxMatrix(matrix, rows, cols);
    std::cout << "\nThe maximum element in the matrix is: " << maxElement << "\n";
    return 0;
}
