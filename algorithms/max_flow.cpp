/**
 * This program implements the Lift-to-Front algorithm for the maximum flow problem.
 * The algorithm is used to find the maximum flow in a flow network.
 * It uses the concepts of preflows, relabeling vertices, and pushing flow from one vertex to another.
 */

#include <iostream>
#include <vector>

using namespace std;

const int MaxN = 101;

struct ListNode {
    ListNode() = default;
    ListNode(int _value, ListNode* _next) : value(_value), next(_next) {}
    ListNode* next = nullptr;
    int value = 0;
};

vector<vector<int>> capacity(MaxN, vector<int>(MaxN, 0));
vector<vector<int>> flow(MaxN, vector<int>(MaxN, 0));
vector<int> excess(MaxN, 0);
vector<int> height(MaxN, 0);
vector<ListNode*> adjacencyList(MaxN);
vector<ListNode*> current(MaxN);
ListNode* listHead = nullptr;
ListNode* listPre = nullptr;
int numVertices, numEdges, source = 1, sink, minHeight;

void constructList();
int min(int a, int b);
void moveToFront(ListNode* node);
void initializePreflow();
void pushFlow(int u, int v);
void liftVertex(int u);
void discharge(int u);
void liftToFront();

void constructList() {
    ListNode* cur;
    auto* t = new ListNode(2, nullptr);
    listPre = listHead = t;
    cur = t;
    for (int i = 3; i < numVertices; i++) {
        auto* newNode = new ListNode(i, nullptr);
        cur->next = newNode;
        cur = cur->next;
    }
}

int min(int a, int b) {
    return a < b ? a : b;
}

void moveToFront(ListNode* node) {
    if (listPre == node) return;
    listPre->next = node->next;
    auto* t = new ListNode(node->value, listHead);
    listPre = listHead = t;
    delete node;
}

void initializePreflow() {
    height[source] = numVertices;
    for (int u = 1; u <= numVertices; u++) {
        if (capacity[source][u] > 0) {
            flow[source][u] = capacity[source][u];
            flow[u][source] = -capacity[source][u];
            excess[u] = capacity[source][u];
        }
    }
}

void pushFlow(int u, int v) {
    int d = min(excess[u], capacity[u][v] - flow[u][v]);
    flow[u][v] += d;
    flow[v][u] = -flow[u][v];
    excess[u] -= d;
    excess[v] += d;
}

void liftVertex(int u) {
    minHeight = 100000;
    ListNode* v = adjacencyList[u];
    while (v) {
        if (minHeight > height[v->value] && capacity[u][v->value] - flow[u][v->value] > 0)
            minHeight = height[v->value];
        v = v->next;
    }
    height[u] = minHeight + 1;
}

void discharge(int u) {
    while (excess[u] > 0) {
        ListNode* v = current[u];
        if (current[u] == nullptr) {
            liftVertex(u);
            current[u] = adjacencyList[u];
        } else if (capacity[u][v->value] - flow[u][v->value] > 0 && height[u] == height[v->value] + 1) {
            pushFlow(u, v->value);
        } else {
            current[u] = current[u]->next;
        }
    }
}

void liftToFront() {
    initializePreflow();
    constructList();
    for (int i = 2; i < numVertices; i++)
        current[i] = adjacencyList[i];
    ListNode* u = listHead;
    while (u != nullptr) {
        int old_height = height[u->value];
        discharge(u->value);
        if (height[u->value] > old_height) {
            moveToFront(u);
            u = listHead;
        }
        listPre = u;
        u = u->next;
    }
}

int main() {
    cout << "Welcome to the Lift-to-Front Maximum Flow Algorithm.\n";
    cout << "Please enter the number of vertices and edges in your flow network.\n";
    cout << "Number of vertices: ";
    cin >> numVertices;
    cout << "Number of edges: ";
    cin >> numEdges;

    cout << "\nNow, please enter the details for each edge in your network.\n";
    cout << "For each edge, provide the start vertex, end vertex, and capacity.\n";
    cout << "Enter these three values separated by spaces.\n";
    for (int i = 0; i < numEdges; i++) {
        cout << "Edge " << i+1 << ": ";
        int from, to, cap;
        cin >> from >> to >> cap;
        capacity[from][to] = cap;
    }

    // Construct the adjacency list for each vertex
    for (int i = 1; i <= numVertices; i++) {
        ListNode* currentNode = nullptr;
        bool firstNeighbor = true;
        for (int j = 1; j <= numVertices; j++) {
            if (capacity[i][j] > 0 || capacity[j][i] > 0) {
                auto* newNode = new ListNode(j, nullptr);
                if (firstNeighbor) {
                    adjacencyList[i] = newNode;
                    currentNode = newNode;
                    firstNeighbor = false;
                } else {
                    currentNode->next = newNode;
                    currentNode = currentNode->next;
                }
            }
        }
    }

    liftToFront();

    int totalFlow = 0;
    for (int i = 1; i <= numVertices; i++)
        totalFlow += flow[source][i];

    cout << "\nThe maximum flow from the source to the sink in your network is: " << totalFlow << endl;
    return 0;
}
