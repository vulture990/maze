//#include <SDL.h>
//#include <iostream>
//#include <utility>
//#include <vector>
#include "maze.h"
using namespace std;
int main(int argc, char* argv[])
{
	init();
	SDL_bool quit = SDL_FALSE;
	SDL_Event event {NULL};
	Draw(event, quit);
	exit();
	return EXIT_SUCCESS;
}
