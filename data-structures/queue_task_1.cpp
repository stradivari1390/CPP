/**
 * This program demonstrates the functionality of a queue data structure.
 * It initializes a queue, adds elements to it, and allows the user to search for an element.
 * The program then reports whether the searched element is in the lower, middle, or upper part of the queue.
 */

#include <iostream>

class Queue {
    int queue[11];
    int size, front, back;
public:
    void init();
    void enqueue(int);
    int dequeue();
    void search(int);
};

void Queue::init() {
    front = back = 0;
}

void Queue::enqueue(int value) {
    if (back == 11) {
        std::cout << "Queue is full.\n";
    } else {
        queue[back++] = value;
    }
}

int Queue::dequeue() {
    if (front == back) {
        std::cout << "Queue is empty.";
        return 0;
    } else {
        return queue[--back];
    }
}

void Queue::search(int element) {
    while ((element != queue[back]) && (back < 11)) {
        back++;
    }
    if (back == 11) {
        std::cout << "The element is not in the list.";
    } else if (back < 5) {
        std::cout << "The element is below the middle.";
    } else if (back == 5) {
        std::cout << "The element is in the middle.";
    } else {
        std::cout << "The element is above the middle.";
    }
}

int main() {
    int value, element;
    Queue q;
    q.init();
    std::cout << "\nAdding elements to the queue:\n";
    for(int i = 0; i < 11; i++) {
        q.enqueue(i * 2);
    }

    std::cout << "\nQueue:\n";
    for(int i = 0; i < 11; i++) {
        std::cout << q.dequeue() << "\n";
    }

    std::cout << "\nEnter an element to search:\n";
    std::cin >> element;
    q.search(element);
    return 0;
}
