#include "GameWindow.h"
#include <QMessageBox>
#include <QPixmap>

// Set an icon for a flagged tile
QPixmap flagIcon("assets/flag.png");
button->setIcon(QIcon(flagIcon));
button->setIconSize(QSize(30, 30));

// Set an icon for a mine
QPixmap mineIcon("assets/mine.png");
button->setIcon(QIcon(mineIcon));

GameWindow::GameWindow(QWidget *parent) : QWidget(parent) {
    gridLayout = new QGridLayout(this);
    mineGrid = new MineGrid(30, 16, 99);

    for (int x = 0; x < 30; ++x) {
        std::vector<QPushButton*> row;
        for (int y = 0; y < 16; ++y) {
            QPushButton *btn = new QPushButton();
            btn->setFixedSize(30, 30);
            connect(btn, &QPushButton::clicked, this, &GameWindow::handleClick);
            gridLayout->addWidget(btn, y, x);
            row.push_back(btn);
        }
        buttons.push_back(row);
    }
}

void GameWindow::handleClick() {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    int x, y;
    gridLayout->getItemPosition(gridLayout->indexOf(btn), &y, &x, nullptr, nullptr);

    if (mineGrid->isMine(x, y)) {
        QMessageBox::information(this, "Game Over", "You hit a mine!");
        resetGame();
    } else {
        btn->setText(QString::number(mineGrid->adjacentMines(x, y)));
    }
}

void GameWindow::resetGame() {
    mineGrid->resetGrid();
    for (auto &row : buttons)
        for (auto *btn : row)
            btn->setText("");
}
