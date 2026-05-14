// Maze.cpp
#include "PCG.h"

Tile maze[MAZE_WIDTH][MAZE_HEIGHT];

/*
W W W W
W W W W
W W W W
W W W W
*/
void InitialiseMaze() {

    for (int x = 0; x < MAZE_WIDTH; x++) {
        for (int y = 0; y < MAZE_HEIGHT; y++) {

            maze[x][y].wall = true;
            maze[x][y].visited = false;
        }
    }
}

/*
WWWWW
WSWWW
WWWWW
WWWWW
*/
void GenerateMaze(int x, int y) {

    maze[x][y].visited = true;
    maze[x][y].wall = false;

    while (true) {

        int directions[] = { 0, 1, 2, 3 };

        // Shuffle directions
        for (int i = 0; i < 4; i++) {

            int j = GetRandomValue(i, 3);

            int temp = directions[i];
            directions[i] = directions[j];
            directions[j] = temp;
        }

        bool moved = false;

        for (int i = 0; i < 4; i++) {

            int dx = 0;
            int dy = 0;

            // Up
            if (directions[i] == 0)
                dy = -2;

            // Right
            else if (directions[i] == 1)
                dx = 2;

            // Down
            else if (directions[i] == 2)
                dy = 2;

            // Left
            else if (directions[i] == 3)
                dx = -2;

            int nx = x + dx;
            int ny = y + dy;

            // Stay inside bounds
            if (nx > 0 &&
                nx < MAZE_WIDTH - 1 &&
                ny > 0 &&
                ny < MAZE_HEIGHT - 1 &&
                !maze[nx][ny].visited) {

                /*
                WWWWW
                WSSSW
                WWWSW
                WSSSW
                WWWWW
                */

                // Remove wall between cells
                maze[x + dx / 2][y + dy / 2].wall = false;

                GenerateMaze(nx, ny);

                moved = true;

                break;
            }
        }

        if (!moved)
            break;
    }
}

void ExportMazeTXT(const char* filename) {

    std::ofstream file(filename);

    if (!file.is_open())
        return;

    for (int y = 0; y < MAZE_HEIGHT; y++) {

        for (int x = 0; x < MAZE_WIDTH; x++) {

            if (maze[x][y].wall)
                file << 'W';
            else
                file << 'S';
        }

        file << "\n";
    }

    file.close();
}

void DrawMaze() {

    for (int x = 0; x < MAZE_WIDTH; x++) {
        for (int y = 0; y < MAZE_HEIGHT; y++) {

            Color color;

            if (maze[x][y].wall)
                color = BLACK;
            else
                color = WHITE;

            DrawRectangle(
                x * TILE_SIZE,
                y * TILE_SIZE,
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