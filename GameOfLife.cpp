//Caleb Scott
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <fstream>
using namespace std;


int neighbors(int **array, int numRow, int numCol, int currentR, int currentC){
    int totalNeighbors = 0;
   
    if(currentR > 0 && array[currentR-1][currentC] == 1){ //top
        totalNeighbors++;
    }
    if(currentR < numRow-1 && array[currentR+1][currentC] == 1) { //bottom
        totalNeighbors++;
    }
    if(currentC > 0 && array[currentR][currentC-1] == 1) { //left
        totalNeighbors++;
    }
    if(currentC < numCol-1 && array[currentR][currentC+1] == 1) { //right
        totalNeighbors++;
    }
    if(currentR > 0 && currentC > 0 && array[currentR-1][currentC-1] == 1) { //top left
        totalNeighbors++;
    }
    if(currentR > 0 && currentC < numCol-1 && array[currentR-1][currentC+1] == 1) { //top right
        totalNeighbors++;
    }
    if(currentR < numRow-1 && currentC > 0 && array[currentR+1][currentC-1] == 1) { //bottom left
        totalNeighbors++;
    }
    if(currentR < numRow-1 && currentC < numCol-1 && array[currentR+1][currentC+1] == 1) { //bottom right
        totalNeighbors++;
    }

    return totalNeighbors;
}

int deadOrAlive(int **arr, int numRow, int numCol, int currentR, int currentC){
    int numNeighbors = neighbors(arr, numRow, numCol, currentR, currentC);

    if(arr[currentR][currentC] == 1 && numNeighbors < 2 || numNeighbors > 3){
        return 0; //switch to 0
    }
    else if(arr[currentR][currentC] == 0 && numNeighbors == 3){
        return 1; //switch to 1
    }
    else{
        return arr[currentR][currentC]; //stay the same(when 1 and having 2 or 3 neighbors)
    }
}

void printArray(int **array, int row, int col){
    for(int i=0; i<row; i++){
        for(int j = 0; j<col; j++){
            cout << array[i][j];
        }
        cout << endl;
    }
    cout << "\n";
}



int main(){
    string grid;
    cout << "Enter file --->";
    cin >> grid;
    ifstream inputF(grid);
    int numRow, numCol;

    inputF >> numRow >> numCol;

    //allocate memory for the rows and columns
    int **currentGrid = new int*[numRow];
    int **nextGrid = new int*[numRow];

    for(int i = 0; i < numRow; i++){
        currentGrid[i] = new int[numCol];
        nextGrid[i] = new int[numCol];
    }

    cout << "rows -> " << numRow << " columns -> " << numCol << "\n";

    //create the 2d array from the file
    for(int i=0; i<numRow; i++){
        for(int j=0; j<numCol; j++){
            char c;
            inputF >> c;
            //take only 1s and 0s from the file after
            //reading the amount of rows and columns
            if(c == '1') {
                currentGrid[i][j] = 1;
            }
            else if(c == '0') {
                currentGrid[i][j] = 0;
            }
        }
    }

    printArray(currentGrid, numRow, numCol); //print first grid

   
    
    //interate 10 times and calculate the next grid
    for(int n=0; n<1000; n++){



        for(int i=0; i<numRow; i++){
            for(int j=0; j<numCol; j++){
                nextGrid[i][j] = deadOrAlive(currentGrid, numRow, numCol, i, j);
            }
        }
   
        //copy the next grid back to the current grid
        for(int i=0; i<numRow; i++){
            for(int j=0; j<numCol; j++){
                currentGrid[i][j] = nextGrid[i][j];
            }
        }
       
        printArray(currentGrid, numRow, numCol); //print the updated grid
    }
    inputF.close();

    //deallocate the pointers
    for(int i=0; i<numRow; i++){
        delete[] currentGrid[i];
        delete[] nextGrid[i];
    }
    delete[] currentGrid;
    delete[] nextGrid;
    return 0;
}
