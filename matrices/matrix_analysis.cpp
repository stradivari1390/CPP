/**
 * This program takes a matrix of size MxN as input.
 * It finds the index of the first row where the number of positive and negative elements are equal.
 * If no such row exists, it outputs "No such row found".
 */

#include <iostream>
#include <vector>

using namespace std;

void inputMatrix(vector<vector<int>>& matrix, int rows, int cols);
int findEqualPosNegRow(const vector<vector<int>>& matrix, int rows, int cols);
void outputMatrix(const vector<vector<int>>& matrix, int rows, int cols, int equalRow);

int main() {
    int rows, cols, equalRow;
    cout << "Enter the dimensions of the matrix (MxN). Find the index of the first row where the number of positive and negative elements are equal.\n";

    do {
        cout << "Enter the dimensions of the matrix:\n";
        cin >> rows >> cols;
        if (rows < 1 || cols < 1) cout << "Error! Dimensions M and N should be > 0\n";
    } while(rows < 1 || cols < 1);

    vector<vector<int>> matrix(rows, vector<int>(cols));
    inputMatrix(matrix, rows, cols);
    equalRow = findEqualPosNegRow(matrix, rows, cols);
    outputMatrix(matrix, rows, cols, equalRow);

    return 0;
}

void inputMatrix(vector<vector<int>>& matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << "Enter element at position [" << i+1 << "] [" << j+1 << "]:\n";
            cin >> matrix[i][j];
        }
    }
}

int findEqualPosNegRow(const vector<vector<int>>& matrix, int rows, int cols) {
    int posCount, negCount, equalRow = 0;
    for (int i = rows-1; i >= 0; i--) {
        posCount = negCount = 0;
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] > 0) posCount++;
            if (matrix[i][j] < 0) negCount++;
        }
        if (posCount == negCount) {
            equalRow = i+1;
            break;
        }
    }
    return equalRow;
}

void outputMatrix(const vector<vector<int>>& matrix, int rows, int cols, int equalRow) {
    cout << "Matrix with row indices where the number of positive and negative elements are equal:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            cout << matrix[i][j] << " ";
        cout << "\n";
    }
    if (equalRow != 0) cout << "\nRow with equal number of positive and negative elements: " << equalRow;
    else cout << "No such row found";
}
