#pragma once

#include "raylib.h"
#include <fstream>

// Screen
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

// Tile size
#define TILE_SIZE 20

// Must be odd numbers for proper maze generation
#define MAZE_WIDTH  9
#define MAZE_HEIGHT 9

typedef struct {

    bool wall;      // whether it's a wall
    bool visited;   // whether it's been visited by algorithm

} Tile;

// Global maze grid
extern Tile maze[MAZE_WIDTH][MAZE_HEIGHT];

// Functions
void InitialiseMaze();

void GenerateMaze(int x, int y);

void ExportMazeTXT(const char* filename);

void DrawMaze();

void RegenerateMaze();