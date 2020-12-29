#pragma once

#include <iostream>
#include <SDL.h>

class Cell
{
private:
    int x, y, CellWidth; // (x,y) ARE THE COORDINATES OF OUR 2D plane
    bool walls[4];
    bool visited;

public:
    // COMMENT: "cw it stands for cellwidth" <- just call the variable cellwidth
    Cell(int i, int j, int cellwidth); // constructor
    void removeWall(int cell);
    void removeWalls(Cell &c); // pass by reference
    void show(SDL_Renderer *renderer);
    // void printWalls();
    void visit();
    int getPositionInVector(int size);
    int getX();
    int getY();
    bool isVisited();
};
