#ifndef MINEGRID_H
#define MINEGRID_H

#include <QVector>

/**
 * @class MineGrid
 * @brief The MineGrid class handles mine placement and adjacent mine counts.
 * 
 * This class generates a Minesweeper board, randomly places mines, 
 * and calculates the number of adjacent mines for each cell.
 */
class MineGrid
{
public:
    /**
     * @brief Constructor for MineGrid.
     * @param width The width of the grid.
     * @param height The height of the grid.
     * @param mineCount The number of mines on the board.
     */
    MineGrid(int width, int height, int mineCount);

    /**
     * @brief Resets and reinitializes the grid with new mine placements.
     */
    void resetGrid();

    /**
     * @brief Checks if a cell contains a mine.
     * @param row The row index.
     * @param col The column index.
     * @return True if the cell contains a mine, otherwise false.
     */
    bool isMine(int row, int col) const;

    /**
     * @brief Gets the number of adjacent mines for a given cell.
     * @param row The row index.
     * @param col The column index.
     * @return The count of mines surrounding the cell.
     */
    int getAdjacentMineCount(int row, int col) const;

private:
    int width; ///< Grid width.
    int height; ///< Grid height.
    int mineCount; ///< Total number of mines.
    QVector<QVector<bool>> mineGrid; ///< 2D array representing mine placement.
    QVector<QVector<int>> adjacentMines; ///< 2D array storing adjacent mine counts.

    /**
     * @brief Initializes the grid with randomly placed mines.
     */
    void initializeGrid();

    /**
     * @brief Calculates the number of adjacent mines for each cell.
     */
    void calculateAdjacentMines();
};

#endif // MINEGRID_H

