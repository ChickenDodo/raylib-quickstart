#include "maze.h"
#include <ctime>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main() {

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Maze");

    srand(time(NULL));

    GuiSetStyle(DEFAULT, TEXT_SIZE, 18);
    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, 0xFFFFFFFF);

    RegenerateMaze();

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_R)) {
            RegenerateMaze();
        }

        BeginDrawing();

        ClearBackground(DARKGRAY);

        DrawMaze();
        DrawGUI();

        EndDrawing();
    }

    CloseWindow();
}