#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <stack>
#include <string>

using namespace std;
//Setting a class
class Maze
{
private:

	int  MazeWidth;
	int  MazeHeight;
	int  *maze;
	// (x, y) coordinate pairs
	stack <pair<int,int>> smaze;


	// variables needed
	bool  VisitedCells;  //To keep track of visitedcells
	int  PathBetweenCells; //In order To draw the path between cells
public:
	// Some Sets of memory to assign them to maze array to get a clear image on it's surronding
	enum cells { CELLNORTH = 0x01, CELLEAST = 0x02, CELLSOUTH = 0x04, CELLWEST = 0x08, CELLVISITED = 0x10, };

	//Setting our private variables

	void SetMazeWidth(int s)
	{
		MazeWidth = s;
	}
	void SetMazeHeight(int s)
	{
		MazeHeight = s;
	}
	void Setmaze(int *s)
	{
		s = new int[MazeHeight*MazeWidth];
		memset(s, 0x00, sizeof(int)*MazeHeight*MazeWidth);
		maze = s;
	}
	void SetPath(int s)
	{
		PathBetweenCells = s;
	}
	void setvisitedcells(bool s)
	{
		s = true;
		VisitedCells = s;
	}
	//This opearation guarantees generating random Mazes 
	int x = rand() % MazeWidth;
	int y = rand() % MazeHeight;

	void setstack(stack <pair <int,int>> s)
	{
		s.push(make_pair(x, y));
		smaze = s;
    }
	//marking the cell as visited
	enum cells cell = CELLVISITED;
	void SetNewMaze(int s)//s in this case locates the initial postion in maze array
	{
		maze[x*MazeHeight + y] = cell;//assuming that the way we fill our dynamic array maze is by fixing x and going through y first
		VisitedCells = true;
	}
	//Here comes the fun part Impelementing the algorithm
	



	
};
