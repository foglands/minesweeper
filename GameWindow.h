#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include "MineGrid.h"

class GameWindow : public QWidget {
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    void resetGame();

private:
    QGridLayout *gridLayout;
    MineGrid *mineGrid;
    std::vector<std::vector<QPushButton*>> buttons;

private slots:
    void handleClick();
};

#endif
