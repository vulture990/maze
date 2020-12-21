#include<SDL.h>
#include <iostream>
#include <vector>
using namespace std;
int main(int argc, char* argv[])
{
	int w = 20;
	int const  grid_width = 29;//ROWS
	int const grid_height = 23;//cOlUmuns
	pair <int, int> cell;
	// + 1 so that the last grid lines fit in the screen.
	int window_width = (grid_width * w) + 1;
	int window_height = (grid_height * w) + 1;
	vector <pair<int,int>> cells;
	// Dark theme.
	SDL_Color grid_background = { 22, 22, 22, 255 }; // Barely Black
	SDL_Color grid_line_color = { 244, 164, 96, 255 } ; // sand
	bool *walls;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Initialize SDL: %s",
			SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_Window *window;
	SDL_Renderer *renderer;
	if (SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window,
		&renderer) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Create window and renderer: %s", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_SetWindowTitle(window, "SDL Grid");

	SDL_bool quit = SDL_FALSE;

	while (!quit) {
		SDL_Event event;
		if (SDL_PollEvent(&event)) 
		{
			if(event.type==SDL_QUIT) 
			{
				quit = SDL_TRUE;
				break;
			}
		}
		// Draw grid background.
		SDL_SetRenderDrawColor(renderer, grid_background.r, grid_background.g,
			grid_background.b, grid_background.a);
		SDL_RenderClear(renderer);

		// Draw grid lines.
		SDL_SetRenderDrawColor(renderer, grid_line_color.r, grid_line_color.g,
			grid_line_color.b, grid_line_color.a);
		int s = 0;
		for (int i = 0;i <grid_width+1;i++)
		{
			for (int j = 0;j <grid_height+1;j++)
			{
				cell = make_pair(i, j);
				cells.push_back(cell);
				s++;
			}
		}
		walls = new bool[4];
		memset(walls, true, sizeof(bool) * 4);//it's going to be set in order way going top,right, bottom,left
		for (int i = 0;i < s;i++)
		{
			pair <int, int> flag;
			flag = cells[i];
			int x = flag.first * w;
			int y = flag.second *w;
			if (walls[0])
			{
				SDL_RenderDrawLine(renderer, x, y, x + w, y);//top
			}
			if (walls[1])
			{
				SDL_RenderDrawLine(renderer, x + w, y, x + w, y + w);//right

			}
			if (walls[2])
			{
				SDL_RenderDrawLine(renderer, x + w, y + w, x, y + w);//bottom
			}
			if (walls[3])
			{
				SDL_RenderDrawLine(renderer, x, y + w, x, y);//left
			}
			
		}
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}
