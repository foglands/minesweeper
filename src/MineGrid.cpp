#include "MineGrid.h"
#include <QGridLayout>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QIcon>
#include <QDebug>

/*
 * MineGrid Constructor:
 * - Creates a grid layout.
 * - Initializes the cells and buttons vectors.
 * - Creates a button for each cell and adds it to the layout.
 * - Connects each button's left and right click signals to the corresponding slots.
 * - Calls functions to place mines and calculate adjacent mine counts.
 */
MineGrid::MineGrid(QWidget *parent) : QWidget(parent)
{
    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(1);
    gridLayout->setContentsMargins(1, 1, 1, 1);

    // Resize the cells and buttons 2D vectors.
    cells.resize(ROWS, std::vector<Cell>(COLS));
    buttons.resize(ROWS, std::vector<CellButton*>(COLS, nullptr));

    // Create buttons for each cell.
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            CellButton *button = new CellButton(row, col, this);
            buttons[row][col] = button;
            gridLayout->addWidget(button, row, col);

            // Connect button signals to the MineGrid's slots.
            connect(button, &CellButton::leftClicked, this, &MineGrid::handleLeftClick);
            connect(button, &CellButton::rightClicked, this, &MineGrid::handleRightClick);
        }
    }

    // Initialize the board: place mines and compute adjacent counts.
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
 * Randomly places MINES number of mines on the board.
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
            // Check all adjacent cells (8 directions).
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
 * Handles a left-click event on a cell:
 * - Reveals the cell.
 * - Checks for win condition.
 */
void MineGrid::handleLeftClick(int row, int col) {
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS)
        return;
    if (cells[row][col].isOpened)
        return;

    // Reveal the cell.
    revealCell(row, col);

    // Check if the player has won after this move.
    if (checkWin()) {
        gameOver(true);
    }
}

/*
 * Handles a right-click event on a cell:
 * - Cycles the cell's marking state: None -> Flag -> Question -> None.
 * - Updates the icon or text accordingly.
 */
void MineGrid::handleRightClick(int row, int col) {
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS)
        return;
    if (cells[row][col].isOpened)
        return;

    // Cycle through marking states.
    if (cells[row][col].mark == Cell::None) {
        cells[row][col].mark = Cell::Flag;
        buttons[row][col]->setIcon(QIcon("assets/flag.png"));
        buttons[row][col]->setIconSize(QSize(30, 30));
    } else if (cells[row][col].mark == Cell::Flag) {
        cells[row][col].mark = Cell::Question;
        // For a question mark, remove the icon and show text.
        buttons[row][col]->setIcon(QIcon());
        buttons[row][col]->setText("?");
    } else {
        cells[row][col].mark = Cell::None;
        buttons[row][col]->setText("");
        // Restore the unrevealed icon.
        buttons[row][col]->setIcon(QIcon("assets/unrevealed.png"));
        buttons[row][col]->setIconSize(QSize(30, 30));
    }
}

/*
 * Reveals the cell at (row, col):
 * - If the cell contains a mine, displays the mine icon and ends the game.
 * - If the cell has adjacent mines, shows the appropriate numbered tile.
 * - If the cell is empty (zero adjacent mines), shows the blank revealed tile and
 *   recursively reveals adjacent cells.
 */
void MineGrid::revealCell(int row, int col) {
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS)
        return;
    if (cells[row][col].isOpened)
        return;

    // Mark the cell as opened and clear any mark.
    cells[row][col].isOpened = true;
    cells[row][col].mark = Cell::None;
    buttons[row][col]->setEnabled(false);

    // Clear any previous text or icon.
    buttons[row][col]->setText("");
    buttons[row][col]->setIcon(QIcon());

    // If the cell contains a mine, display the mine icon and trigger game over.
    if (cells[row][col].hasMine) {
        buttons[row][col]->setIcon(QIcon("assets/mine.png"));
        buttons[row][col]->setIconSize(QSize(30, 30));
        gameOver(false);
        return;
    }

    // If the cell has adjacent mines, show the numbered tile.
    if (cells[row][col].adjacentMines > 0) {
        QString tilePath = QString("assets/tile_%1.png").arg(cells[row][col].adjacentMines);
        buttons[row][col]->setIcon(QIcon(tilePath));
        buttons[row][col]->setIconSize(QSize(30, 30));
    } else {
        // If no adjacent mines, show the blank revealed tile and reveal adjacent cells.
        buttons[row][col]->setIcon(QIcon("assets/revealed.png"));
        buttons[row][col]->setIconSize(QSize(30, 30));
        revealAdjacentZeros(row, col);
    }
}

/*
 * Recursively reveals adjacent cells that have zero adjacent mines.
 */
void MineGrid::revealAdjacentZeros(int row, int col) {
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            int r = row + dr, c = col + dc;
            if (r >= 0 && r < ROWS && c >= 0 && c < COLS) {
                if (!cells[r][c].isOpened && !cells[r][c].hasMine) {
                    // Mark adjacent cell as opened.
                    cells[r][c].isOpened = true;
                    buttons[r][c]->setEnabled(false);
                    buttons[r][c]->setText("");
                    buttons[r][c]->setIcon(QIcon());
                    // Clear any mark.
                    if (cells[r][c].mark != Cell::None) {
                        cells[r][c].mark = Cell::None;
                    }
                    // Reveal the cell based on its adjacent mine count.
                    if (cells[r][c].adjacentMines > 0) {
                        QString tilePath = QString("assets/tile_%1.png").arg(cells[r][c].adjacentMines);
                        buttons[r][c]->setIcon(QIcon(tilePath));
                        buttons[r][c]->setIconSize(QSize(30, 30));
                    } else {
                        buttons[r][c]->setIcon(QIcon("assets/revealed.png"));
                        buttons[r][c]->setIconSize(QSize(30, 30));
                        revealAdjacentZeros(r, c); // Recursively reveal further.
                    }
                }
            }
        }
    }
}

/*
 * Checks if the player has won by ensuring that all non-mine cells are opened.
 * @return true if the win condition is met.
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
 * - Reveals all mines.
 * - Displays a message box indicating whether the player won or lost.
 * - Disables all buttons.
 * @param won: true if the player won, false if lost.
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






