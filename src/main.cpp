//https://www.youtube.com/watch?v=mh7X_I7uKHM
#include "maze.h"
#include <stdlib.h>
#include <time.h>

int main() {

    InitWindow(
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        "Tile Maze Generator"
    );

    srand(time(NULL)); //set random seed

    RegenerateMaze();

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        // Press R to regenerate
        if (IsKeyPressed(KEY_R)) {

            RegenerateMaze();
        }

        BeginDrawing();

        ClearBackground(BLUE);

        DrawMaze();

        DrawText(
            "Press R to regenerate/export maze.txt",
            10,
            10,
            20,
            RED
        );

        EndDrawing();
    }

    CloseWindow();

    return 0;
}