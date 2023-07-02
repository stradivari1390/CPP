/** This C++ program implements a directed graph data structure and provides functionality to create,
 * display, and compare two such graphs checking isomorphism.
 * The nodes in these graphs are numbered (the numbers serve as keys)
 * and each node maintains a list of its connections (or arcs) to other nodes.
 *
 * It's important to mention that the isomorphic check in this program is a basic one and works correctly
 * only if the graphs are sorted and the nodes are labeled consecutively starting from 0. */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <limits>

class GraphNode {
public:
    int key;
    int count;
    GraphNode* next;
    std::vector<GraphNode*> trail;

    GraphNode(int key) : key(key), count(0), next(nullptr) {}
};

class Graph {
private:
    GraphNode* head;
    GraphNode* tail;
    std::vector<int> Fun;
    std::vector<int> NewFun;

    GraphNode* search(int key) {
        GraphNode* temp = head;
        while(temp) {
            if(temp->key == key) return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    bool findArc(int x, int y) {
        GraphNode* temp = search(x);
        if(temp == nullptr) return false;
        for(auto node : temp->trail) {
            if(node->key == y) return true;
        }
        return false;
    }

public:
    Graph() : head(nullptr), tail(nullptr) {}
    GraphNode* getHead() { return head; }
    GraphNode* getTail() { return tail; }

    void makeGraph() {
        int numNodes;
        std::cout << "Enter the number of nodes in the graph: ";
        while(!(std::cin >> numNodes)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter an integer: ";
        }

        for(int i=0; i<numNodes; i++) {
            GraphNode* node = new GraphNode(i);
            if(head == nullptr) {
                head = tail = node;
            } else {
                tail->next = node;
                tail = node;
            }
        }

        for(int i=0; i<numNodes; i++) {
            GraphNode* temp = search(i);
            int num_connections;
            std::cout << "Enter the number of connections for node " << i << ": ";
            while(!(std::cin >> num_connections)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter an integer: ";
            }
            for(int j=0; j<num_connections; j++) {
                int target;
                std::cout << "Enter the target node for connection " << j+1 << " of node " << i << ": ";
                while(!(std::cin >> target)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input. Please enter an integer: ";
                }
                if(target < 0 || target >= numNodes) {
                    std::cout << "Invalid node. Nodes should be between 0 and " << numNodes-1 << std::endl;
                    j--;
                    continue;
                }
                if(!findArc(i, target)) {
                    temp->trail.push_back(search(target));
                } else {
                    std::cout << "This connection already exists. Try again." << std::endl;
                    j--;
                }
            }
        }
    }

    void printGraph() {
        GraphNode* temp = head;
        while(temp) {
            std::cout << temp->key << " -> ";
            for(auto node : temp->trail) {
                std::cout << node->key << " ";
            }
            std::cout << std::endl;
            temp = temp->next;
        }
    }

    void sortGraph() {
        GraphNode* temp = head;
        while(temp) {
            std::sort(temp->trail.begin(), temp->trail.end(), [](GraphNode* a, GraphNode* b) { return a->key < b->key; });
            temp = temp->next;
        }
    }

    bool isomorphic(Graph& other) {
        GraphNode* temp1 = head;
        GraphNode* temp2 = other.getHead();

        while(temp1 != nullptr && temp2 != nullptr) {
            if(temp1->trail.size() != temp2->trail.size()) {
                return false;
            }

            for(int i=0; i<temp1->trail.size(); i++) {
                if(temp1->trail[i]->key != temp2->trail[i]->key) {
                    return false;
                }
            }

            temp1 = temp1->next;
            temp2 = temp2->next;
        }

        if(temp1 != nullptr || temp2 != nullptr) {
            return false;
        }

        return true;
    }

    friend void compareGraphs(Graph& A, Graph& B);
};

void compareGraphs(Graph& A, Graph& B) {
    GraphNode* tempA = A.getHead();
    GraphNode* tempB = B.getHead();
    int countA = 0, countB = 0;
    while(tempA) { countA++; tempA = tempA->next; }
    while(tempB) { countB++; tempB = tempB->next; }

    if(countA == countB) {
        std::cout << "Graphs A and B have the same number of nodes.\n";
    } else {
        std::cout << "Graphs A and B do not have the same number of nodes.\n";
    }
}

int main() {
    srand(time(0));
    Graph A, B;

    A.makeGraph();
    std::cout << "Graph A:\n";
    A.printGraph(); std::cout << std::endl;

    B.makeGraph();
    std::cout << "Graph B:\n";
    B.printGraph(); std::cout << std::endl;

    A.sortGraph();
    std::cout << "Graph A sorted:\n";
    A.printGraph(); std::cout << std::endl;

    B.sortGraph();
    std::cout << "Graph B sorted:\n";
    B.printGraph(); std::cout << std::endl;

    compareGraphs(A, B);

    if(A.isomorphic(B)) {
        std::cout << "Graphs A and B are isomorphic.\n";
    } else {
        std::cout << "Graphs A and B are not isomorphic.\n";
    }

    std::cin.get();
    return 0;
}