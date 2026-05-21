#pragma once

#include "raylib.h"
#include <fstream>

// ===================== CONFIG =====================
constexpr int SCREEN_WIDTH = 500;
constexpr int SCREEN_HEIGHT = 500;

constexpr int TILE_SIZE = 20;
constexpr int MAX_SIZE = 19;

constexpr int DEFAULT_MAZE_WIDTH = 9;
constexpr int DEFAULT_MAZE_HEIGHT = 9;

// ===================== DATA =====================
struct Tile {
    bool wall = true;
    bool visited = false;
};

extern Tile maze[MAX_SIZE][MAX_SIZE];
extern int mazeWidth;
extern int mazeHeight;

extern float g_mazeWidthSlider;
extern float g_mazeHeightSlider;

// ===================== FUNCTIONS =====================
void InitialiseMaze();
void GenerateMaze(int x, int y);
void ExportMazeTXT(const char* filename);

void DrawMaze();
void DrawGUI();

void RegenerateMaze();
void ApplyMazeSizeFromSliders();