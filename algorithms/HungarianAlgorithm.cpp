/**
 * This program implements the Hungarian Algorithm for the assignment problem.
 * It reads a square matrix from standard input, where the matrix represents the cost of assigning tasks to agents.
 * The program then computes the optimal assignment that minimizes the total cost and prints the total cost to standard output.
 */

#include <iostream>
#include <vector>
#include <limits>

const int MAX_SIZE = 15;

std::vector<std::vector<long>> costMatrix(MAX_SIZE, std::vector<long>(MAX_SIZE));
std::vector<int> u(MAX_SIZE), v(MAX_SIZE), p(MAX_SIZE), way(MAX_SIZE);
long matrixSize;

void readCostMatrix(){
    std::cout << "Enter the size of the matrix: ";
    std::cin >> matrixSize;
    if (matrixSize < 1 || matrixSize > MAX_SIZE) {
        throw std::runtime_error("Matrix size must be between 1 and " + std::to_string(MAX_SIZE));
    }
    std::cout << "Enter the cost matrix (each row on a separate line, values separated by spaces):" << std::endl;
    for(long i = 0; i < matrixSize; i++)
        for(long j = 0; j < matrixSize; j++){
            std::cin >> costMatrix[i][j];
            if (costMatrix[i][j] < 0) {
                throw std::runtime_error("Costs must be non-negative");
            }
        }
}

void hungarianAlgorithm(){
    for (int i=1; i<=matrixSize; ++i) {
        p[0] = i;
        int j0 = 0;
        std::vector<int> minv (matrixSize+1, std::numeric_limits<int>::max());
        std::vector<char> used (matrixSize+1, false);
        do {
            used[j0] = true;
            int i0 = p[j0],  delta = std::numeric_limits<int>::max(),  j1;
            for (int j=1; j<=matrixSize; ++j)
                if (!used[j]) {
                    int cur = costMatrix[i0-1][j-1]-u[i0]-v[j];
                    if (cur < minv[j])
                        minv[j] = cur,  way[j] = j0;
                    if (minv[j] < delta)
                        delta = minv[j],  j1 = j;
                }
            for (int j=0; j<=matrixSize; ++j)
                if (used[j])
                    u[p[j]] += delta,  v[j] -= delta;
                else
                    minv[j] -= delta;
            j0 = j1;
        } while (p[j0] != 0);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }
}

void printResult(){
    long sum = 0;
    std::vector<int> ans (matrixSize+1);
    for (int i=1; i<=matrixSize; ++i){
        ans[p[i]] = i;
        sum += costMatrix[i-1][p[i]-1];
    }
    for (int i=1; i<=matrixSize; ++i){
        std::cout << "Agent " << i-1 << " is assigned to task " << ans[i]-1 << std::endl;
    }
    std::cout << "The minimum cost is: " << sum << std::endl;
}

int main()
{
    try {
        std::cout << "Reading cost matrix..." << std::endl;
        readCostMatrix();
        std::cout << "Applying Hungarian Algorithm..." << std::endl;
        hungarianAlgorithm();
        printResult();
        std::cout << "Algorithm completed successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
