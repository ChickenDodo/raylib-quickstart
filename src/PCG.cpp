#include "PCG.h"
#include <stdio.h>
#include <iostream>
#include <fstream>

// globals
float g_grassPercentage = 50.0f;  
float g_hillPercentage = 50.0f;
Color PCG::tileTint[MAP_ROWS][MAP_COLUMNS];

// ============================================= 
// void CreateMap(TileType tileArray[MAP_ROWS][MAP_COLUMNS])
// ============================================= 
void PCG::CreateMap(TileType tileArray[MAP_ROWS][MAP_COLUMNS]) {
    for (int y = 0; y < MAP_ROWS; y++)
    {
        for (int x = 0; x < MAP_COLUMNS; x++)
        {
            // -------------------------
            // 1. TERRAIN GENERATION
            // -------------------------

            if (y >= MAP_ROWS - 3)
            {
                tileArray[y][x] = TILE_TYPE_SAND;
            }
            else
            {
                int roll = GetRandomValue(0, 99);

                if (roll < g_grassPercentage)
                    tileArray[y][x] = TILE_TYPE_GRASS;
                else
                    tileArray[y][x] = TILE_TYPE_ROCK;
            }

            // -------------------------
            // 2. TINT GENERATION
            // -------------------------

            int tintRoll = GetRandomValue(0, 99);

            if (tintRoll < g_hillPercentage)
                tileTint[y][x] = GRAY;
            else
                tileTint[y][x] = WHITE;
        }
    }
}

// ============================================= 
// Color GetTileColor(TileType tileType)
// Return a colour based on the type type input
// ============================================= 
Color PCG::GetTileColor(PCG::TileType tileType) {
    switch (tileType) {
    case TILE_TYPE_GRASS: return GRASS_COLOR;
    case TILE_TYPE_ROCK: return ROCK_COLOR;
    case TILE_TYPE_SAND: return SAND_COLOR;
    default: return UNKNOWN_COLOR;
    }
}

// ============================================= 
// void DrawMap(TileType tileArray[MAP_ROWS][MAP_COLUMNS])
// ============================================= 
//void DrawMap(TileType tileArray[MAP_ROWS][MAP_COLUMNS]) {
//    for (int y = 0; y < MAP_ROWS; y++) {
//        for (int x = 0; x < MAP_COLUMNS; x++) {
//            DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, GetTileColor(tileArray[y][x]));
//        }
//    }
//}

void PCG::DrawMap(
    PCG::TileType tileArray[MAP_ROWS][MAP_COLUMNS],
    Texture2D grass,
    Texture2D stone,
    Texture2D sand)
{
    for (int y = 0; y < MAP_ROWS; y++) {
        for (int x = 0; x < MAP_COLUMNS; x++) {

            Vector2 pos = { x * TILE_SIZE, y * TILE_SIZE };

            Color tint = tileTint[y][x];

            if (y >= MAP_ROWS - 3) { // bottom 3 rows
                DrawTextureEx(sand, pos, 0.0f,
                    (float)TILE_SIZE / sand.width,
                    tint);
                continue;
            }

            switch (tileArray[y][x]) {
            case TILE_TYPE_GRASS:
                DrawTextureEx(grass, pos, 0.0f, (float)TILE_SIZE / grass.width, tint);//resizes texture to tile size
                break;

            case TILE_TYPE_ROCK:
            default:
                DrawTextureEx(stone, pos, 0.0f,
                    (float)TILE_SIZE / stone.width, tint);
                break;
            }
        }
    }
}

// ============================================= 
// void PrintMap(TileType tileArray[MAP_ROWS][MAP_COLUMNS])
// ============================================= 
void PCG::PrintMap(TileType tileArray[MAP_ROWS][MAP_COLUMNS]) {
    printf("\n-------Map Layout:--------\n");
    // (Existing Print Logic here...)
    printf("--------------------------\n");
}

// ============================================= 
// char GetTileChar(TileType tileType)
// Return a char value based on the type of tile passed in
// ============================================= 
char PCG::GetTileChar(TileType tileType) {
    switch (tileType) {
    case TILE_TYPE_GRASS: return GRASS_CHAR;
    case TILE_TYPE_ROCK: return ROCK_CHAR;
    case TILE_TYPE_SAND: return SAND_CHAR;
    default: return '?';
    }
}

// ============================================= 
// void SaveMapData(TileType _tileArray[MAP_ROWS][MAP_COLUMNS], const char* _filename)
// Store our tilemap data to a text file using the input _filename
// ============================================= 
void PCG::SaveMapData(TileType _tileArray[MAP_ROWS][MAP_COLUMNS], const char* _filename) {
    std::fstream file;
    file.open(_filename, std::ios::out); // Open C++ file stream for writing
    //if (file == nullptr) {    // old C-style file open check
    if (!file.is_open()) { // Check if file opened successfully
        return;
    }

    // Write each single tileArray charater into our file stream
    for (int y = 0; y < PCG::MAP_ROWS; y++) {
        for (int x = 0; x < PCG::MAP_COLUMNS; x++) {
            //fputc(PCG::GetTileChar(_tileArray[y][x]), file);  // old c-style file write
            file.put(PCG::GetTileChar(_tileArray[y][x])); // Write char to C++ file stream
        }
        //fputc('\n', file); // New line at end of row
        file.put('\n'); // New line at end of row for C++ file stream
    }
    //fclose(file); // old C-style file close
    file.close(); // Close C++ file stream
    std::cout << "Map saved to " << _filename << std::endl;
}

// ============================================= 
// void LoadMapData(TileType _tileArray[MAP_ROWS][MAP_COLUMNS], const char* _filename)
// Load our tilemap data from a text file, using input _filename
// ============================================= 
void PCG::LoadMapData(TileType _tileArray[MAP_ROWS][MAP_COLUMNS], const char* _filename) {
    //FILE* file = fopen(_filename, "r"); // "r" = Read // old c style
    std::fstream file;  // C++ file stream object for reading
    file.open(_filename, std::ios::in); // Open C++ file stream for reading
    //if (file == NULL) {   // old C-style file open check
    if (!file.is_open()) { // Check if file opened successfully for C++ stream
        return;
    }

    // Get each character from our file stream, and load it into our tileMap array
    for (int y = 0; y < PCG::MAP_ROWS; y++) {
        for (int x = 0; x < PCG::MAP_COLUMNS; x++) {
            //int ch = fgetc(file); // old C-style file read
            int ch = file.get(); // Get char from C++ file stream
            // Skip invisible newline characters
            while (ch == '\n' || ch == '\r') {
                //ch = fgetc(file); // old C-style file read for skipping newlines
                ch = file.get(); // Get char from C++ file stream for skipping newlines
            }

            if (ch == PCG::GRASS_CHAR) {
                _tileArray[y][x] = PCG::TileType::TILE_TYPE_GRASS;
            }
            else if (ch == PCG::ROCK_CHAR) {
                _tileArray[y][x] = PCG::TileType::TILE_TYPE_ROCK;
            }
        }
    }
    //fclose(file); // old C-style file close
    file.close(); // Close C++ file stream
    // printf("Map loaded from %s\n", _filename);   // old C-style print statement
    std::cout << "Map loaded from " << _filename << std::endl; // C++ style print statement
}

// ============================================= 
// void SaveMapImage(TileType tileArray[MAP_ROWS][MAP_COLUMNS], const char* filename)
// Store our tileMap data as a .png image, using the input filename.
// ============================================= 
void PCG::SaveMapImage(TileType tileArray[MAP_ROWS][MAP_COLUMNS], const char* filename) {
    Image mapImage = GenImageColor(MAP_COLUMNS, MAP_ROWS, BLACK);

    for (int y = 0; y < MAP_ROWS; y++) {
        for (int x = 0; x < MAP_COLUMNS; x++) {
            Color c = GetTileColor(tileArray[y][x]);
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
// void DrawGUI(TileType tileArray[MAP_ROWS][MAP_COLUMNS])
// ============================================= 
void PCG::DrawGUI(TileType tileArray[MAP_ROWS][MAP_COLUMNS]) {
    // Reset Button
    if (GuiButton(RESET_BUTTON_BOUNDS, "Reset Map")) {
        CreateMap(tileArray);
    }

    // Save Data Button
    Rectangle saveRect = { BUTTON_X, BUTTON_Y - 70, BUTTON_WIDTH, BUTTON_HEIGHT };
    if (GuiButton(saveRect, "Save Map Data")) {
        SaveMapData(tileArray, MAP_TEXT_FILENAME);
    }

    // Load Data Button
    Rectangle loadRect = { BUTTON_X, BUTTON_Y - 140, BUTTON_WIDTH, BUTTON_HEIGHT };
    if (GuiButton(loadRect, "Load Map Data")) {
        LoadMapData(tileArray, MAP_TEXT_FILENAME);
    }

    // Save Image Button
    Rectangle imgRect = { BUTTON_X, BUTTON_Y - 210, BUTTON_WIDTH, BUTTON_HEIGHT };
    if (GuiButton(imgRect, "Save Map PNG")) {
        SaveMapImage(tileArray, MAP_IMAGE_FILENAME);
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

