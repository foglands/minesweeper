#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QVector>
#include "MineGrid.h"

/**
 * @class GameWindow
 * @brief The GameWindow class handles the Minesweeper game UI.
 * 
 * This class initializes the game board, processes user inputs, 
 * and manages game state changes.
 */
class GameWindow : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for GameWindow.
     * @param parent The parent QWidget.
     */
    explicit GameWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor for GameWindow.
     */
    ~GameWindow();

    /**
     * @brief Resets the game board.
     */
    void resetGame();

private:
    QGridLayout *gridLayout; ///< Grid layout to hold buttons.
    QVector<QVector<QPushButton*>> buttons; ///< 2D array of buttons for the grid.
    MineGrid *mineGrid; ///< Logic for mine placement and adjacent counts.

    /**
     * @brief Initializes the grid with buttons.
     */
    void setupGrid();

    /**
     * @brief Handles left-clicks on tiles.
     * @param row Row index of clicked tile.
     * @param col Column index of clicked tile.
     */
    void revealTile(int row, int col);

    /**
     * @brief Handles right-clicks on tiles (flagging).
     * @param row Row index of clicked tile.
     * @param col Column index of clicked tile.
     */
    void flagTile(int row, int col);

    /**
     * @brief Checks if the player has won the game.
     */
    void checkWinCondition();

private slots:
    /**
     * @brief Slot function for handling button clicks.
     */
    void handleButtonClick();

    /**
     * @brief Slot function for handling right-clicks.
     */
    void handleRightClick();
};

#endif // GAMEWINDOW_H
