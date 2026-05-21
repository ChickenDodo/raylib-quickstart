#include "maze.h"
#include "raygui.h"

Tile maze[MAX_SIZE][MAX_SIZE];
int mazeWidth = DEFAULT_MAZE_WIDTH;
int mazeHeight = DEFAULT_MAZE_HEIGHT;

// =============================================
// Maze generation reference
// https://www.youtube.com/watch?v=mh7X_I7uKHM
// =============================================

void InitialiseMaze() {

    /*
    Fill entire grid with walls first

    W W W W
    W W W W
    W W W W
    W W W W
    */

    for (int x = 0; x < mazeWidth; x++) {
        for (int y = 0; y < mazeHeight; y++) {

            maze[x][y].wall = true;
            maze[x][y].visited = false;
        }
    }
}

void GenerateMaze(int x, int y) { //recursive backtacking, carve a path, if it's invalid, undo,

    /*
    Starting point becomes a path

    W W W W W
    W S W W W
    W W W W W
    W W W W W
    */

    maze[x][y].visited = true; // mark current cell so we don't revisit it
    maze[x][y].wall = false;   // turn current cell into a path

    while (true) {

        int directions[4] = { 0, 1, 2, 3 };

        // Shuffle choices so maze is random every run
        for (int i = 0; i < 4; i++) {

            int j = GetRandomValue(i, 3);

            /*
            Example shuffle:

            before:
            0 1 2 3

            after shuffle:
            2 0 3 1
            */

            int temp = directions[i];
            directions[i] = directions[j];
            directions[j] = temp;
        }

        bool moved = false; // tracks if we successfully moved to a new cell

        for (int i = 0; i < 4; i++) {

            int dx = 0, dy = 0;

            // convert direction into movement, take 2 steps to carve wall between

            if (directions[i] == 0) dy = -2;      // UP
            else if (directions[i] == 1) dx = 2;  // RIGHT
            else if (directions[i] == 2) dy = 2;  // DOWN
            else if (directions[i] == 3) dx = -2; // LEFT

            int nx = x + dx; // next cell x
            int ny = y + dy; // next cell y

            // check if next cell is inside the maze and not visited yet
            if (nx > 0 && nx < mazeWidth - 1 &&
                ny > 0 && ny < mazeHeight - 1 &&
                !maze[nx][ny].visited) {

                /*
                carving

                W W W W W
                W S S S W
                W W W S W
                W S S S W
                W W W W W
                */

                // remove wall between current cell and next cell
                maze[x + dx / 2][y + dy / 2].wall = false;

                // move into the next cell and continue carving from there
                GenerateMaze(nx, ny);

                moved = true;
                break;        // stop checking other directions
            }
        }

        // if we cannot move anywhere, backtrack
        if (!moved)
            break;
    }
}

void ExportMazeTXT(const char* filename) {

    std::ofstream file(filename);

    if (!file.is_open())
        return;

    for (int y = 0; y < mazeHeight; y++) {
        for (int x = 0; x < mazeWidth; x++) {
            file << (maze[x][y].wall ? 'W' : 'S');
        }
        file << "\n";
    }
}

void DrawMaze() {
    const int MAZE_OFFSET_Y = 50;

    for (int x = 0; x < mazeWidth; x++) {
        for (int y = 0; y < mazeHeight; y++) {

            // If it's a wall → BLACK
            // If it's a path → WHITE
            Color color = maze[x][y].wall ? BLACK : WHITE;

            // Draw a square for each tile
            DrawRectangle(
                x * TILE_SIZE,
                y * TILE_SIZE + MAZE_OFFSET_Y, // shift down by offset
                TILE_SIZE,
                TILE_SIZE,
                color
            );
        }
    }
}

void RegenerateMaze() {

    InitialiseMaze();
    GenerateMaze(1, 1);
    ExportMazeTXT("maze.txt");
}

// =============================================
// helper to force odd values for maze size
// =============================================

static float SnapToOdd(float v) {
    int i = (int)roundf(v);
    if (i % 2 == 0) i += 1;
    return (float)i;
}

// =============================================
// GUI Stuff
// =============================================

float g_mazeWidthSlider = 9;
float g_mazeHeightSlider = 9;

void ApplyMazeSizeFromSliders() {
    mazeWidth = (int)g_mazeWidthSlider;
    mazeHeight = (int)g_mazeHeightSlider;
}

void DrawGUI() {

    const float sliderWidth = 220;
    const float sliderHeight = 20;
    const float padding = 20;
    const float spacing = 60;
    const float lineGap = 25;

    float x = GetScreenWidth() - sliderWidth - padding;
    float y = GetScreenHeight() - (spacing * 2) - padding;

    DrawText(
        "Press R to regenerate/export maze.txt",
        padding,
        padding,
        20,
        WHITE
    );

    // remember previous slider values
    static float oldW = g_mazeWidthSlider;
    static float oldH = g_mazeHeightSlider;

    // WIDTH
    GuiLabel(
        { x, y, sliderWidth, 20 },
        TextFormat("Maze Width: %d", (int)g_mazeWidthSlider)
    );

    GuiSlider(
        { x, y + lineGap, sliderWidth, sliderHeight },
        "3", "19",
        &g_mazeWidthSlider,
        3, 19
    );

    // HEIGHT
    GuiLabel(
        { x, y + spacing, sliderWidth, 20 },
        TextFormat("Maze Height: %d", (int)g_mazeHeightSlider)
    );

    GuiSlider(
        { x, y + spacing + lineGap, sliderWidth, sliderHeight },
        "3", "19",
        &g_mazeHeightSlider,
        3, 19
    );

    // enforce odd sizes
    g_mazeWidthSlider = SnapToOdd(g_mazeWidthSlider);
    g_mazeHeightSlider = SnapToOdd(g_mazeHeightSlider);

    // rebuild only when changed
    if (oldW != g_mazeWidthSlider || oldH != g_mazeHeightSlider)
    {
        ApplyMazeSizeFromSliders();
        RegenerateMaze();

        oldW = g_mazeWidthSlider;
        oldH = g_mazeHeightSlider;
    }
}