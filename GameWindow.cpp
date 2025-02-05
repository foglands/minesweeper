// GameWindow.cpp
// Implements the Minesweeper game logic and UI interaction.

#include "GameWindow.h"
#include <QMessageBox>

// Constructor: Initializes the Minesweeper game grid
GameWindow::GameWindow(QWidget *parent) : QWidget(parent) {
    gridLayout = new QGridLayout(this);
    mineGrid = new MineGrid(30, 16, 99); // 30x16 grid with 99 mines

    // Create the grid of buttons
    for (int x = 0; x < 30; ++x) {
        for (int y = 0; y < 16; ++y) {
            QPushButton *btn = new QPushButton();
            btn->setFixedSize(30, 30);
            connect(btn, &QPushButton::clicked, this, &GameWindow::handleClick);
            gridLayout->addWidget(btn, y, x);
        
            // Store button coordinates in map
            buttonPositions[btn] = {x, y};
        }
    }

}

// Handles user clicks on grid buttons
void GameWindow::handleClick() {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    
    if (buttonPositions.find(btn) == buttonPositions.end()) {
        qDebug() << "Error: Button not found in map!";
        return; // Prevent segmentation fault
    }

    int x = buttonPositions[btn].first;
    int y = buttonPositions[btn].second;

    if (mineGrid->isMine(x, y)) {
        QMessageBox::information(this, "Game Over", "You hit a mine!");
        resetGame();
    } else {
        btn->setText(QString::number(mineGrid->adjacentMines(x, y)));
    }
}

// Resets the game state
void GameWindow::resetGame() {
    mineGrid->resetGrid();
    for (auto &row : buttons)
        for (auto *btn : row)
            btn->setText("");
}
