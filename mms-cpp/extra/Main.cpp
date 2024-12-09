#include <iostream>
#include <string>
#include "API.h"
using namespace std;

void setinitial(int x, int y);

int leftwalls[9][9]; //marks the presense of wall on left side of each cell.
int rightwalls[9][9]; //marks the presense of wall on right side of each cell.
int frontwalls[9][9]; // marks the front walls
int cellvalues[9][9]; // marks the value of each cell

void init_arrays();

struct LocationTrack // here it stores the neigbouring cells address and access them.
{
    /* data */
    int i,j;
    int value;
    int neighbour_val;
    LocationTrack* next;
    LocationTrack* prev;
};


void log(const std::string& message) {
    std::cerr << message << std::endl;
}

// Function to handle encountering a wall on the left
// void handleLeftWall() {
//     log("Wall on the left, turning left.");
//     API::turnLeft();
// }


int main() {
    log("started!");
    init_arrays();
    setinitial(8,8);
    

    return 0;  // Indicate successful execution (optional)
}

void setinitial(int x, int y){
    
    LocationTrack* head = new LocationTrack;
    head->i = x;
    head->j = y;
    head->value = 0;
    head->neighbour_val = -1;
     // Or whatever makes sense for your application
    head->next = nullptr;
    head->prev = nullptr;
    cellvalues[x][y] = 0; // Assuming this marks the initial cell
    API::setText(x, y, to_string(head->value));

    LocationTrack* current = head;
    LocationTrack* temp = current;
    LocationTrack* listHead = head;

    LocationTrack* lastAdded = nullptr;

    if(current->j+1<9){
                LocationTrack* newNode = new LocationTrack;
                newNode->i = current->i;
                newNode->j = current->j+1;
                newNode->value = current->value+1;
                newNode->neighbour_val = current->value;
                newNode->next = nullptr;
                newNode->prev = current;

                cellvalues[newNode->i][newNode->j] = newNode->value;
                API::setText(newNode->i, newNode->j, to_string(newNode->value));
                if (lastAdded != nullptr) {
                lastAdded->next = newNode;
                }
                lastAdded = newNode;
            };

            if(current->j-1>0){
                log("Passed the if 2");

                LocationTrack* newNode = new LocationTrack;
                newNode->i = current->i;
                newNode->j = current->j-1;
                newNode->value = current->value+1;
                newNode->neighbour_val = current->value;
                newNode->next = nullptr;
                newNode->prev = current;

                cellvalues[newNode->i][newNode->j] = newNode->value;
                API::setText(newNode->i, newNode->j, to_string(newNode->value));
                if (lastAdded != nullptr) {
                lastAdded->next = newNode;
                }
                lastAdded = newNode;
            };

            if(current->i+1<9){
                log("Passed the if 3");

                LocationTrack* newNode = new LocationTrack;
                newNode->i = current->i+1;
                newNode->j = current->j;
                newNode->value = current->value+1;
                newNode->neighbour_val = current->value;
                newNode->next = nullptr;
                newNode->prev = current;

                cellvalues[newNode->i][newNode->j] = newNode->value;
                API::setText(newNode->i, newNode->j, to_string(newNode->value));
                if (lastAdded != nullptr) {
                lastAdded->next = newNode;
                }
                lastAdded = newNode;
            };

            if(current->i-1>0){
                log("Passed the if 4");

                LocationTrack* newNode = new LocationTrack;
                newNode->i = current->i-1;
                newNode->j = current->j;
                newNode->value = current->value+1;
                newNode->neighbour_val = current->value;
                newNode->next = nullptr;
                newNode->prev = current;

                cellvalues[newNode->i][newNode->j] = newNode->value;
                API::setText(newNode->i, newNode->j, to_string(newNode->value));
                if (lastAdded != nullptr) {
                lastAdded->next = newNode;
                }
                lastAdded = newNode;
            };
            if (lastAdded != nullptr) {
            LocationTrack* tail = current; // Start with current as tail
            while (tail->next != nullptr) {
                tail = tail->next; // Move tail to the last node
            }
            tail->next = lastAdded; // Append lastAdded after the last node
        }
            
            current = current->next;
            delete temp;

    while(current != nullptr){
        log("Passed the while loop!");
        log(to_string(cellvalues[current->i][current->j]));
        
        LocationTrack* lastAdded = nullptr;

            if(current->j+1<9 && cellvalues[current->i][current->j+1] == 100){

                LocationTrack* newNode = new LocationTrack;
                newNode->i = current->i;
                newNode->j = current->j+1;
                newNode->value = current->value+1;
                newNode->neighbour_val = current->value;
                newNode->next = nullptr;
                newNode->prev = current;

                cellvalues[newNode->i][newNode->j] = newNode->value;
                API::setText(newNode->i, newNode->j, to_string(newNode->value));
                
                if (lastAdded != nullptr) {
                lastAdded->next = newNode;
                }
                lastAdded = newNode;
            };

            if(current->j-1>0 && cellvalues[current->i][current->j-1] == 100){

                LocationTrack* newNode = new LocationTrack;
                newNode->i = current->i;
                newNode->j = current->j-1;
                newNode->value = current->value+1;
                newNode->neighbour_val = current->value;
                newNode->next = nullptr;
                newNode->prev = current;

                cellvalues[newNode->i][newNode->j] = newNode->value;
                API::setText(newNode->i, newNode->j, to_string(newNode->value));
                
                if (lastAdded != nullptr) {
                lastAdded->next = newNode;
                }
                lastAdded = newNode;
            };

            if(current->i+1<9 && cellvalues[current->i+1][current->j] == 100){

                LocationTrack* newNode = new LocationTrack;
                newNode->i = current->i+1;
                newNode->j = current->j;
                newNode->value = current->value+1;
                newNode->neighbour_val = current->value;
                newNode->next = nullptr;
                newNode->prev = current;

                cellvalues[newNode->i][newNode->j] = newNode->value;
                API::setText(newNode->i, newNode->j, to_string(newNode->value));
                
                if (lastAdded != nullptr) {
                lastAdded->next = newNode;
                }
                lastAdded = newNode;
            };

            if(current->i-1>0 && cellvalues[current->i-1][current->j] == 100){

                LocationTrack* newNode = new LocationTrack;
                newNode->i = current->i-1;
                newNode->j = current->j;
                newNode->value = current->value+1;
                newNode->neighbour_val = current->value;
                newNode->next = nullptr;
                newNode->prev = current;

                cellvalues[newNode->i][newNode->j] = newNode->value;
                API::setText(newNode->i, newNode->j, to_string(newNode->value));
                
                if (lastAdded != nullptr) {
                lastAdded->next = newNode;
                }
                lastAdded = newNode;
            };

        if (lastAdded != nullptr) {
            LocationTrack* tail = current; // Start with current as tail
            while (tail->next != nullptr) {
                tail = tail->next; // Move tail to the last node
            }
            tail->next = lastAdded; // Append lastAdded after the last node
        }


        current = current->next;
    };

    current = head;
    while(current != nullptr){
        LocationTrack* temp = current;
        current = current->next;
        delete temp;
    }

};

void init_arrays(){
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            cellvalues[i][j] = 100;
        }
    }
}
