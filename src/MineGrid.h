#ifndef MINEGRID_H
#define MINEGRID_H

#include <vector>

class MineGrid {
public:
    MineGrid(int width, int height, int mines);
    void resetGrid();
    bool isMine(int x, int y);
    int adjacentMines(int x, int y);
    void revealCell(int x, int y);
    void flagCell(int x, int y);
    bool isGameWon();
    bool isGameOver();

private:
    int width, height, mineCount;
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<bool>> revealed;
    std::vector<std::vector<bool>> flagged;
    void generateMines();
};

#endif
