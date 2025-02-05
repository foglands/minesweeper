// GameWindow.h
// This file defines the GameWindow class responsible for the Minesweeper UI.

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include "MineGrid.h"
#include <map>

class GameWindow : public QWidget {
private:
    std::map<QPushButton*, std::pair<int, int>> buttonPositions;
};

public:
    GameWindow(QWidget *parent = nullptr); // Constructor
    void resetGame(); // Function to reset the game

private:
    QGridLayout *gridLayout; // Layout for game grid
    MineGrid *mineGrid; // Logic class for handling the game grid
    std::vector<std::vector<QPushButton*>> buttons; // Button grid

private slots:
    void handleClick(); // Handles button clicks
};

#endif // GAMEWINDOW_H
