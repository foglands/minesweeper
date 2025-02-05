// GameWindow.cpp
// Implements the Minesweeper game logic and UI interaction.

#include "GameWindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QMouseEvent>
#include <QApplication> // Fix: Include QApplication

// Constructor: Initializes the Minesweeper game grid
GameWindow::GameWindow(QWidget *parent) : QWidget(parent) {
    gridLayout = new QGridLayout(this);
    mineGrid = new MineGrid(30, 16, 99); // 30x16 grid with 99 mines

    // Create the grid of buttons
    for (int x = 0; x < 30; ++x) {
        std::vector<QPushButton*> row;
        for (int y = 0; y < 16; ++y) {
            QPushButton *btn = new QPushButton();
            btn->setFixedSize(30, 30);
            connect(btn, &QPushButton::clicked, this, &GameWindow::handleClick);
            gridLayout->addWidget(btn, y, x);
            row.push_back(btn);
            buttonPositions[btn] = {x, y}; // Store position
        }
        buttons.push_back(row);
    }
}

// Handles user left-clicks
void GameWindow::handleClick() {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());

    if (!btn || buttonPositions.find(btn) == buttonPositions.end()) {
        qDebug() << "Error: Invalid button!";
        return;
    }

    int x = buttonPositions[btn].first;
    int y = buttonPositions[btn].second;

    if (mineGrid->isMine(x, y)) {
        // Reveal all mines when the game is lost
        for (int i = 0; i < 30; i++) {
            for (int j = 0; j < 16; j++) {
                if (mineGrid->isMine(i, j)) {
                    buttons[i][j]->setIcon(QIcon("assets/mine.png")); // Show mine icon
                }
            }
        }

        // Show Game Over popup
        QMessageBox msgBox;
        msgBox.setText("Game Over! You hit a mine.");
        msgBox.setInformativeText("Do you want to restart?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();

        if (ret == QMessageBox::Yes) {
            resetGame();
        } else {
            QApplication::quit();
        }
        return;
    } else {
        btn->setText(QString::number(mineGrid->adjacentMines(x, y)));
    }
}

// Handles right-click to place flags
void GameWindow::handleRightClick(QPushButton *btn) {
    if (!btn || buttonPositions.find(btn) == buttonPositions.end()) {
        qDebug() << "Error: Invalid button!";
        return;
    }

    int x = buttonPositions[btn].first;
    int y = buttonPositions[btn].second;

    if (!mineGrid->isRevealed(x, y)) {
        if (mineGrid->isFlagged(x, y)) {
            btn->setIcon(QIcon()); // Remove flag
            mineGrid->setFlag(x, y, false);
        } else {
            btn->setIcon(QIcon("assets/flag.png")); // Set flag icon
            mineGrid->setFlag(x, y, true);
        }
    }
}

// Detect right-click on grid buttons
void GameWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        QPushButton *btn = qobject_cast<QPushButton*>(childAt(event->pos()));
        if (btn) {
            handleRightClick(btn);
        }
    } else {
        QWidget::mousePressEvent(event);
    }
}

// Resets the game state
void GameWindow::resetGame() {
    mineGrid->resetGrid();

    // Reset all button text and icons
    for (int x = 0; x < 30; ++x) {
        for (int y = 0; y < 16; ++y) {
            buttons[x][y]->setText("");
            buttons[x][y]->setIcon(QIcon()); // Clear icons
        }
    }
}





