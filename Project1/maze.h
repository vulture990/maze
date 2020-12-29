#pragma once

#include <SDL.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <stack>

#include "grid.h"

#define WIDTH 600
#define HEIGHT 600
#define ROWS 100
#define COLUMNS 100
#define ROOM_WIDTH (WIDTH / ROWS)
#define FPS 512

using namespace std;
int const grid_width = 29;  //ROWS
int const grid_height = 23; //COLUMNS
// Dark theme.
SDL_Color grid_background = {22, 22, 22, 255};   // Barely Black
SDL_Color grid_line_color = {244, 164, 96, 255}; // sand
SDL_Window *window;
SDL_Renderer *renderer;

void init(void);
bool unvisitedCells(vector<Cell> mazeGrid);
int checkNeighbours(vector<Cell> maze, Cell c);
void cap_framerate(Uint32 starting_tick);
void exit(void);
