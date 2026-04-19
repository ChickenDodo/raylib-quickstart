#pragma once
#include "raylib.h"

namespace PCG{
    // Screen & Map Dimensions
    constexpr int SCREEN_WIDTH = 1024;
    constexpr int SCREEN_HEIGHT = 1024;
    constexpr int TILE_SIZE = 64;
    constexpr int MAP_COLUMNS = (SCREEN_WIDTH / TILE_SIZE);
    constexpr int MAP_ROWS = (SCREEN_HEIGHT / TILE_SIZE);

// Tile Types
enum TileType {
    TILE_TYPE_GRASS = 0,
    TILE_TYPE_ROCK = 1,
    TILE_TYPE_SAND = 2,
    TILE_COUNT
};

// Visual & Character settings
constexpr char GRASS_CHAR = '.';
constexpr char ROCK_CHAR = '#';
constexpr char SAND_CHAR = 'S';
constexpr Color GRASS_COLOR = GREEN;
constexpr Color ROCK_COLOR = GRAY;
constexpr Color SAND_COLOR = YELLOW;
constexpr Color UNKNOWN_COLOR = WHITE;

// Function Declarations
void CreateMap(TileType tileArray[MAP_ROWS][MAP_COLUMNS]);

void DrawMap(
    TileType tileArray[MAP_ROWS][MAP_COLUMNS],
    Texture2D grass,
    Texture2D stone,
    Texture2D sand
);

void PrintMap(TileType tileArray[MAP_ROWS][MAP_COLUMNS]);

Color GetTileColor(TileType tileType);

extern Color tileTint[MAP_ROWS][MAP_COLUMNS];

// File Names
constexpr char* MAP_TEXT_FILENAME = "pcg_map_data.txt";

// Helpers
char GetTileChar(TileType tileType);

// I/O Functions
void SaveMapData(TileType _tileArray[MAP_ROWS][MAP_COLUMNS], const char* filename);
void LoadMapData(TileType _tileArray[MAP_ROWS][MAP_COLUMNS], const char* filename);

constexpr char* MAP_IMAGE_FILENAME = "pcg_map.png";
void SaveMapImage(TileType _tileArray[MAP_ROWS][MAP_COLUMNS], const char* filename);

// UI variable defines used to position buttons on screen
constexpr int BUTTON_WIDTH = 200;
constexpr int BUTTON_HEIGHT = 50;
constexpr int BUTTON_X = (SCREEN_WIDTH - BUTTON_WIDTH - 20);
constexpr int BUTTON_Y = (SCREEN_HEIGHT - BUTTON_HEIGHT - 20);
constexpr Rectangle RESET_BUTTON_BOUNDS = { BUTTON_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT };

// Declare UI drawing function
void DrawGUI(TileType tileArray[MAP_ROWS][MAP_COLUMNS]);

//TODO: convert to c++ below
// Player Controls
#define UP 'W'
#define DOWN 'S'
#define LEFT 'A'
#define RIGHT 'D'

// Player Movespeed
#define UP_SPEED 5
#define DOWN_SPEED 5
#define LEFT_SPEED 5
#define RIGHT_SPEED 5
}