// MineGrid.cpp
// Implements game logic, such as mine placement and win/loss conditions.

#include "MineGrid.h"
#include <cstdlib>
#include <ctime>

// Constructor: Initializes the grid with mines
MineGrid::MineGrid(int width, int height, int mines)
    : width(width), height(height), mineCount(mines) {
    resetGrid();
}

// Resets the game grid
void MineGrid::resetGrid() {
    grid.assign(width, std::vector<int>(height, 0));
    revealed.assign(width, std::vector<bool>(height, false));
    flagged.assign(width, std::vector<bool>(height, false));
    generateMines();
}

// Generates mines randomly on the grid
void MineGrid::generateMines() {
    srand(time(nullptr));
    int placedMines = 0;
    while (placedMines < mineCount) {
        int x = rand() % width;
        int y = rand() % height;
        if (grid[x][y] != -1) {
            grid[x][y] = -1;
            placedMines++;
        }
    }
}

// Checks if a tile contains a mine
bool MineGrid::isMine(int x, int y) {
    return grid[x][y] == -1;
}
