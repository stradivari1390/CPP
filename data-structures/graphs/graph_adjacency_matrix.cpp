/**
 * This program reads an adjacency matrix from the user and prints out the vertices
 * that have outgoing edges. The adjacency matrix represents a graph where the value
 * at the i-th row and j-th column indicates whether there is an edge from vertex i to vertex j.
 */

#include <iostream>
#include <vector>

#define MAX_SIZE 10

void inputAdjacencyMatrix(std::vector<std::vector<int>>& matrix, int size);
void printVerticesWithOutgoingEdges(int vertex, int size, const std::vector<std::vector<int>>& matrix);

int main() {
    std::vector<std::vector<int>> adjacencyMatrix(MAX_SIZE, std::vector<int>(MAX_SIZE, 0));
    int size;

    std::cout << "\nEnter the number of vertices: ";
    std::cin >> size;

    inputAdjacencyMatrix(adjacencyMatrix, size);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (adjacencyMatrix[i][j]) {
                printVerticesWithOutgoingEdges(j, size, adjacencyMatrix);
            }
        }
    }

    return 0;
}

void printVerticesWithOutgoingEdges(int vertex, int size, const std::vector<std::vector<int>>& matrix) {
    for (int i = 0; i < size; i++) {
        if (matrix[vertex][i]) {
            std::cout << "Vertex " << vertex << " has an outgoing edge;\n";
            break;
        }
    }
}

void inputAdjacencyMatrix(std::vector<std::vector<int>>& matrix, int size) {
    std::cout << "Enter the adjacency matrix:\n\n";
    std::cout << " | ";
    for(int j = 0; j < size; j++) std::cout << j;
    std::cout << '\n';
    for (int i = 0; i < 2 * size + 2; i++) std::cout << '-';
    std::cout << '\n';

    for (int i = 0; i < size; i++) {
        std::cout << "\n " << i << " | ";
        for(int j = 0; j < size; j++) std::cin >> matrix[i][j];
    }
    std::cout << '\n';
}
