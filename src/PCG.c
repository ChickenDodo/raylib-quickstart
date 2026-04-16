#include "PCG.h"
#include <stdio.h>

// globals
float g_grassPercentage = 50.0f;  
float g_hillPercentage = 50.0f;
static char g_text;
    
// ============================================= 
// void PCG_CreateMap(TileType _tileArray[MAP_ROWS][MAP_COLUMNS])
// ============================================= 
void PCG_CreateMap(TileType _tileArray[MAP_ROWS][MAP_COLUMNS])
{
    for (int y = 0; y < MAP_ROWS; y++)
    {
        for (int x = 0; x < MAP_COLUMNS; x++)
        {
            // -------------------------
            // 1. TERRAIN GENERATION
            // -------------------------

            if (y >= MAP_ROWS - 3)
            {
                _tileArray[y][x] = TILE_TYPE_SAND;
            }
            else
            {
                int roll = GetRandomValue(0, 99);

                if (roll < g_grassPercentage)
                    _tileArray[y][x] = TILE_TYPE_GRASS;
                else
                    _tileArray[y][x] = TILE_TYPE_ROCK;
            }

            // -------------------------
            // 2. TINT GENERATION
            // -------------------------

            int tintRoll = GetRandomValue(0, 99);

            if (tintRoll < g_hillPercentage)
                _tileTint[y][x] = GRAY;
            else
                _tileTint[y][x] = WHITE;
        }
    }
}


// ============================================= 
// Color PCG_GetTileColor(TileType tileType)
// Return a colour based on the type type input
// ============================================= 
Color PCG_GetTileColor(TileType tileType) {
    switch (tileType) {
    case TILE_TYPE_GRASS: return GRASS_COLOR;
    case TILE_TYPE_ROCK: return ROCK_COLOR;
    case TILE_TYPE_SAND: return SAND_COLOR;
    default: return UNKNOWN_COLOR;
    }
}


// ============================================= 
// void PCG_DrawMap(TileType _tileArray[MAP_ROWS][MAP_COLUMNS])
// ============================================= 
//void PCG_DrawMap(TileType _tileArray[MAP_ROWS][MAP_COLUMNS]) {
//    for (int y = 0; y < MAP_ROWS; y++) {
//        for (int x = 0; x < MAP_COLUMNS; x++) {
//            DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, PCG_GetTileColor(_tileArray[y][x]));
//        }
//    }
//}

void PCG_DrawMap(TileType _tileArray[MAP_ROWS][MAP_COLUMNS],
    Texture grass,
    Texture stone,
    Texture sand)
{
    for (int y = 0; y < MAP_ROWS; y++) {
        for (int x = 0; x < MAP_COLUMNS; x++) {

            Vector2 pos = { x * TILE_SIZE, y * TILE_SIZE };

            Color tint = _tileTint[y][x];

            if (y >= MAP_ROWS - 3) { // bottom 3 rows
                DrawTextureEx(sand, pos, 0.0f,
                    (float)TILE_SIZE / sand.width,
                    tint);
                continue;
            }

            switch (_tileArray[y][x]) {
            case TILE_TYPE_GRASS:
                DrawTextureEx(grass, pos, 0.0f, (float)TILE_SIZE / grass.width, tint);//resizes texture to tile size
                break;

            default: TILE_TYPE_ROCK:
                DrawTextureEx(stone, pos, 0.0f, (float)TILE_SIZE / stone.width, tint);//ideally an artist problem, but just to show textures working
                break;
            }
        }
    }
}

// ============================================= 
// void PCG_PrintMap(TileType _tileArray[MAP_ROWS][MAP_COLUMNS])
// ============================================= 
void PCG_PrintMap(TileType _tileArray[MAP_ROWS][MAP_COLUMNS]) {
    printf("\n-------Map Layout:--------\n");
    // (Existing Print Logic here...)
    printf("--------------------------\n");
}

// ============================================= 
// char GetTileChar(TileType tileType)
// Return a char value based on the type of tile passed in
// ============================================= 
char GetTileChar(TileType tileType) {
    switch (tileType) {
    case TILE_TYPE_GRASS: return GRASS_CHAR;
    case TILE_TYPE_ROCK: return ROCK_CHAR;
    case TILE_TYPE_SAND: return SAND_CHAR;
    default: return '?';
    }
}

// ============================================= 
// void PCG_SaveMapData(TileType _tileArray[MAP_ROWS][MAP_COLUMNS], const char* _filename)
// Store our tilemap data to a text file using the input _filename
// ============================================= 
void PCG_SaveMapData(TileType _tileArray[MAP_ROWS][MAP_COLUMNS], const char* _filename) {
    FILE* file = fopen(_filename, "w"); // "w" = Write
    if (file == NULL) {
        return;
    }

    // Write each single tileArray charater into our file stream
    for (int y = 0; y < MAP_ROWS; y++) {
        for (int x = 0; x < MAP_COLUMNS; x++) {
            fputc(GetTileChar(_tileArray[y][x]), file);
        }
        fputc('\n', file); // New line at end of row
    }
    fclose(file);
    printf("Map saved to %s\n", _filename);
}


// ============================================= 
// void PCG_LoadMapData(TileType _tileArray[MAP_ROWS][MAP_COLUMNS], const char* _filename)
// Load our tilemap data from a text file, using input _filename
// ============================================= 
void PCG_LoadMapData(TileType _tileArray[MAP_ROWS][MAP_COLUMNS], const char* _filename) {
    FILE* file = fopen(_filename, "r"); // "r" = Read
    if (file == NULL) {
        return;
    }

    // Get each character from our file stream, and load it into our tileMap array
    for (int y = 0; y < MAP_ROWS; y++) {
        for (int x = 0; x < MAP_COLUMNS; x++) {
            int ch = fgetc(file);
            // Skip invisible newline characters
            while (ch == '\n' || ch == '\r') {
                ch = fgetc(file);
            }

            if (ch == GRASS_CHAR) {
                _tileArray[y][x] = TILE_TYPE_GRASS;
            }
            else if (ch == ROCK_CHAR) {
                _tileArray[y][x] = TILE_TYPE_ROCK;
            }
            else if (ch == SAND_CHAR) {
                _tileArray[y][x] = TILE_TYPE_SAND;
            }
        }
    }
    fclose(file);
    printf("Map loaded from %s\n", _filename);
}

// ============================================= 
// void PCG_SaveMapImage(TileType _tileArray[MAP_ROWS][MAP_COLUMNS], const char* filename)
// Store our tileMap data as a .png image, using the input filename.
// ============================================= 
void PCG_SaveMapImage(TileType _tileArray[MAP_ROWS][MAP_COLUMNS], const char* filename) {
    Image mapImage = GenImageColor(MAP_COLUMNS, MAP_ROWS, BLACK);

    for (int y = 0; y < MAP_ROWS; y++) {
        for (int x = 0; x < MAP_COLUMNS; x++) {
            Color c = PCG_GetTileColor(_tileArray[y][x]);
            ImageDrawPixel(&mapImage, x, y, c);
        }
    }
    if (ExportImage(mapImage, filename)) {
        printf("Image saved: %s\n", filename);
    }
    UnloadImage(mapImage);
}

// Required to call Raylib gui buttons. Add this near the top of PCG.c
#define RAYGUI_IMPLEMENTATION
#include "raygui.h" 

// ============================================= 
// void PCG_DrawGUI(TileType tileArray[MAP_ROWS][MAP_COLUMNS])
// ============================================= 
void PCG_DrawGUI(TileType tileArray[MAP_ROWS][MAP_COLUMNS]) {
    // Reset Button
    if (GuiButton(RESET_BUTTON_BOUNDS, "Reset Map")) {
        PCG_CreateMap(tileArray);
    }

    // Save Data Button
    Rectangle saveRect = { BUTTON_X, BUTTON_Y - 70, BUTTON_WIDTH, BUTTON_HEIGHT };
    if (GuiButton(saveRect, "Save Map Data")) {
        PCG_SaveMapData(tileArray, MAP_TEXT_FILENAME);
    }

    // Load Data Button
    Rectangle loadRect = { BUTTON_X, BUTTON_Y - 140, BUTTON_WIDTH, BUTTON_HEIGHT };
    if (GuiButton(loadRect, "Load Map Data")) {
        PCG_LoadMapData(tileArray, MAP_TEXT_FILENAME);
    }

    // Save Image Button
    Rectangle imgRect = { BUTTON_X, BUTTON_Y - 210, BUTTON_WIDTH, BUTTON_HEIGHT };
    if (GuiButton(imgRect, "Save Map PNG")) {
        PCG_SaveMapImage(tileArray, MAP_IMAGE_FILENAME);
    }

    // Grass Slider
    Rectangle grassSlider = { 100, 100, 200, 20 };
    GuiSlider(grassSlider, "Min", "Max", &g_grassPercentage, 0.0f, 100.0f);
    DrawText(TextFormat("Grass Percentage: %.2f", g_grassPercentage), 100, 130, 20, WHITE);

    // Hill Slider
    Rectangle hillSlider = { 100, 200, 200, 20 };
    GuiSlider(hillSlider, "Min", "Max", &g_hillPercentage, 0.0f, 100.0f);
    DrawText(TextFormat("Hill Percentage: %.2f", g_hillPercentage), 100, 230, 20, WHITE);

    // Savefile Naming
    Rectangle saveFileBox = { 100, 300, 200, 30 };
    static char g_text[64] = "savefile name here...";//static so we can edit
    static bool editMode = false;
    if (GuiTextBox(saveFileBox, g_text, sizeof(g_text), editMode))
    {
        editMode = !editMode;
    }
}

