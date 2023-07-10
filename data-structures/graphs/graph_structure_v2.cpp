/**
 * @file graph.cpp
 * @brief This program demonstrates a simple graph data structure.
 * It allows the creation of graphs, adding/removing vertices and edges,
 * and checking if two graphs are isomorphic (simple way, without using of the Boost Graph Library (BGL)),
 * also it displays adjacency matrix.
 */

#include <iostream>
#include <vector>

class Graph {
    int numVertices;
    std::vector<std::vector<int>> adjacencyMatrix;

public:
    Graph(int numVertices);
    void addEdge(int startVertex, int endVertex);
    void removeEdge(int startVertex, int endVertex);
    void displayGraph();
    void checkIsomorphism(Graph& graph1, Graph& graph2);
};

Graph::Graph(int numVertices) : numVertices(numVertices) {
    adjacencyMatrix.resize(numVertices, std::vector<int>(numVertices, 0));
}

void Graph::addEdge(int startVertex, int endVertex) {
    if(startVertex <= numVertices && endVertex <= numVertices && startVertex > 0 && endVertex > 0) {
        if(startVertex == endVertex) {
            adjacencyMatrix[startVertex - 1][endVertex - 1] = 2;
        } else {
            adjacencyMatrix[startVertex - 1][endVertex - 1] = 1;
            adjacencyMatrix[endVertex - 1][startVertex - 1] = -1;
        }
    } else {
        std::cout << "Cannot add edge to non-existent vertex" << std::endl;
    }
}

void Graph::removeEdge(int startVertex, int endVertex) {
    if(startVertex <= numVertices && endVertex <= numVertices && startVertex > 0 && endVertex > 0) {
        adjacencyMatrix[startVertex - 1][endVertex - 1] = 0;
    } else {
        std::cout << "Cannot remove edge between non-existent vertices" << std::endl;
    }
}

void Graph::displayGraph() {
    for(int i = 0; i < numVertices; ++i) {
        for(int j = 0; j < numVertices; ++j) {
            std::cout << adjacencyMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Graph::checkIsomorphism(Graph& graph1, Graph& graph2) {
    if (graph1.numVertices != graph2.numVertices) {
        std::cout << "\n\nGraphs are not isomorphic\n\n";
        return;
    }

    for (int i = 0; i < graph1.numVertices; ++i) {
        for (int j = 0; j < graph1.numVertices; ++j) {
            if (graph1.adjacencyMatrix[i][j] != graph2.adjacencyMatrix[i][j]) {
                std::cout << "\n\nGraphs are not isomorphic\n\n";
                return;
            }
        }
    }

    std::cout << "\n\nGraphs are isomorphic\n\n";
}

int main() {
    int numVertices;
    std::cout << "Enter number of vertices for the first graph: ";
    std::cin >> numVertices;

    Graph graph1(numVertices);

    char operation;
    int startVertex, endVertex;
    do {
        std::cout << "Enter operation (a=add edge, r=remove edge, d=done): ";
        std::cin >> operation;

        switch(operation) {
            case 'a':
                std::cout << "Enter start vertex of edge: ";
                std::cin >> startVertex;
                std::cout << "Enter end vertex of edge: ";
                std::cin >> endVertex;
                graph1.addEdge(startVertex, endVertex);
                break;
            case 'r':
                std::cout << "Enter start vertex of edge: ";
                std::cin >> startVertex;
                std::cout << "Enter end vertex of edge: ";
                std::cin >> endVertex;
                graph1.removeEdge(startVertex, endVertex);
                break;
        }
    } while(operation != 'd');

    std::cout << "Enter number of vertices for the second graph: ";
    std::cin >> numVertices;

    Graph graph2(numVertices);

    do {
        std::cout << "Enter operation (a=add edge, r=remove edge, d=done): ";
        std::cin >> operation;

        switch(operation) {
            case 'a':
                std::cout << "Enter start vertex of edge: ";
                std::cin >> startVertex;
                std::cout << "Enter end vertex of edge: ";
                std::cin >> endVertex;
                graph2.addEdge(startVertex, endVertex);
                break;
            case 'r':
                std::cout << "Enter start vertex of edge: ";
                std::cin >> startVertex;
                std::cout << "Enter end vertex of edge: ";
                std::cin >> endVertex;
                graph2.removeEdge(startVertex, endVertex);
                break;
        }
    } while(operation != 'd');

    std::cout << "\nFirst Graph:\n";
    graph1.displayGraph();

    std::cout << "\nSecond Graph:\n";
    graph2.displayGraph();

    graph1.checkIsomorphism(graph1, graph2);

    return 0;
}
