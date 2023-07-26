/**
 * @file MaxFlowAlgorithm.cpp
 * @brief This program implements the preflow-push maximum flow algorithm.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

const int MAX_NODES = 2000;

std::vector<int> excessFlow(MAX_NODES), height(MAX_NODES);
std::vector<std::vector<int>> capacity(MAX_NODES, std::vector<int>(MAX_NODES));
int numNodes, source, sink;

void push(int fromNode, int toNode)
{
    int flow = std::min(excessFlow[fromNode], capacity[fromNode][toNode]);
    excessFlow[fromNode] -= flow;
    excessFlow[toNode] += flow;
    capacity[fromNode][toNode] -= flow;
    capacity[toNode][fromNode] += flow;
}

void lift(int node)
{
    int minHeight = 3 * numNodes + 1;

    for (int i = 0; i < numNodes; i++)
        if (capacity[node][i] && (height[i] < minHeight))
            minHeight = height[i];

    height[node] = minHeight + 1;
}

void discharge(int node)
{
    int neighbour = 0;
    while (excessFlow[node] > 0)
    {
        if (capacity[node][neighbour] && height[node] == height[neighbour] + 1)
        {
            push(node, neighbour);
            neighbour = 0;
            continue;
        }
        neighbour++;
        if (neighbour == numNodes)
        {
            lift(node);
            neighbour = 0;
        }
    }
}

void readNetwork()
{
    std::cin >> numNodes >> source >> sink;

    for (int i = 0; i < numNodes; i++)
        for (int j = 0; j < numNodes; j++)
        {
            if (i == j)
                continue;
            std::cin >> capacity[i][j];
        }
}

void initialize()
{
    readNetwork();
    for (int i = 0; i < numNodes; i++)
    {
        if (i == source)
            continue;
        excessFlow[i] = capacity[source][i];
        capacity[i][source] += capacity[source][i];
    }
    height[source] = numNodes;
}

int main()
{
    std::list<int> activeNodes;
    std::list<int>::iterator currentNode;
    int oldHeight;

    initialize();

    for (int i = 0; i < numNodes; i++)
        if (i != source && i != sink)
            activeNodes.push_front(i);

    currentNode = activeNodes.begin();

    while (currentNode != activeNodes.end())
    {
        oldHeight = height[*currentNode];
        discharge(*currentNode);
        if (height[*currentNode] != oldHeight)
        {
            activeNodes.push_front(*currentNode);
            currentNode = activeNodes.erase(currentNode);
        }
        else
        {
            ++currentNode;
        }
    }

    std::cout << "Maximum flow from source to sink is: " << excessFlow[sink] << std::endl;
    return 0;
}
