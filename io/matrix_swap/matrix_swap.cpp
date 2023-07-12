/**
 * This program reads a matrix of size M*N (M is even) from a file,
 * swaps the top and bottom halves of the matrix, and writes the result
 * back to a file. It also prints the transformed matrix to the console.
 */

#include <cstdio>
#define MAX_ROWS 10
#define MAX_COLS 10

void readMatrix(int matrix[][MAX_COLS], int rows, int cols);
void swapHalves(int matrix[][MAX_COLS], int rows, int cols);
void writeMatrix(int matrix[][MAX_COLS], int rows, int cols);

int main() {
    int matrix[MAX_ROWS][MAX_COLS], rows, cols;
    printf("Given a matrix of size M*N (M is even)\nSwap the top and bottom halves of the matrix\n");

    FILE *inputFile = fopen("INPUT.DAT", "r");
    fscanf(inputFile, "%d%d", &rows, &cols);
    readMatrix(matrix, rows, cols);
    swapHalves(matrix, rows, cols);
    writeMatrix(matrix, rows, cols);

    return 0;
}

void readMatrix(int matrix[][MAX_COLS], int rows, int cols) {
    FILE *inputFile = fopen("INPUT.DAT", "r");
    int skip;
    fscanf(inputFile, "%d%d", &skip, &skip);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            fscanf(inputFile, "%d", &matrix[i][j]);
    fclose(inputFile);
}

void writeMatrix(int matrix[][MAX_COLS], int rows, int cols) {
    FILE *outputFile = fopen("output.dat", "w");
    fprintf(outputFile, "Matrix after transformation\n");
    printf("Matrix after transformation\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(outputFile, "%3d", matrix[i][j]);
            printf("%3d", matrix[i][j]);
        }
        fprintf(outputFile, "\n");
        printf("\n");
    }
}

void swapHalves(int matrix[][MAX_COLS], int rows, int cols) {
    int temp;
    for (int i = 0; i < rows / 2; i++)
        for (int j = 0; j < cols; j++) {
            temp = matrix[i][j];
            matrix[i][j] = matrix[rows / 2 + i][j];
            matrix[rows / 2 + i][j] = temp;
        }
}
