#include <iostream>
#include "Main.cpp"

using namespace std;

void floodfill(int m, int n){ //main flood fill code is here m,n is codinations of the destination
    resetwalls();
    enqueue(m,n,0,-1);
    log(to_string(front->val));
    cellvalues[m][n] = 0;
    API::setText(m, n, to_string(front->val));
    

    while(!isEmpty()){
        int x = front->i;
        int y = front->j;
        // log("front value :");
        // log2(to_string(x), to_string(y));
        int fval = front->val;

        dequeue();

    if(x+1<MAZE_SIZE && !isWallRight(x+1, y) && cellvalues[x+1][y] == 100){
        enqueue(x+1, y, fval+1, fval);
        API::setText(x+1, y, to_string(fval+1));
        cellvalues[x+1][y] = fval+1;
    }

    if(x-1>=0 && !isWallLeft(x-1, y) && cellvalues[x-1][y] == 100){
        enqueue(x-1, y, fval+1, fval);
        API::setText(x-1, y, to_string(fval+1));
        cellvalues[x-1][y] = fval+1;
    }

    if(y+1<MAZE_SIZE && !isWallUp(x, y+1) && cellvalues[x][y+1] == 100){
        enqueue(x, y+1, fval+1, fval);
        API::setText(x, y+1, to_string(fval+1));
        cellvalues[x][y+1] = fval+1;
    }

    if(y-1>=0 && !isWallDown(x, y-1) && cellvalues[x][y-1] == 100){
        enqueue(x, y-1, fval+1, fval);
        API::setText(x, y-1, to_string(fval+1));
        cellvalues[x][y-1] = fval+1;
    }
    }

    deleteLinkedList();

    log("update done");

};