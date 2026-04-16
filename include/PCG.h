#ifndef PCG_H
#define PCG_H
#include "raylib.h"

// Screen & Map Dimensions
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 1024
#define TILE_SIZE 64
#define MAP_COLUMNS (SCREEN_WIDTH / TILE_SIZE)
#define MAP_ROWS (SCREEN_HEIGHT / TILE_SIZE)

// Tile Types (Using Enum for readability)
typedef enum {
    TILE_TYPE_GRASS = 0,
    TILE_TYPE_ROCK = 1,
    TILE_TYPE_SAND = 2,
    TILE_COUNT  // Automatically counts total types
} TileType;

// Visual & Character settings
#define GRASS_CHAR '.'
#define ROCK_CHAR '#'
#define SAND_CHAR 'S'
#define GRASS_COLOR (DARKGREEN)
#define ROCK_COLOR (GRAY)
#define SAND_COLOR (YELLOW)
#define UNKNOWN_COLOR WHITE

// Function Declarations
void PCG_CreateMap(TileType _tileArray[MAP_ROWS][MAP_COLUMNS]);
void PCG_DrawMap(TileType _tileArray[MAP_ROWS][MAP_COLUMNS], Texture grass, Texture stone, Texture sand);
void PCG_PrintMap(TileType _tileArray[MAP_ROWS][MAP_COLUMNS]);
Color PCG_GetTileColor(TileType tileType);
//added for textures
Color _tileTint[MAP_ROWS][MAP_COLUMNS];

// File Names
#define MAP_TEXT_FILENAME "pcg_map_data.txt"

// Helpers
char GetTileChar(TileType tileType);

// I/O Functions
void PCG_SaveMapData(TileType _tileArray[MAP_ROWS][MAP_COLUMNS], const char* filename);
void PCG_LoadMapData(TileType _tileArray[MAP_ROWS][MAP_COLUMNS], const char* filename);

#define MAP_IMAGE_FILENAME "pcg_map.png"
void PCG_SaveMapImage(TileType _tileArray[MAP_ROWS][MAP_COLUMNS], const char* filename);

// UI variable defines used to position buttons on screen
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50
#define BUTTON_X (SCREEN_WIDTH - BUTTON_WIDTH - 20)
#define BUTTON_Y (SCREEN_HEIGHT - BUTTON_HEIGHT - 20)
#define RESET_BUTTON_BOUNDS (Rectangle){ BUTTON_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT }

// Declare UI drawing function
void PCG_DrawGUI(TileType tileArray[MAP_ROWS][MAP_COLUMNS]);

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



#endif // PCG_H