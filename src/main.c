#include "raylib.h"
#include "raygui.h"//remove once the slider code is out of here
#include "resource_dir.h"
#include "PCG.h" // Import our new module

float sliderValue = 50.0f; // Initial value
Rectangle sliderRec = { 100, 100, 200, 20 };

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Construct Map Editor");

    TileType tileArray[MAP_ROWS][MAP_COLUMNS] = { 0 };
    PCG_CreateMap(tileArray);

    SearchAndSetResourceDir("resources");//needed to add this to find wabbit in folder
    Texture wabbit = LoadTexture("wabbit_alpha.png");
    Vector2 wabbitPosition = { (float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 };

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        PCG_DrawMap(tileArray);
        DrawText("Construct Map Editor", 20, 20, 20, WHITE);
        PCG_DrawGUI(tileArray);
        
        if (IsKeyDown(RIGHT)) wabbitPosition.x += 5.0f;
        if (IsKeyDown(LEFT)) wabbitPosition.x -= 5.0f;
        if (IsKeyDown(UP)) wabbitPosition.y -= 5.0f;
        if (IsKeyDown(DOWN)) wabbitPosition.y += 5.0f;

        DrawTexture(wabbit, wabbitPosition.x, wabbitPosition.y, WHITE);

        // Draws the slider and updates 'sliderValue' based on user interaction
        GuiSlider(sliderRec, "Min", "Max", &sliderValue, 0.0f, 100.0f);
        DrawText(TextFormat("Value: %.2f", sliderValue), 100, 130, 20, WHITE);

        EndDrawing();
    }
    UnloadTexture(wabbit);
    CloseWindow();
    return 0;
}