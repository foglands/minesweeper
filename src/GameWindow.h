// GameWindow.h
// Defines the GameWindow class responsible for the Minesweeper UI.

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include "MineGrid.h"
#include <map>
#include <QMouseEvent>

class GameWindow : public QWidget {
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr); // Constructor
    void resetGame(); // Function to reset the game

protected:
    void mousePressEvent(QMouseEvent *event) override; // Detect right-click

private:
    QGridLayout *gridLayout; // Layout for game grid
    MineGrid *mineGrid; // Game logic class
    std::vector<std::vector<QPushButton*>> buttons; // Button grid
    std::map<QPushButton*, std::pair<int, int>> buttonPositions; // Stores button positions

private slots:
    void handleClick(); // Handles left-click
    void handleRightClick(QPushButton *btn); // Handles right-click for flagging
};

#endif // GAMEWINDOW_H

