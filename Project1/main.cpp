#include<SDL.h>
#include <iostream>
using namespace std;
int main(int argc, char* argv[])
{
	int grid_cell_size = 26;
	int grid_width = 29;
	int grid_height = 23;

	// + 1 so that the last grid lines fit in the screen.
	int window_width = (grid_width * grid_cell_size) + 1;
	int window_height = (grid_height * grid_cell_size) + 1;

	// Dark theme.
	SDL_Color grid_background = { 22, 22, 22, 255 }; // Barely Black
	SDL_Color grid_line_color = { 244, 164, 96, 255 } ; // sand

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
		while (SDL_PollEvent(&event)) {
			if(event.type==SDL_QUIT) {
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

		for (int x = 0; x < 1 + grid_width * grid_cell_size;
			x += grid_cell_size) {
			SDL_RenderDrawLine(renderer, x, 0, x, window_height);
		}

		for (int y = 0; y < 1 + grid_height * grid_cell_size;
			y += grid_cell_size) {
			SDL_RenderDrawLine(renderer, 0, y, window_width, y);
		}
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}
