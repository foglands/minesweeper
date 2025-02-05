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
    // Reset grid to all zeros
    grid.assign(width, std::vector<int>(height, 0));
    revealed.assign(width, std::vector<bool>(height, false));
    flagged.assign(width, std::vector<bool>(height, false));

    // Generate new mines
    generateMines();
}


// Generates mines randomly on the grid
void MineGrid::generateMines() {
    srand(time(nullptr));
    int placedMines = 0;

    while (placedMines < mineCount) {
        int x = rand() % width;
        int y = rand() % height;

        // Ensure mine isn't placed on top of another mine
        if (grid[x][y] == 0) {
            grid[x][y] = -1; // Place a mine
            placedMines++;
        }
    }
}


// Returns the number of mines adjacent to (x, y)
int MineGrid::adjacentMines(int x, int y) const {
    if (!isWithinBounds(x, y)) return 0; // Prevents crashes

    int count = 0;

    // Iterate through surrounding 8 cells
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            int nx = x + dx, ny = y + dy;
            if (isWithinBounds(nx, ny) && isMine(nx, ny)) {
                count++;
            }
        }
    }
    return count;
}


// Returns true if (x, y) is within valid board range
bool MineGrid::isWithinBounds(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}


// Checks if a tile contains a mine
bool MineGrid::isMine(int x, int y) const {
    return isWithinBounds(x, y) && grid[x][y] == -1;
}

