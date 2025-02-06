#include "MineGrid.h"
#include <QRandomGenerator>

/**
 * @brief Constructor for MineGrid.
 * @param width The width of the grid.
 * @param height The height of the grid.
 * @param mineCount The number of mines to be placed.
 */
MineGrid::MineGrid(int width, int height, int mineCount)
    : width(width), height(height), mineCount(mineCount)
{
    resetGrid();
}

/**
 * @brief Resets and reinitializes the grid with new mine placements.
 */
void MineGrid::resetGrid()
{
    mineGrid = QVector<QVector<bool>>(height, QVector<bool>(width, false));
    adjacentMines = QVector<QVector<int>>(height, QVector<int>(width, 0));
    initializeGrid();
    calculateAdjacentMines();
}

/**
 * @brief Initializes the grid with randomly placed mines.
 */
void MineGrid::initializeGrid()
{
    int placedMines = 0;
    while (placedMines < mineCount)
    {
        int row = QRandomGenerator::global()->bounded(height);
        int col = QRandomGenerator::global()->bounded(width);

        if (!mineGrid[row][col])
        {
            mineGrid[row][col] = true;
            placedMines++;
        }
    }
}

/**
 * @brief Calculates the number of adjacent mines for each cell.
 */
void MineGrid::calculateAdjacentMines()
{
    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            if (mineGrid[row][col])
            {
                adjacentMines[row][col] = -1; // Mark as a mine
                continue;
            }

            int count = 0;
            for (int i = -1; i <= 1; ++i)
            {
                for (int j = -1; j <= 1; ++j)
                {
                    int newRow = row + i;
                    int newCol = col + j;

                    if (newRow >= 0 && newRow < height && newCol >= 0 && newCol < width)
                    {
                        if (mineGrid[newRow][newCol])
                        {
                            count++;
                        }
                    }
                }
            }
            adjacentMines[row][col] = count;
        }
    }
}

/**
 * @brief Checks if a cell contains a mine.
 * @param row The row index.
 * @param col The column index.
 * @return True if the cell contains a mine, otherwise false.
 */
bool MineGrid::isMine(int row, int col) const
{
    return mineGrid[row][col];
}

/**
 * @brief Gets the number of adjacent mines for a given cell.
 * @param row The row index.
 * @param col The column index.
 * @return The count of mines surrounding the cell.
 */
int MineGrid::getAdjacentMineCount(int row, int col) const
{
    return adjacentMines[row][col];
}







