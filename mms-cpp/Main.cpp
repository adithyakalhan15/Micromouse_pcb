#include <iostream>
#include <string>
#include "API.h"
#include <thread> // Include the thread header for sleep_for
#include <chrono> // Include the chrono header for duration types

#define TARGET_X 8
#define TARGET_Y 8

#define MAZE_SIZE 9

// have 4 directions N - 0, E - 1, S - 2, W - 3
// and have 16 different wall types.

using namespace std;
int direction = 0;
int currwall; // store the current direction and current cell's wall type.
int cellvalues[MAZE_SIZE][MAZE_SIZE];
int walls[MAZE_SIZE][MAZE_SIZE];
bool visited[MAZE_SIZE][MAZE_SIZE];
int nextMove[3]; // x-cordinate y-cordinate value

int currentx, currenty;

void init_arrays() {
  for (int i = 0; i < MAZE_SIZE; i++) {
    for (int j = 0; j < MAZE_SIZE; j++) {
      cellvalues[i][j] = 100;
    }
  }

  for (int i = 0; i < MAZE_SIZE; i++) {
    for (int j = 0; j < MAZE_SIZE; j++) {
      walls[i][j] = 15;
    }
  }

  for (int i = 0; i < MAZE_SIZE; i++) {
    for (int j = 0; j < MAZE_SIZE; j++) {
      visited[i][j] = false;
    }
  }
};

void resetwalls() {
  for (int i = 0; i < MAZE_SIZE; i++) {
    for (int j = 0; j < MAZE_SIZE; j++) {
      cellvalues[i][j] = 100;
    }
  }
}

struct Node {
  int i;
  int j;
  int val;
  int adj_val;
  bool isvisited = false;
  Node *next;
};

Node *createNode(int x, int y, int value, int adj_val) {
  Node *newNode = new Node;
  newNode->i = x;
  newNode->j = y;
  newNode->val = value;
  newNode->adj_val = adj_val;
  newNode->next = nullptr;
  return newNode;
};

Node *front = nullptr;
Node *rear = nullptr;

bool isEmpty() { return front == nullptr && rear == nullptr; };

void enqueue(int x, int y, int val, int adj_val) {
  Node *newNode = createNode(x, y, val, adj_val);
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
  Node *temp = front;  // Store the front node in a temporary variable
  front = front->next; // Move front to the next node
  delete temp;         // Free the memory occupied by the previous front node
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

void deleteLinkedList() {
  Node *current = front;
  Node *nextNode;

  while (current != nullptr) {
    nextNode =
        current->next;  // Save the next node before deleting the current one
    delete current;     // Free the memory occupied by the current node
    current = nextNode; // Move to the next node
  }

  // Reset front and rear pointers
  front = rear = nullptr;
};

void log(const std::string &message) { std::cerr << message << std::endl; };

void log2(const std::string &message1, const std::string &message2) {
  std::cerr << message1 << " " << message2 << std::endl;
};

// check wether the next right cell has walls combination.
bool isWallRight(int x, int y) {
  if (walls[x][y] == 1 || walls[x][y] == 5 || walls[x][y] == 8 ||
      walls[x][y] == 9 || walls[x][y] == 11 || walls[x][y] == 13 ||
      walls[x][y] == 14) {
    return true;
  } else {
    return false;
  }
};

bool isWallLeft(int x, int y) {
  if (walls[x][y] == 3 || walls[x][y] == 6 || walls[x][y] == 7 ||
      walls[x][y] == 9 || walls[x][y] == 11 || walls[x][y] == 12 ||
      walls[x][y] == 13) {
    return true;
  } else {
    return false;
  }
}

bool isWallUp(int x, int y) {
  if (walls[x][y] == 4 || walls[x][y] == 5 || walls[x][y] == 6 ||
      walls[x][y] == 10 || walls[x][y] == 11 || walls[x][y] == 12 ||
      walls[x][y] == 14) {
    return true;
  } else {
    return false;
  }
}

bool isWallDown(int x, int y) {
  if (walls[x][y] == 2 || walls[x][y] == 7 || walls[x][y] == 8 ||
      walls[x][y] == 10 || walls[x][y] == 12 || walls[x][y] == 13 ||
      walls[x][y] == 14) {
    return true;
  } else {
    return false;
  }
}

void floodfill(int m, int n) { // main flood fill code is here m,n is
                               // codinations of the destination
  resetwalls();
  enqueue(m, n, 0, -1);
  log(to_string(front->val));
  cellvalues[m][n] = 0;
  API::setText(m, n, to_string(front->val));

  while (!isEmpty()) {
    int x = front->i;
    int y = front->j;
    // log("front value :");
    // log2(to_string(x), to_string(y));
    int fval = front->val;

    dequeue();

    if (x + 1 < MAZE_SIZE && !isWallRight(x + 1, y) &&
        cellvalues[x + 1][y] == 100) {
      enqueue(x + 1, y, fval + 1, fval);
      API::setText(x + 1, y, to_string(fval + 1));
      cellvalues[x + 1][y] = fval + 1;
    }

    if (x - 1 >= 0 && !isWallLeft(x - 1, y) && cellvalues[x - 1][y] == 100) {
      enqueue(x - 1, y, fval + 1, fval);
      API::setText(x - 1, y, to_string(fval + 1));
      cellvalues[x - 1][y] = fval + 1;
    }

    if (y + 1 < MAZE_SIZE && !isWallUp(x, y + 1) &&
        cellvalues[x][y + 1] == 100) {
      enqueue(x, y + 1, fval + 1, fval);
      API::setText(x, y + 1, to_string(fval + 1));
      cellvalues[x][y + 1] = fval + 1;
    }

    if (y - 1 >= 0 && !isWallDown(x, y - 1) && cellvalues[x][y - 1] == 100) {
      enqueue(x, y - 1, fval + 1, fval);
      API::setText(x, y - 1, to_string(fval + 1));
      cellvalues[x][y - 1] = fval + 1;
    }
  }

  deleteLinkedList();
};

void floodfill2(int m, int n) { // main flood fill code is here m,n is
                                // codinations of the destination
  resetwalls();
  enqueue(m, n, 0, -1);
  log(to_string(front->val));
  API::setText(m, n, to_string(front->val));
  cellvalues[m][n] = 0;

  while (front->val != 15) {
    int x = getFront();
    int y = front->j;
    log("front value :");
    log2(to_string(x), to_string(y));
    int fval = front->val;
    log2("Current cell value :", to_string(fval));

    dequeue();

    if (x + 1 < 9 && cellvalues[x + 1][y] == 100) {
      enqueue(x + 1, y, fval + 1, fval);
      API::setText(x + 1, y, to_string(x + 1));
      cellvalues[x + 1][y] = fval + 1;
    }

    if (x - 1 >= 0 && cellvalues[x - 1][y] == 100) {
      enqueue(x - 1, y, fval + 1, fval);
      API::setText(x - 1, y, to_string(x + 1));
      cellvalues[x - 1][y] = fval + 1;
    }

    if (y + 1 < 9 && cellvalues[x][y + 1] == 100) {
      enqueue(x, y + 1, fval + 1, fval);
      API::setText(x, y + 1, to_string(x + 1));
      cellvalues[x][y + 1] = fval + 1;
    }

    if (y - 1 >= 0 && cellvalues[x][y - 1] == 100) {
      enqueue(x, y - 1, fval + 1, fval);
      API::setText(x, y - 1, to_string(x + 1));
      cellvalues[x][y - 1] = fval + 1;
    }
  }

  log("update done");
};

void delay(int milliseconds) {
  this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

void handleMoveForward() {
  API::moveForward();

  if (direction == 0 && currenty < MAZE_SIZE - 1) {
    currenty++;
  } else if (direction == 2 && currenty > 0) {
    currenty--;
  } else if (direction == 1 && currentx < 8) {
    currentx++;
  } else if (direction == 3 && currentx > 0) {
    currentx--;
  }
}

void handleTR() { // handles the Turn right action.
  API::turnRight();
  direction = (direction + 1) % 4;
  handleMoveForward();
};

void handleTL() { // handle the turn left action.
  API::turnLeft();
  direction = (direction - 1) % 4;
  if (direction < 0) {
    direction = direction + 4;
  }
  handleMoveForward();
};

void handle180() {
  API::turnLeft();
  API::turnLeft();
  direction = (direction - 2) % 4;
  if (direction < 0) {
    direction = direction + 4;
  }
  handleMoveForward();
};

bool CheckFront() { // handle the api and return the front wall or not

  if (API::wallFront()) {
    return true;
  } else {
    return false;
  }
};

bool CheckRight() { // handle the api and return the right wall or not

  if (API::wallRight()) {
    return true;
  } else {
    return false;
  }
};

bool CheckLeft() { // handle the api and return the left wall or not

  if (API::wallLeft()) {
    return true;
  } else {
    return false;
  }
};

// this code segment to check the 3 sensor status and get walls.
int checkwalls(int direction) { // check the walls combination.
  if (direction == 0) {
    if (CheckLeft() && !CheckFront() && !CheckRight()) {
      API::setWall(currentx, currenty, 'w');
      return 1;
    } else if (!CheckLeft() && CheckFront() && !CheckRight()) {
      API::setWall(currentx, currenty, 'n');
      return 2;
    } else if (!CheckLeft() && !CheckFront() && CheckRight()) {
      API::setWall(currentx, currenty, 'e');
      return 3;
    } else if (!CheckLeft() && CheckFront() && CheckRight()) {
      API::setWall(currentx, currenty, 'e');
      API::setWall(currentx, currenty, 'n');
      return 7;
    } else if (CheckLeft() && CheckFront() && !CheckRight()) {
      API::setWall(currentx, currenty, 'w');
      API::setWall(currentx, currenty, 'n');
      return 8;
    } else if (CheckLeft() && !CheckFront() && CheckRight()) {
      API::setWall(currentx, currenty, 'w');
      API::setWall(currentx, currenty, 'e');
      return 9;
    } else if ((CheckLeft() && CheckFront() && CheckRight())) {
      API::setWall(currentx, currenty, 'w');
      API::setWall(currentx, currenty, 'n');
      API::setWall(currentx, currenty, 'e');
      return 13;
    } else {
      return 15;
    }
  }

  if (direction == 1) {
    if (CheckLeft() && !CheckFront() && !CheckRight()) {
      API::setWall(currentx, currenty, 'n');
      return 2;
    } else if (!CheckLeft() && CheckFront() && !CheckRight()) {
      API::setWall(currentx, currenty, 'e');
      return 3;
    } else if (!CheckLeft() && !CheckFront() && CheckRight()) {
      API::setWall(currentx, currenty, 's');
      return 4;
    } else if (!CheckLeft() && CheckFront() && CheckRight()) {
      API::setWall(currentx, currenty, 'e');
      API::setWall(currentx, currenty, 's');
      return 6;
    } else if (CheckLeft() && CheckFront() && !CheckRight()) {
      API::setWall(currentx, currenty, 'e');
      API::setWall(currentx, currenty, 'n');
      return 7;
    } else if (CheckLeft() && !CheckFront() && CheckRight()) {
      API::setWall(currentx, currenty, 's');
      API::setWall(currentx, currenty, 'n');
      return 10;
    } else if (CheckLeft() && CheckFront() && CheckRight()) {
      API::setWall(currentx, currenty, 'e');
      API::setWall(currentx, currenty, 'n');
      API::setWall(currentx, currenty, 's');
      return 12;
    } else {
      return 15;
    }
  }

  if (direction == 2) {
    if (!CheckLeft() && !CheckFront() && CheckRight()) {
      API::setWall(currentx, currenty, 'w');
      return 1;
    } else if (CheckLeft() && !CheckFront() && !CheckRight()) {
      API::setWall(currentx, currenty, 'e');
      return 3;
    } else if (!CheckLeft() && CheckFront() && !CheckRight()) {
      API::setWall(currentx, currenty, 's');
      return 4;
    } else if (!CheckLeft() && CheckFront() && CheckRight()) {
      API::setWall(currentx, currenty, 'w');
      API::setWall(currentx, currenty, 's');
      return 5;
    } else if (CheckLeft() && CheckFront() && !CheckRight()) {
      API::setWall(currentx, currenty, 'e');
      API::setWall(currentx, currenty, 's');
      return 6;
    } else if (CheckLeft() && !CheckFront() && CheckRight()) {
      API::setWall(currentx, currenty, 'e');
      API::setWall(currentx, currenty, 'w');
      return 9;
    } else if (CheckLeft() && CheckFront() && CheckRight()) {
      API::setWall(currentx, currenty, 'e');
      API::setWall(currentx, currenty, 's');
      API::setWall(currentx, currenty, 'w');
      return 11;
    } else {
      return 15;
    }
  }

  if (direction == 3) {
    if (!CheckLeft() && CheckFront() && !CheckRight()) {
      API::setWall(currentx, currenty, 'w');
      return 1;
    } else if (!CheckLeft() && !CheckFront() && CheckRight()) {
      API::setWall(currentx, currenty, 'n');
      return 2;
    } else if (CheckLeft() && !CheckFront() && !CheckRight()) {
      API::setWall(currentx, currenty, 's');
      return 4;
    } else if (CheckLeft() && CheckFront() && !CheckRight()) {
      API::setWall(currentx, currenty, 'w');
      API::setWall(currentx, currenty, 's');
      return 5;
    } else if (!CheckLeft() && CheckFront() && CheckRight()) {
      API::setWall(currentx, currenty, 'w');
      API::setWall(currentx, currenty, 'n');
      return 8;
    } else if (CheckLeft() && !CheckFront() && CheckRight()) {
      API::setWall(currentx, currenty, 'n');
      API::setWall(currentx, currenty, 's');
      return 10;
    } else if (CheckLeft() && CheckFront() && CheckRight()) {
      API::setWall(currentx, currenty, 'w');
      API::setWall(currentx, currenty, 'n');
      API::setWall(currentx, currenty, 's');
      return 14;
    } else {
      return 15;
    }
  }

  return 0;
};

int findMin(int a, int b, int c, int d) {
  int min = a; // Assume 'a' is the minimum initially

  // Compare 'b', 'c', and 'd' with the current minimum
  if (b < min)
    min = b;
  if (c < min)
    min = c;
  if (d < min)
    min = d;

  return min;
}

int findMin(int a, int b, int c) {
  int min = a; // Assume 'a' is the minimum initially

  // Compare 'b' and 'c' with the current minimum
  if (b < min)
    min = b;
  if (c < min)
    min = c;

  return min;
};

int findMin(int a, int b) { return (a < b) ? a : b; }

void momentDecider(int walltype) {
  if (direction == 0) {
    if (walltype == 1 || walltype == 3 || walltype == 4 || walltype == 5 ||
        walltype == 6 || walltype == 9 || walltype == 11 || walltype == 15) {
      handleMoveForward();
    } else if (walltype == 8 || walltype == 2) {
      handleTR();

    } else if (walltype == 7) {
      handleTL();

    } else if (walltype == 13) {
      handle180();
    }
  }
  if (direction == 1) {
    if (walltype == 1 || walltype == 2 || walltype == 4 || walltype == 5 ||
        walltype == 8 || walltype == 10 || walltype == 14 || walltype == 15) {
      handleMoveForward();
    } else if (walltype == 3 || walltype == 6) {
      handleTL();

    } else if (walltype == 7) {
      handleTR();

    } else if (walltype == 12) {
      handle180();
    }
  }
  if (direction == 2) {
    if (walltype == 1 || walltype == 2 || walltype == 3 || walltype == 7 ||
        walltype == 8 || walltype == 9 || walltype == 13 || walltype == 15) {
      handleMoveForward();
    } else if (walltype == 4 || walltype == 5) {
      handleTL();

    } else if (walltype == 6) {
      handleTR();

    } else if (walltype == 11) {
      handle180();
    }
  }
  if (direction == 3) {
    if (walltype == 2 || walltype == 3 || walltype == 4 || walltype == 6 ||
        walltype == 7 || walltype == 10 || walltype == 12 || walltype == 15) {
      handleMoveForward();
    } else if (walltype == 8 || walltype == 1) {
      handleTL();

    } else if (walltype == 5) {
      handleTR();

    } else if (walltype == 14) {
      handle180();
    }
  }
}

void moveToNext(int dir, int cx, int cy, int nx, int ny) {
  int dx = nx - cx;
  int dy = ny - cy;

  log2("direction at decider:", to_string(direction));

  if (dir == 0) {
    if (dy > 0) {
      handleMoveForward();
    } else if (dy < 0) {
      handle180();
    } else if (dx > 0) {
      handleTR();
      log("turned right");
      log2("direction : ", to_string(direction));
    } else {
      handleTL();
    }
  } else if (dir == 1) {
    if (dy > 0) {
      handleTL();
    } else if (dy < 0) {
      handleTR();
    } else if (dx > 0) {
      handleMoveForward();
    } else {
      handle180();
    }
  } else if (dir == 2) {
    if (dy > 0) {
      handle180();
    } else if (dy < 0) {
      handleMoveForward();
    } else if (dx > 0) {
      handleTL();
    } else {
      handleTR();
    }
  } else {
    if (dy > 0) {
      handleTR();
    } else if (dy < 0) {
      handleTL();
    } else if (dx > 0) {
      handle180();
    } else {
      handleMoveForward();
    }
  }
}

void MovementFinder(int walltype, int x, int y) {

  if (walltype == 13 || walltype == 14 || walltype == 12 || walltype == 11) {
    handle180();
  } else if (walltype == 15) {
    int ex = findMin(cellvalues[x + 1][y], cellvalues[x - 1][y],
                     cellvalues[x][y + 1], cellvalues[x][y - 1]);
    if (ex == cellvalues[x + 1][y] && x + 1 < MAZE_SIZE) {
      moveToNext(direction, currentx, currenty, currentx + 1, currenty);
    } else if (ex == cellvalues[x - 1][y] && x - 1 >= 0) {
      moveToNext(direction, currentx, currenty, currentx - 1, currenty);
    } else if (ex == cellvalues[x][y + 1] && y + 1 < MAZE_SIZE) {
      moveToNext(direction, currentx, currenty, currentx, currenty + 1);
    } else if (ex == cellvalues[x][y - 1] && y - 1 >= 0) {
      moveToNext(direction, currentx, currenty, currentx, currenty - 1);
    }
  } else if (walltype == 1 || walltype == 2 || walltype == 3 || walltype == 4) {
    if (walltype == 1) {
      int ex = findMin(cellvalues[x + 1][y], cellvalues[x][y + 1],
                       cellvalues[x][y - 1]);
      if (ex == cellvalues[x + 1][y] && x + 1 < MAZE_SIZE) {
        moveToNext(direction, currentx, currenty, currentx + 1, currenty);
      } else if (ex == cellvalues[x][y + 1] && y + 1 < MAZE_SIZE) {
        moveToNext(direction, currentx, currenty, currentx, currenty + 1);
      } else if (ex == cellvalues[x][y - 1] && y - 1 >= 0) {
        moveToNext(direction, currentx, currenty, currentx, currenty - 1);
      }
    } else if (walltype == 2) {
      int ex = findMin(cellvalues[x + 1][y], cellvalues[x - 1][y],
                       cellvalues[x][y - 1]);
      if (ex == cellvalues[x + 1][y] && x + 1 < MAZE_SIZE) {
        moveToNext(direction, currentx, currenty, currentx + 1, currenty);
      } else if (ex == cellvalues[x][y - 1] && y - 1 >= 0) {
        moveToNext(direction, currentx, currenty, currentx, currenty - 1);
      } else if (ex == cellvalues[x - 1][y] && x - 1 >= 0) {
        moveToNext(direction, currentx, currenty, currentx - 1, currenty);
      }
    } else if (walltype == 3) {
      int ex = findMin(cellvalues[x - 1][y], cellvalues[x][y + 1],
                       cellvalues[x][y - 1]);
      if (ex == cellvalues[x - 1][y] && x - 1 >= 0) {
        moveToNext(direction, currentx, currenty, currentx - 1, currenty);
      } else if (ex == cellvalues[x][y + 1] && y + 1 < MAZE_SIZE) {
        moveToNext(direction, currentx, currenty, currentx, currenty + 1);
      } else if (ex == cellvalues[x][y - 1] && y - 1 >= 0) {
        moveToNext(direction, currentx, currenty, currentx, currenty - 1);
      }
    } else {
      int ex = findMin(cellvalues[x + 1][y], cellvalues[x - 1][y],
                       cellvalues[x][y + 1]);
      if (ex == cellvalues[x + 1][y] && x + 1 < MAZE_SIZE) {
        moveToNext(direction, currentx, currenty, currentx + 1, currenty);
      } else if (ex == cellvalues[x - 1][y] && x - 1 >= 0) {
        moveToNext(direction, currentx, currenty, currentx - 1, currenty);
      } else if (ex == cellvalues[x][y + 1] && y + 1 < MAZE_SIZE) {
        moveToNext(direction, currentx, currenty, currentx, currenty + 1);
      }
    }

  } else if (walltype == 5 || walltype == 6 || walltype == 7 || walltype == 8) {
    if (walltype == 5) {
      int ex = findMin(cellvalues[x + 1][y], cellvalues[x][y + 1]);
      if (ex == cellvalues[x + 1][y] && x + 1 < MAZE_SIZE) {
        moveToNext(direction, currentx, currenty, currentx + 1, currenty);
      } else if (ex == cellvalues[x][y + 1] && y + 1 < MAZE_SIZE) {
        moveToNext(direction, currentx, currenty, currentx, currenty + 1);
      }
    } else if (walltype == 6) {
      int ex = findMin(cellvalues[x - 1][y], cellvalues[x][y + 1]);
      if (ex == cellvalues[x - 1][y] && x - 1 >= 0) {
        moveToNext(direction, currentx, currenty, currentx - 1, currenty);
      } else if (ex == cellvalues[x][y + 1] && y + 1 < MAZE_SIZE) {
        moveToNext(direction, currentx, currenty, currentx, currenty + 1);
      }
    } else if (walltype == 7) {
      int ex = findMin(cellvalues[x - 1][y], cellvalues[x][y - 1]);
      if (ex == cellvalues[x - 1][y] && x - 1 >= 0) {
        moveToNext(direction, currentx, currenty, currentx - 1, currenty);
      } else if (ex == cellvalues[x][y - 1] && y - 1 >= 0) {
        moveToNext(direction, currentx, currenty, currentx, currenty - 1);
      }
    } else if (walltype == 8) {
      int ex = findMin(cellvalues[x + 1][y], cellvalues[x][y - 1]);
      if (ex == cellvalues[x + 1][y] && x + 1 < MAZE_SIZE) {
        moveToNext(direction, currentx, currenty, currentx + 1, currenty);
      } else if (ex == cellvalues[x][y - 1] && y - 1 >= 0) {
        moveToNext(direction, currentx, currenty, currentx, currenty - 1);
      }
    }
  } else if (walltype == 9 || walltype == 10) {
    handleMoveForward();
  }
};

void moveRobot(int targetx, int targety) { // make robot move
  while ((currentx != targetx) || (currenty != targety)) {
    walls[currentx][currenty] = checkwalls(direction);
    visited[currentx][currenty] = true;
    currwall = walls[currentx][currenty];
    // jsut for test
    // log(to_string(CheckFront()));
    // log(to_string(CheckLeft()));
    // log(to_string(CheckRight()));
    // log("direction");
    // log(to_string(direction));
    log("wall setup");
    log(to_string(currwall));
    floodfill(TARGET_X, TARGET_Y);
    // log2("value of dest :", to_string(cellvalues[TARGET_X][TARGET_Y]));
    // momentDecider(currwall);
    MovementFinder(currwall, currentx, currenty);
    log2(to_string(currentx), to_string(currenty));
    delay(100);
  }
};

int main() {
  log("started!");
  init_arrays();
  // API::setWall(0, 0, 'e');
  // API::setWall(0, 1, 'e');
  // API::moveForward();
  // API::moveForward();

  // API::turnRight();
  // API::setWall(0, 2, 'n');
  // API::moveForward();
  // API::setWall(1,2, 'n');
  moveRobot(TARGET_X, TARGET_Y);
  // floodfill(8,8);

  return 0;
}
