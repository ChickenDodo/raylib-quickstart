#include "raylib.h"
#include "resource_dir.h"
#include "PCG.h" // Import our new module

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Construct Map Editor");

    TileType tileArray[MAP_ROWS][MAP_COLUMNS] = { 0 };
    PCG_CreateMap(tileArray);

    SearchAndSetResourceDir("resources");//needed to add this to make wabbit appear in game
    Texture wabbit = LoadTexture("wabbit_alpha.png");
    Vector2 wabbitPosition = { (float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 };

    Texture stone = LoadTexture("stone.png");
    Texture grass = LoadTexture("grass.png");
    Texture sand = LoadTexture("sand.png");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        //Map
        //PCG_DrawMap(tileArray);
        PCG_DrawMap(tileArray, grass, stone, sand);
        DrawText("Construct Map Editor", 20, 20, 20, WHITE);
        
        //wabbit
        if (IsKeyDown(RIGHT)) wabbitPosition.x += RIGHT_SPEED;
        if (IsKeyDown(LEFT)) wabbitPosition.x -= LEFT_SPEED;
        if (IsKeyDown(UP)) wabbitPosition.y -= UP_SPEED;
        if (IsKeyDown(DOWN)) wabbitPosition.y += DOWN_SPEED;
        DrawTexture(wabbit, wabbitPosition.x, wabbitPosition.y, WHITE);

        //GUI
        PCG_DrawGUI(tileArray);

        EndDrawing();
    }
    UnloadTexture(wabbit);
    CloseWindow();
    return 0;
}