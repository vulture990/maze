#include <iostream> 
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <stack>
#include "maze.h"
#include <SDL.h>
#include "Griid.h"


using namespace std;



int main(int argc, char *argv[]) {
	init();

	Uint32 starting_tick;
	SDL_Event event;
	bool running = true;
	//gameplay
	vector < Cell > mazeGrid;
	stack < Cell* > CellStack;

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			Cell newCell(i, j, ROOM_WIDTH);
			mazeGrid.push_back(newCell);
		}
	}

	Cell *current = &mazeGrid[0];
	current->visit();

	while (running) {
		starting_tick = SDL_GetTicks();


		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
				break;
			}
		}
		//SDL_Color grid_background = { 22, 22, 22, 255 }; // Barely Black
		//SDL_Color grid_line_color = { 244, 164, 96, 255 }; // sand
		SDL_SetRenderDrawColor(renderer, 0,0,0,SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		


		//Now here comes the fun Part

		int next = checkNeighbours(mazeGrid, *current);
		// If the current cell has any neighbours which have not been visited
		if (next != -1) {
			// Choose randomly one of the unvisited neighbours
			Cell &nextRoom = mazeGrid[next];
			// Push the current cell to the stack
			CellStack.push(current);
			// Remove the wall between the current cell and the chosen cell
			current->removeWalls(nextRoom);
			// Make the chosen cell the current cell and mark it as visited
			current = &nextRoom;
			current->visit();
		}
		else if (!CellStack.empty())
		{ 
			// If stack is not empty
	        // Pop a cell from the stack
			Cell &previousRoom = *CellStack.top();
			CellStack.pop();
			// Make it the current cell
			current = &previousRoom;
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		for (Uint32 i = 0; i < mazeGrid.size(); i++) {
			if (!mazeGrid[i].isVisited()) {
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
			}
			else {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
			}
			SDL_Rect rect{ mazeGrid[i].getX() * ROOM_WIDTH, mazeGrid[i].getY() * ROOM_WIDTH, ROOM_WIDTH, ROOM_WIDTH };
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
			mazeGrid[i].show(renderer);
		}

		SDL_SetRenderDrawColor(renderer, 55, 55, 55, SDL_ALPHA_OPAQUE);
		int xCoordHead = current->getX() * ROOM_WIDTH;
		int yCoordHead = current->getY() * ROOM_WIDTH;
		SDL_Rect rect{ xCoordHead, yCoordHead, ROOM_WIDTH, ROOM_WIDTH };
		SDL_RenderFillRect(renderer, &rect);
		SDL_RenderPresent(renderer);

		cap_framerate(starting_tick);
	}
	exit();
}
