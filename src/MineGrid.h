#ifndef MINEGRID_H
#define MINEGRID_H

#include <QWidget>
#include <vector>

class QGridLayout;
class CellButton;

/*
 * MineGrid class
 *
 * Implements the Minesweeper grid:
 * - A 30x16 board with 99 mines.
 * - Manages the state of each cell (whether it is a mine, opened, marked, etc.).
 * - Handles user interactions (left/right clicks).
 */
class MineGrid : public QWidget {
    Q_OBJECT
public:
    explicit MineGrid(QWidget *parent = nullptr);
    
private slots:
    // Handles a left-click event on a cell.
    void handleLeftClick(int row, int col);
    // Handles a right-click event on a cell.
    void handleRightClick(int row, int col);
    
private:
    // Structure representing a cell's state.
    struct Cell {
        bool hasMine = false;
        bool isOpened = false;
        int adjacentMines = 0;
        // Enumeration for marking state.
        enum MarkState { None, Flag, Question } mark = None;
    };

    static const int COLS = 30;  // Number of columns.
    static const int ROWS = 16;  // Number of rows.
    static const int MINES = 99; // Total number of mines.

    QGridLayout *gridLayout;  // Layout to hold the grid of cells.
    std::vector<std::vector<Cell>> cells;  // 2D vector to hold cell data.
    std::vector<std::vector<CellButton*>> buttons;  // 2D vector of pointers to the cell buttons.

    // Functions to set up and manage the board.
    void initializeBoard();
    void placeMines();
    void calculateAdjacencies();
    void revealCell(int row, int col);
    void revealAdjacentZeros(int row, int col);
    bool checkWin();
    void gameOver(bool won);
};

//
// CellButton class
//
// A custom QPushButton that represents a cell in the grid. It overrides the mousePressEvent
// to emit separate signals for left and right clicks, which the MineGrid uses to process moves.
//
#include <QPushButton>
#include <QMouseEvent>
#include <QIcon>
#include <QSize>

class CellButton : public QPushButton {
    Q_OBJECT
public:
    /*
     * Constructor for CellButton.
     * @param row: The row index of this cell.
     * @param col: The column index of this cell.
     * @param parent: The parent QWidget.
     */
    explicit CellButton(int row, int col, QWidget *parent = nullptr)
        : QPushButton(parent), m_row(row), m_col(col) {
        // Set a fixed size for the cell (adjust as necessary to match your assets).
        setFixedSize(30, 30);
        setFocusPolicy(Qt::NoFocus);
        // Set the default icon for an unrevealed cell.
        setIcon(QIcon("assets/unrevealed.png"));
        setIconSize(QSize(30, 30));
    }
    
    // Accessor functions for row and column indices.
    int row() const { return m_row; }
    int col() const { return m_col; }
    
protected:
    /*
     * Overrides mousePressEvent to detect left and right mouse clicks.
     */
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            emit leftClicked(m_row, m_col);
        } else if (event->button() == Qt::RightButton) {
            emit rightClicked(m_row, m_col);
        }
        // Do not call QPushButton's default mousePressEvent to avoid unwanted behavior.
    }
    
signals:
    // Signal emitted when the cell is left-clicked.
    void leftClicked(int row, int col);
    // Signal emitted when the cell is right-clicked.
    void rightClicked(int row, int col);
    
private:
    int m_row;  // Row index of the cell.
    int m_col;  // Column index of the cell.
};

#endif // MINEGRID_H
