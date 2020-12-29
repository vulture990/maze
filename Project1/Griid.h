#include <iostream>
#include <SDL.h>

class Cell {
private:
	int x, y, CellWidth;//(x,y) ARE THE COORDINATES OF OUR 2D plane
	bool walls[4];
	bool visited;
public:
	Cell(int i, int j, int cw);//constructor//cw it stands for cellwidth
	void removeWall(int cell);
	void removeWalls(Cell &c);//pass by reference
	void show(SDL_Renderer* renderer);
	//void printWalls();
	void visit();
	int getPositionInVector(int size);
	int getX();
	int getY();
	bool isVisited();
};
