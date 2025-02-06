#ifndef MINEGRID_H
#define MINEGRID_H

#include <QWidget>
#include <vector>
#include <QPushButton>
#include <QMouseEvent>
#include <QIcon>
#include <QSize>

// Forward declaration for QGridLayout
class QGridLayout;

/*
 * MineGrid Class:
 *
 * Implements the Minesweeper game grid (30x16) with 99 mines.
 * This class manages the state of each cell, handles user interactions,
 * and performs the game logic including mine placement, calculating adjacent
 * mine counts, and revealing cells.
 */
class MineGrid : public QWidget {
    Q_OBJECT
public:
    explicit MineGrid(QWidget *parent = nullptr);

private slots:
    // Slot for handling left-click events on a cell.
    void handleLeftClick(int row, int col);
    // Slot for handling right-click events on a cell.
    void handleRightClick(int row, int col);

private:
    // Structure representing a single cell on the grid.
    struct Cell {
        bool hasMine = false;         // True if this cell contains a mine.
        bool isOpened = false;        // True if the cell has been revealed.
        int adjacentMines = 0;        // Number of adjacent mines.
        enum MarkState { None, Flag, Question } mark = None; // Marking state.
    };

    // Constants for grid dimensions and mine count.
    static const int COLS = 30;
    static const int ROWS = 16;
    static const int MINES = 99;

    QGridLayout *gridLayout;  // Layout manager for placing cells.
    std::vector<std::vector<Cell>> cells;             // 2D vector of cell states.
    std::vector<std::vector<class CellButton*>> buttons; // 2D vector of pointers to cell buttons.

    // Initialization and setup functions.
    void initializeBoard();
    void placeMines();
    void calculateAdjacencies();

    // Functions for revealing cells.
    void revealCell(int row, int col);
    void revealAdjacentZeros(int row, int col);

    // Checks if the win condition is met.
    bool checkWin();
    // Ends the game and reveals all mines.
    void gameOver(bool won);
};

/*
 * CellButton Class:
 *
 * A custom QPushButton that represents an individual cell.
 * It overrides the mousePressEvent to emit separate signals for
 * left-clicks and right-clicks.
 */
class CellButton : public QPushButton {
    Q_OBJECT
public:
    /*
     * Constructor for CellButton.
     * @param row: The row index of the cell.
     * @param col: The column index of the cell.
     * @param parent: The parent widget.
     */
    explicit CellButton(int row, int col, QWidget *parent = nullptr)
        : QPushButton(parent), m_row(row), m_col(col) {
        // Set a fixed size (adjust based on your asset sizes).
        setFixedSize(30, 30);
        // Disable focus to remove the focus rectangle.
        setFocusPolicy(Qt::NoFocus);
        // Set the default icon to the unrevealed image.
        setIcon(QIcon("assets/unrevealed.png"));
        setIconSize(QSize(30, 30));
    }
    
    // Accessor functions.
    int row() const { return m_row; }
    int col() const { return m_col; }
    
protected:
    // Override mousePressEvent to handle left and right clicks.
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            emit leftClicked(m_row, m_col);
        } else if (event->button() == Qt::RightButton) {
            emit rightClicked(m_row, m_col);
        }
        // Do not call the base class implementation to avoid default behavior.
    }

signals:
    // Signal emitted when the cell is left-clicked.
    void leftClicked(int row, int col);
    // Signal emitted when the cell is right-clicked.
    void rightClicked(int row, int col);

private:
    int m_row; // Row index.
    int m_col; // Column index.
};

#endif // MINEGRID_H

