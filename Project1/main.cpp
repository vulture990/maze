#include <iostream> 
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <stack>
#include <SDL.h>
#include "Griid.h"

#define WIDTH      600
#define HEIGHT     600
#define ROWS       100
#define COLUMNS    100
#define ROOM_WIDTH (WIDTH / ROWS)


using namespace std;

bool unvisitedCells(vector <Cell> mazeGrid) {
	for (Uint32 i = 0; i < mazeGrid.size(); i++) {
		if (!mazeGrid[i].isVisited()) {
			return true;
		}
	}
	return false;
}

int checkNeighbours(vector <Cell> maze, Cell r) {
	int x = r.getX();
	int y = r.getY();
	vector < Cell > neighbours;
	if (x > 0 && !maze[(x-1 ) * ROWS + y].isVisited() ) {
		neighbours.push_back(maze[(x-1) * ROWS + y]);
	}
	if ( x < ROWS-1 && !maze[(x + 1) * ROWS + y].isVisited() ) {
		neighbours.push_back(maze[(x + 1) * ROWS + y]);
	}
	if (y < COLUMNS-1 && !maze[x * ROWS + y + 1].isVisited()  ) {
		neighbours.push_back(maze[x * ROWS + y + 1]);
	}
	if (y > 0 && !maze[x * ROWS + y-1 ].isVisited()) {
		neighbours.push_back(maze[x * ROWS + y-1 ]);
	}
	else if (neighbours.size() < 1){
		return -1;
	}

	int randomIdx =rand() % neighbours.size();
	int nxt = neighbours[randomIdx].getY() + neighbours[randomIdx].getX() * ROWS;
	return nxt;
}



int main(int argc, char *argv[]) {
	/*srand(time(NULL));*/
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer);

	if (window == NULL) {
		std::cout << "There was an error initializing the window! :(\n"
			<< SDL_GetError();
		return 1;
	}

	/*Uint32 starting_tick;*/
	SDL_Event event;
	bool running = true;

	vector < Cell > mazeGrid;
	stack < Cell* > roomStack;

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			Cell newRoom(i, j, ROOM_WIDTH);
			mazeGrid.push_back(newRoom);
		}
	}

	Cell *current = &mazeGrid[0];
	current->visit();

	while (running) {
		/*starting_tick = SDL_GetTicks();*/


		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
				break;
			}
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		int next = checkNeighbours(mazeGrid, *current);
		// If the current cell has any neighbours which have not been visited
		if (next != -1) {
			// Choose randomly one of the unvisited neighbours
			Cell &nextRoom = mazeGrid[next];
			// Push the current cell to the stack
			roomStack.push(current);
			// Remove the wall between the current cell and the chosen cell
			current->removeWalls(nextRoom);
			// Make the chosen cell the current cell and mark it as visited
			current = &nextRoom;
			current->visit();
		}
		else if (!roomStack.empty()) { // If stack is not empty
	   // Pop a cell from the stack
			Cell &previousRoom = *roomStack.top();
			roomStack.pop();
			// Make it the current cell
			current = &previousRoom;
		}

		SDL_SetRenderDrawColor(renderer, 244, 164, 96, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		for (Uint32 i = 0; i < mazeGrid.size(); i++) {
			if (!mazeGrid[i].isVisited()) {
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 244, 164, 96, SDL_ALPHA_OPAQUE);
			}
			SDL_Rect rect{ mazeGrid[i].getX() * ROOM_WIDTH, mazeGrid[i].getY() * ROOM_WIDTH, ROOM_WIDTH, ROOM_WIDTH };
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
			mazeGrid[i].show(renderer);
		}

		SDL_SetRenderDrawColor(renderer, 244, 164, 96, SDL_ALPHA_OPAQUE);
		int xCoordHead = current->getX() * ROOM_WIDTH;
		int yCoordHead = current->getY() * ROOM_WIDTH;
		SDL_Rect rect{ xCoordHead, yCoordHead, ROOM_WIDTH, ROOM_WIDTH };
		SDL_RenderFillRect(renderer, &rect);
		SDL_RenderPresent(renderer);


	}


	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
