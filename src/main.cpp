#include "raylib.h"
#include "resource_dir.h"
#include "PCG.h" // Import our new module

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(PCG::SCREEN_WIDTH, PCG::SCREEN_HEIGHT, "Construct Map Editor");

    PCG::TileType tileArray[PCG::MAP_ROWS][PCG::MAP_COLUMNS] = { PCG::TileType::TILE_TYPE_ROCK };
    PCG::CreateMap(tileArray);

    SearchAndSetResourceDir("resources");//needed to add this to make wabbit appear in game
    Texture wabbit = LoadTexture("wabbit_alpha.png");
    Vector2 wabbitPosition = { (float)PCG::SCREEN_WIDTH / 2, (float)PCG::SCREEN_HEIGHT / 2 };

    Texture stone = LoadTexture("stone.png");
    Texture grass = LoadTexture("grass.png");
    Texture sand = LoadTexture("sand.png");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        //Map
        //DrawMap(tileArray);
        PCG::DrawMap(tileArray, grass, stone, sand);
        DrawText("Construct Map Editor", 20, 20, 20, WHITE);
        
        //wabbit
        if (IsKeyDown(RIGHT)) wabbitPosition.x += RIGHT_SPEED;
        if (IsKeyDown(LEFT)) wabbitPosition.x -= LEFT_SPEED;
        if (IsKeyDown(UP)) wabbitPosition.y -= UP_SPEED;
        if (IsKeyDown(DOWN)) wabbitPosition.y += DOWN_SPEED;
        DrawTexture(wabbit, wabbitPosition.x, wabbitPosition.y, WHITE);

        //GUI
        PCG::DrawGUI(tileArray);

        EndDrawing();
    }
    UnloadTexture(wabbit);
    UnloadTexture(stone);
    UnloadTexture(grass);
    UnloadTexture(sand);
    CloseWindow();
    return 0;
}