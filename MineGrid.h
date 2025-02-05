// MineGrid.h
// Defines the MineGrid class, handling game logic such as mine placement.

#ifndef MINEGRID_H
#define MINEGRID_H

#include <vector>

class MineGrid {
public:
    MineGrid(int width, int height, int mines); // Constructor

    void resetGrid();
    bool isMine(int x, int y) const;
    int adjacentMines(int x, int y) const;
    void revealCell(int x, int y);
    void flagCell(int x, int y);
    bool isGameWon() const;
    bool isGameOver() const;
    bool isRevealed(int x, int y) const;
    bool isFlagged(int x, int y) const;
    void setFlag(int x, int y, bool flag);

private:
    int width, height, mineCount;
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<bool>> revealed;
    std::vector<std::vector<bool>> flagged;

    void generateMines();
    bool isWithinBounds(int x, int y) const;
};

#endif // MINEGRID_H
