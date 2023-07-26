/**
 * @file QueueSorter.cpp
 * @brief This file contains a QueueSorter class that implements a queue data structure with sorting functionality.
 */

#include <iostream>
#include <vector>
#include <algorithm>

class QueueSorter {
    std::vector<int> queue;
public:
    void enqueue(int item);
    int dequeue();
    void sortQueue();
};

void QueueSorter::enqueue(int item) {
    if(queue.size() == 10) {
        std::cout << "Queue is already full\n";
    } else {
        queue.push_back(item);
    }
}

int QueueSorter::dequeue() {
    if(queue.empty()) {
        std::cout << "Queue is empty\n";
        return 0;
    } else {
        int item = queue.back();
        queue.pop_back();
        return item;
    }
}

void QueueSorter::sortQueue() {
    std::sort(queue.begin(), queue.end());
}

int main() {
    QueueSorter queueSorter;
    int item;

    for(int i = 0; i < 10; i++) {
        std::cin >> item;
        queueSorter.enqueue(item);
    }

    queueSorter.sortQueue();

    for(int i = 0; i < 10; i++) {
        std::cout << queueSorter.dequeue() << "\n";
    }

    return 0;
}
