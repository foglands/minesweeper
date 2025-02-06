#include "GameWindow.h"
#include <QMessageBox>
#include <QMouseEvent>

/**
 * @brief Constructor for GameWindow.
 * @param parent The parent QWidget.
 */
GameWindow::GameWindow(QWidget *parent) : QWidget(parent)
{
    gridLayout = new QGridLayout(this);
    mineGrid = new MineGrid(30, 16, 99); // 30x16 grid with 99 mines
    setupGrid();
}

/**
 * @brief Destructor for GameWindow.
 */
GameWindow::~GameWindow()
{
    delete mineGrid;
}

/**
 * @brief Initializes the game board with buttons.
 */
void GameWindow::setupGrid()
{
    buttons.resize(16, QVector<QPushButton*>(30));

    for (int row = 0; row < 16; ++row)
    {
        for (int col = 0; col < 30; ++col)
        {
            QPushButton *button = new QPushButton(this);
            button->setFixedSize(30, 30);
            button->setStyleSheet("background-color: lightgray;");

            // Connect left-click signal to reveal function
            connect(button, &QPushButton::clicked, this, &GameWindow::handleButtonClick);

            gridLayout->addWidget(button, row, col);
            buttons[row][col] = button;
        }
    }
}

/**
 * @brief Handles left-click on a tile.
 * @param row The row of the clicked tile.
 * @param col The column of the clicked tile.
 */
void GameWindow::revealTile(int row, int col)
{
    if (mineGrid->isMine(row, col))
    {
        buttons[row][col]->setIcon(QIcon(":/assets/mine.png"));
        QMessageBox::critical(this, "Game Over", "You hit a mine!");
        resetGame();
        return;
    }

    int adjacentMines = mineGrid->getAdjacentMineCount(row, col);
    if (adjacentMines == 0)
    {
        buttons[row][col]->setIcon(QIcon(":/assets/tile_0.png"));
    }
    else
    {
        buttons[row][col]->setIcon(QIcon(QString(":/assets/tile_%1.png").arg(adjacentMines)));
    }

    buttons[row][col]->setEnabled(false);
    checkWinCondition();
}

/**
 * @brief Handles right-click (flagging a tile).
 * @param row The row of the flagged tile.
 * @param col The column of the flagged tile.
 */
void GameWindow::flagTile(int row, int col)
{
    QPushButton *button = buttons[row][col];
    if (button->icon().isNull())  // Not flagged yet
    {
        button->setIcon(QIcon(":/assets/flag.png"));
    }
    else
    {
        button->setIcon(QIcon()); // Remove flag
    }
}

/**
 * @brief Checks if the player has won the game.
 */
void GameWindow::checkWinCondition()
{
    for (int row = 0; row < 16; ++row)
    {
        for (int col = 0; col < 30; ++col)
        {
            if (!mineGrid->isMine(row, col) && buttons[row][col]->isEnabled())
            {
                return; // Still some non-mine spaces left
            }
        }
    }
    QMessageBox::information(this, "Congratulations!", "You won!");
    resetGame();
}

/**
 * @brief Resets the game board.
 */
void GameWindow::resetGame()
{
    mineGrid->resetGrid();
    for (int row = 0; row < 16; ++row)
    {
        for (int col = 0; col < 30; ++col)
        {
            buttons[row][col]->setEnabled(true);
            buttons[row][col]->setIcon(QIcon());
        }
    }
}

/**
 * @brief Slot function to handle button clicks (left-clicks).
 */
void GameWindow::handleButtonClick()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    for (int row = 0; row < 16; ++row)
    {
        for (int col = 0; col < 30; ++col)
        {
            if (buttons[row][col] == button)
            {
                revealTile(row, col);
                return;
            }
        }
    }
}

/**
 * @brief Slot function to handle right-clicks.
 */
void GameWindow::handleRightClick()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    for (int row = 0; row < 16; ++row)
    {
        for (int col = 0; col < 30; ++col)
        {
            if (buttons[row][col] == button)
            {
                flagTile(row, col);
                return;
            }
        }
    }
}







