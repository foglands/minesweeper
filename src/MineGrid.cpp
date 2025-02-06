#include "MineGrid.h"
#include <QGridLayout>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QDebug>

/*
 * MineGrid Constructor:
 * - Creates and configures the grid layout.
 * - Initializes cell state and corresponding buttons.
 * - Connects button signals to the appropriate slots.
 * - Calls functions to place mines and compute adjacent mine counts.
 */
MineGrid::MineGrid(QWidget *parent) : QWidget(parent)
{
    // Create and configure the grid layout.
    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(1);
    gridLayout->setContentsMargins(1, 1, 1, 1);

    // Resize the 2D vectors for cells and buttons.
    cells.resize(ROWS, std::vector<Cell>(COLS));
    buttons.resize(ROWS, std::vector<CellButton*>(COLS, nullptr));

    // Create buttons for each cell and add them to the layout.
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            CellButton *button = new CellButton(row, col, this);
            buttons[row][col] = button;
            gridLayout->addWidget(button, row, col);

            // Connect left-click and right-click signals.
            connect(button, &CellButton::leftClicked, this, &MineGrid::handleLeftClick);
            connect(button, &CellButton::rightClicked, this, &MineGrid::handleRightClick);
        }
    }

    // Initialize the game board.
    initializeBoard();
}

/*
 * Initializes the board by placing mines and calculating adjacent mine counts.
 */
void MineGrid::initializeBoard() {
    placeMines();
    calculateAdjacencies();
}

/*
 * Randomly places the specified number of mines on the board.
 */
void MineGrid::placeMines() {
    int placedMines = 0;
    while (placedMines < MINES) {
        int row = QRandomGenerator::global()->bounded(ROWS);
        int col = QRandomGenerator::global()->bounded(COLS);
        if (!cells[row][col].hasMine) {
            cells[row][col].hasMine = true;
            ++placedMines;
        }
    }
}

/*
 * Calculates the number of adjacent mines for each cell.
 * For cells that contain a mine, sets adjacentMines to -1.
 */
void MineGrid::calculateAdjacencies() {
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            if (cells[row][col].hasMine) {
                cells[row][col].adjacentMines = -1;
                continue;
            }
            int count = 0;
            // Check all 8 neighboring cells.
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    if (dr == 0 && dc == 0)
                        continue;
                    int r = row + dr, c = col + dc;
                    if (r >= 0 && r < ROWS && c >= 0 && c < COLS && cells[r][c].hasMine)
                        ++count;
                }
            }
            cells[row][col].adjacentMines = count;
        }
    }
}

/*
 * Slot for handling left-click events on a cell.
 * Reveals the cell and checks for the win condition.
 */
void MineGrid::handleLeftClick(int row, int col) {
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS)
        return;
    if (cells[row][col].isOpened)
        return;

    // Reveal the cell.
    revealCell(row, col);

    // Check if all non-mine cells have been opened.
    if (checkWin()) {
        gameOver(true);
    }
}

/*
 * Slot for handling right-click events on a cell.
 * Cycles through marking states: None -> Flag -> Question -> None.
 */
void MineGrid::handleRightClick(int row, int col) {
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS)
        return;
    if (cells[row][col].isOpened)
        return;

    // Cycle the marking state.
    if (cells[row][col].mark == Cell::None) {
        cells[row][col].mark = Cell::Flag;
        buttons[row][col]->setIcon(QIcon("assets/flag.png"));
        buttons[row][col]->setIconSize(QSize(30, 30));
    } else if (cells[row][col].mark == Cell::Flag) {
        cells[row][col].mark = Cell::Question;
        // For a question mark, remove the icon and show a text marker.
        buttons[row][col]->setIcon(QIcon());
        buttons[row][col]->setText("?");
    } else {
        cells[row][col].mark = Cell::None;
        buttons[row][col]->setText("");
        // Restore the unrevealed cell icon.
        buttons[row][col]->setIcon(QIcon("assets/unrevealed.png"));
        buttons[row][col]->setIconSize(QSize(30, 30));
    }
}

/*
 * Reveals the cell at (row, col):
 * - If the cell contains a mine, displays the mine icon and ends the game.
 * - If the cell has adjacent mines (> 0), shows the numbered tile.
 * - If the cell has 0 adjacent mines, shows tile_0.png and recursively reveals neighbors.
 */
void MineGrid::revealCell(int row, int col) {
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS)
        return;
    if (cells[row][col].isOpened)
        return;

    // Mark the cell as opened and remove any previous mark.
    cells[row][col].isOpened = true;
    cells[row][col].mark = Cell::None;
    buttons[row][col]->setEnabled(false);
    
    // Clear any previous text or icon.
    buttons[row][col]->setText("");
    buttons[row][col]->setIcon(QIcon());

    // If the cell is a mine, display the mine icon and end the game.
    if (cells[row][col].hasMine) {
        buttons[row][col]->setIcon(QIcon("assets/mine.png"));
        buttons[row][col]->setIconSize(QSize(30, 30));
        gameOver(false);
        return;
    }

    // If the cell has adjacent mines, display the corresponding numbered tile.
    if (cells[row][col].adjacentMines > 0) {
        QString tilePath = QString("assets/tile_%1.png").arg(cells[row][col].adjacentMines);
        buttons[row][col]->setIcon(QIcon(tilePath));
        buttons[row][col]->setIconSize(QSize(30, 30));
    } else {
        // For a cell with 0 adjacent mines, use tile_0.png.
        buttons[row][col]->setIcon(QIcon("assets/tile_0.png"));
        buttons[row][col]->setIconSize(QSize(30, 30));
        // Recursively reveal adjacent cells.
        revealAdjacentZeros(row, col);
    }
}

/*
 * Recursively reveals adjacent cells that have 0 adjacent mines.
 */
void MineGrid::revealAdjacentZeros(int row, int col) {
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            int r = row + dr, c = col + dc;
            if (r >= 0 && r < ROWS && c >= 0 && c < COLS) {
                if (!cells[r][c].isOpened && !cells[r][c].hasMine) {
                    // Mark the cell as opened.
                    cells[r][c].isOpened = true;
                    buttons[r][c]->setEnabled(false);
                    buttons[r][c]->setText("");
                    buttons[r][c]->setIcon(QIcon());
                    
                    // Clear any mark.
                    if (cells[r][c].mark != Cell::None) {
                        cells[r][c].mark = Cell::None;
                    }
                    
                    // Reveal the cell: if it has adjacent mines, show the numbered tile.
                    if (cells[r][c].adjacentMines > 0) {
                        QString tilePath = QString("assets/tile_%1.png").arg(cells[r][c].adjacentMines);
                        buttons[r][c]->setIcon(QIcon(tilePath));
                        buttons[r][c]->setIconSize(QSize(30, 30));
                    } else {
                        // Otherwise, show tile_0.png and recursively reveal its neighbors.
                        buttons[r][c]->setIcon(QIcon("assets/tile_0.png"));
                        buttons[r][c]->setIconSize(QSize(30, 30));
                        revealAdjacentZeros(r, c);
                    }
                }
            }
        }
    }
}

/*
 * Checks if all non-mine cells have been revealed.
 * @return true if the player has won, false otherwise.
 */
bool MineGrid::checkWin() {
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            if (!cells[row][col].hasMine && !cells[row][col].isOpened)
                return false;
        }
    }
    return true;
}

/*
 * Ends the game:
 * - Reveals all mines on the board.
 * - Displays a message box indicating a win or loss.
 * - Disables further interaction with all cells.
 */
void MineGrid::gameOver(bool won) {
    // Reveal all mines.
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            if (cells[row][col].hasMine) {
                buttons[row][col]->setIcon(QIcon("assets/mine.png"));
                buttons[row][col]->setIconSize(QSize(30, 30));
                buttons[row][col]->setEnabled(false);
            }
        }
    }
    // Display game over message.
    QMessageBox::information(this, tr("Game Over"),
                             won ? tr("Congratulations! You Win!")
                                 : tr("You hit a mine! Game Over."));
    // Disable all buttons.
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            buttons[row][col]->setEnabled(false);
        }
    }
}







