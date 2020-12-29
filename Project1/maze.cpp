#include "maze.h"
#include "Griid.h"
void init(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Initialize SDL: %s",
			SDL_GetError());
	}
	if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window,
		&renderer) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Create window and renderer: %s", SDL_GetError());
		
	}

	SDL_SetWindowTitle(window, "Escape The Maze");
}
bool unvisitedCells(vector <Cell> mazeGrid)//return boolean value based on visited vs unvisited cells
{
	for (Uint32 i = 0; i < mazeGrid.size(); i++) {
		if (!mazeGrid[i].isVisited()) {
			return true;
		}
	}
	return false;
}
int checkNeighbours(vector <Cell> maze, Cell c) {
	int x = c.getX();
	int y = c.getY();
	vector < Cell > neighbours;
	if (!maze[(x - 1) * ROWS + y].isVisited() && x > 0) {
		neighbours.push_back(maze[(x - 1) * ROWS + y]);
	}
	if (!maze[(x + 1) * ROWS + y].isVisited() && x < ROWS - 1) {
		neighbours.push_back(maze[(x + 1) * ROWS + y]);
	}
	if (!maze[x * ROWS + y + 1].isVisited() && y < COLUMNS - 1) {
		neighbours.push_back(maze[x * ROWS + y + 1]);
	}
	if (!maze[x * ROWS + y - 1].isVisited() && y > 0) {
		neighbours.push_back(maze[x * ROWS + y - 1]);
	}
	if (neighbours.size() < 1) {
		return -1;
	}

	int randomIdx = rand() % neighbours.size();
	int nxt = neighbours[randomIdx].getY() + neighbours[randomIdx].getX() * ROWS;
	return nxt;//this refers to the next neighboor
}
void cap_framerate(Uint32 starting_tick) {
	if ((1000 / FPS) > SDL_GetTicks() - starting_tick) {
		SDL_Delay(1000 / FPS - (SDL_GetTicks() - starting_tick));
	}
}
void exit(void)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
