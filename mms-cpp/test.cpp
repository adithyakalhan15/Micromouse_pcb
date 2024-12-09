#include <iostream>
using namespace std;

// Define a struct for the nodes of the linked list
struct Node {
    int data;
    Node* next;
};

// Function to create a new node with given data
Node* createNode(int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;
    return newNode;
}

Node* front = nullptr; // Pointer to the front of the queue
Node* rear = nullptr;  // Pointer to the rear of the queue

// Function to check if the queue is empty
bool isEmpty() {
    return front == nullptr && rear == nullptr;
}

// Function to add an element to the queue (enqueue)
void enqueue(int value) {
    Node* newNode = createNode(value);
    if (isEmpty()) {
        front = rear = newNode; // If queue is empty, newNode is both front and rear
    } else {
        rear->next = newNode; // Add newNode after the current rear
        rear = newNode;       // Update rear to newNode
    }
}

// Function to remove an element from the queue (dequeue)
void dequeue() {
    if (isEmpty()) {
        cout << "Queue is empty. Cannot dequeue.\n";
        return;
    }
    Node* temp = front; // Store the front node in a temporary variable
    front = front->next; // Move front to the next node
    delete temp; // Free the memory occupied by the previous front node
    if (front == nullptr) {
        rear = nullptr; // If queue becomes empty after dequeue, update rear
    }
}

// Function to get the front element of the queue
int getFront() {
    if (isEmpty()) {
        cout << "Queue is empty.\n";
        return -1;
    }
    return front->data;
}

// Function to display the elements of the queue
void display() {
    if (isEmpty()) {
        cout << "Queue is empty.\n";
        return;
    }
    cout << "Queue: ";
    Node* current = front;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

int main() {
    // Enqueue elements
    enqueue(1);
    enqueue(2);
    enqueue(3);

    // Display the queue
    display(); // Output: Queue: 1 2 3

    // Dequeue an element
    dequeue();

    enqueue(4);
    enqueue(5);

    // Display the queue after dequeue
    display(); // Output: Queue: 2 3

    // Get the front element
    cout << "Front element: " << getFront() << endl; // Output: Front element: 2

    return 0;
}
