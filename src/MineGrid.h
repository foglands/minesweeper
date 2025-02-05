// MineGrid.h
// Defines the MineGrid class, which handles game logic such as mine placement.

#ifndef MINEGRID_H
#define MINEGRID_H

#include <vector>

class MineGrid {
public:
    MineGrid(int width, int height, int mines); // Constructor
    void resetGrid(); // Resets the game grid
    bool isMine(int x, int y); // Checks if a cell contains a mine
    int adjacentMines(int x, int y); // Counts adjacent mines
    void revealCell(int x, int y); // Reveals a cell
    void flagCell(int x, int y); // Flags a cell
    bool isGameWon(); // Checks if the game is won
    bool isGameOver(); // Checks if the game is lost

private:
    int width, height, mineCount; // Grid size and number of mines
    std::vector<std::vector<int>> grid; // Grid data structure
    std::vector<std::vector<bool>> revealed; // Tracks revealed cells
    std::vector<std::vector<bool>> flagged; // Tracks flagged cells
    void generateMines(); // Generates mines in the grid
};

#endif // MINEGRID_H
