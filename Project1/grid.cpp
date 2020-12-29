#include "grid.h"

using namespace std;
Cell::Cell(int i, int j, int cellwidth)
{
    this->x = i; //using the this operator to reference to the coordinates
    this->y = j;
    this->CellWidth = cellwidth;
    // we re going to set the wall states to true (by default) & and not visited so that once it s visited
    //will demolish those walls by setting to false
    walls[0] = true; //top
    walls[1] = true; //right
    walls[2] = true; //left
    walls[3] = true; //bottom
    visited = false;
}

void Cell::removeWall(int w)
{
    // COMMENT: these kinds of comments are useless and only distracting
    //set the wall to false
    this->walls[w] = false;
}

void Cell::removeWalls(Cell &c)
{
    if (this->x - c.x == -1)
    {
        this->removeWall(1);
        c.removeWall(3);
    }
    if (this->x - c.x == 1)
    {
        this->removeWall(3);
        c.removeWall(1);
    }
    if (this->y - c.y == -1)
    {
        this->removeWall(2);
        c.removeWall(0);
    }
    if (this->y - c.y == 1)
    {
        this->removeWall(0);
        c.removeWall(2);
    }
}

void Cell::show(SDL_Renderer *renderer)
{
    int xCoord = this->x * CellWidth;
    int yCoord = this->y * CellWidth;
    if (this->walls[0])
    {
        SDL_RenderDrawLine(renderer,
                           xCoord, yCoord,
                           xCoord + this->CellWidth, yCoord);
        //The soul purpose of this rendereing is to create a single line on the top of wall
    }
    if (this->walls[1])
    {
        SDL_RenderDrawLine(renderer,
                           xCoord + this->CellWidth, yCoord,
                           xCoord + this->CellWidth, yCoord + this->CellWidth);
        //right
    }
    if (this->walls[2])
    {
        SDL_RenderDrawLine(renderer,
                           xCoord, yCoord + this->CellWidth,
                           xCoord + this->CellWidth, yCoord + this->CellWidth);
        //bottom
    }
    if (this->walls[3])
    {
        SDL_RenderDrawLine(renderer,
                           xCoord, yCoord,
                           xCoord, yCoord + this->CellWidth);
        //left
    }
}

void Cell::visit()
{
    this->visited = true;
}

int Cell::getPositionInVector(int size)
{
    return this->x * size + this->y;
}

// COMMENT: getters/setters should be in .h file instead
int Cell::getX()
{
    return this->x;
}

int Cell::getY()
{
    return this->y;
}

bool Cell::isVisited()
{
    return this->visited;
}
