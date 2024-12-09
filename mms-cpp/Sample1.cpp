#include <iostream>
#include <string>
#include "API.h"
using namespace std;

int cellvalues[9][9];
int walls[9][9];

void init_arrays(){
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            cellvalues[i][j] = 100;
        }
    }

    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            walls[i][j] = 15;  
        }
    }
};

struct Node{
    int i;
    int j;
    int val;
    int adj_val;
    Node* next;
};

Node* createNode(int x, int y, int value, int adj_val){
    Node* newNode = new Node;
    newNode->i=x;
    newNode->j=y;
    newNode->val = value;
    newNode->adj_val = adj_val;
    newNode->next = nullptr;
    return newNode;
};

Node* front = nullptr;
Node* rear = nullptr;

bool isEmpty() {
    return front == nullptr && rear == nullptr;
};

void enqueue(int x, int y, int val, int adj_val) {
    Node* newNode = createNode(x, y, val, adj_val);
    if (isEmpty()) {
        front = rear = newNode; // If queue is empty, newNode is both front and rear
    } else {
        rear->next = newNode; // Add newNode after the current rear
        rear = newNode;       // Update rear to newNode
    }
};

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
};

int getFront() {
    if (isEmpty()) {
        cout << "Queue is empty.\n";
        return -1;
    }
    return front->i;
};

void log(const std::string& message) {
    std::cerr << message << std::endl;
};

void initialize(int m, int n){
    enqueue(m,n,0,-1);
    log(to_string(front->val));
    API::setText(m, n, to_string(front->val));
    cellvalues[m][n] = 0;

        if(front->i+1<9 && cellvalues[front->i+1][front->j] == 100){
            log("right");
            enqueue(front->i+1, front->j, front->val+1, front->val);
            API::setText(front->i+1, front->j, to_string(front->val+1));
            cellvalues[front->i+1][front->j] = front->val+1;
        }

        if(front->i-1>=0 && cellvalues[front->i-1][front->j] == 100){
            log("left");
            enqueue(front->i-1, front->j, front->val+1, front->val);
            API::setText(front->i-1, front->j, to_string(front->val+1));
            cellvalues[front->i-1][front->j] = front->val+1;
        }

        if(front->j+1<9 && cellvalues[front->i][front->j+1] == 100){
            log("up");
            enqueue(front->i, front->j+1, front->val+1, front->val);
            API::setText(front->i, front->j+1, to_string(front->val+1));
            cellvalues[front->i][front->j+1] = front->val+1;
        }

        if(front->j-1>=0 && cellvalues[front->i][front->j-1] == 100){
            log("down");
            enqueue(front->i, front->j-1, front->val+1, front->val);
            API::setText(front->i, front->j-1, to_string(front->val+1));
            cellvalues[front->i][front->j-1] = front->val+1;
        }

        dequeue();

    while(front != nullptr){
        if(front->i+1<9 && cellvalues[front->i+1][front->j] == 100){
            log("right");
            enqueue(front->i+1, front->j, front->val+1, front->val);
            API::setText(front->i+1, front->j, to_string(front->val+1));
            cellvalues[front->i+1][front->j] = front->val+1;
        }

        if(front->i-1>=0 && cellvalues[front->i-1][front->j] == 100){
            log("left");
            enqueue(front->i-1, front->j, front->val+1, front->val);
            API::setText(front->i-1, front->j, to_string(front->val+1));
            cellvalues[front->i-1][front->j] = front->val+1;
        }

        if(front->j+1<9 && cellvalues[front->i][front->j+1] == 100){
            log("up");
            enqueue(front->i, front->j+1, front->val+1, front->val);
            API::setText(front->i, front->j+1, to_string(front->val+1));
            cellvalues[front->i][front->j+1] = front->val+1;
        }

        if(front->j-1>=0 && cellvalues[front->i][front->j-1] == 100){
            log("down");
            enqueue(front->i, front->j-1, front->val+1, front->val);
            API::setText(front->i, front->j-1, to_string(front->val+1));
            cellvalues[front->i][front->j-1] = front->val+1;
        }

        dequeue();
    };
    log("assigning completed!");
};

void findpathRobot(){
    int m,n = 0;
    int robot_dir = 0;
    
    while(cellvalues[m][n] != 0){

    }
}

int main(){
    log("started!");
    init_arrays();
    initialize(8,8);
    return 0;
};