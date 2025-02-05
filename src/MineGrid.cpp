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

        if (grid[x][y] == 0) { // Ensure no duplicate mines
            grid[x][y] = -1; // Place a mine
            placedMines++;
        }
    }
}

// Returns true if (x, y) is within valid board range
bool MineGrid::isWithinBounds(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

// Returns the number of mines adjacent to (x, y)
int MineGrid::adjacentMines(int x, int y) const {
    if (!isWithinBounds(x, y)) return 0;

    int count = 0;
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

// Checks if a tile contains a mine
bool MineGrid::isMine(int x, int y) const {
    return isWithinBounds(x, y) && grid[x][y] == -1;
}

// Returns true if the tile at (x, y) has been revealed
bool MineGrid::isRevealed(int x, int y) const {
    return isWithinBounds(x, y) && revealed[x][y];
}

// Returns true if the tile at (x, y) has been flagged
bool MineGrid::isFlagged(int x, int y) const {
    return isWithinBounds(x, y) && flagged[x][y];
}

// Sets or removes a flag at (x, y)
void MineGrid::setFlag(int x, int y, bool flag) {
    if (isWithinBounds(x, y) && !revealed[x][y]) {
        flagged[x][y] = flag;
    }
}





