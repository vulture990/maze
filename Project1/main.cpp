#include<SDL.h>
#include <iostream>
#include <SDL_image.h>
using namespace std;
SDL_Texture *IMG_LoadTexture(SDL_Renderer *renderer, const char *file);
int main(int argc, char* argv[])
{
	int grid_cell_size = 30;
	int grid_width = 25;
	int grid_height = 23;

	// + 1 so that the last grid lines fit in the screen.
	int window_width = (grid_width * grid_cell_size) + 1;
	int window_height = (grid_height * grid_cell_size) + 1;

	// Place the grid cursor in the middle of the screen.
	SDL_Rect grid_cursor;
	grid_cursor.x = (grid_width - 1) / 2 * grid_cell_size;
	grid_cursor.y = (grid_height - 1) / 2 * grid_cell_size;
	grid_cursor.w = grid_cell_size;
	grid_cursor.h = grid_cell_size;

		// The cursor ghost is a cursor that always shows in the cell below the
		// mouse cursor.
	SDL_Rect grid_cursor_ghost= { grid_cursor.x, grid_cursor.y, grid_cell_size,
								grid_cell_size };

	// 
	//SDL_Color grid_background = { 46, 139, 87, 255 }; // seagreen
	SDL_Color grid_cursor_ghost_color = { 244, 164, 96, 255 };//sand color

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

	SDL_SetWindowTitle(window, "Escape The Maze");
	IMG_LoadTexture(renderer, "C:/Users/vulture/source/repos/Project1/rsc/lol.bmp");
	SDL_bool quit = SDL_FALSE;
	SDL_bool mouse_active = SDL_FALSE;
	SDL_bool mouse_hover = SDL_FALSE;

	while (!quit) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) 
			{
			case SDL_MOUSEMOTION:
				grid_cursor_ghost.x = (event.motion.x / grid_cell_size) * grid_cell_size;
				grid_cursor_ghost.y = (event.motion.y / grid_cell_size) * grid_cell_size;

				if (!mouse_active)
					mouse_active = SDL_TRUE;
				break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_ENTER && !mouse_hover)
					mouse_hover = SDL_TRUE;
				else if (event.window.event == SDL_WINDOWEVENT_LEAVE && mouse_hover)
					mouse_hover = SDL_FALSE;
				break;
			case SDL_QUIT:
				quit = SDL_TRUE;
				break;
			}
		}

		// Draw grid background.
		//SDL_SetRenderDrawColor(renderer, grid_background.r, grid_background.g,
			//grid_background.b, grid_background.a);
		//SDL_RenderClear(renderer);
		// Draw grid ghost cursor.
		if (mouse_active && mouse_hover) {
			SDL_SetRenderDrawColor(renderer, grid_cursor_ghost_color.r,
				grid_cursor_ghost_color.g,
				grid_cursor_ghost_color.b,
				grid_cursor_ghost_color.a);
			SDL_RenderFillRect(renderer, &grid_cursor_ghost);
		}
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}
SDL_Texture *IMG_LoadTexture(SDL_Renderer *renderer, const char *file)
{
	SDL_Texture *texture = NULL;
	SDL_Surface *surface = IMG_Load(file);
	if (surface) 
	{
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
	}
	return texture;
}
