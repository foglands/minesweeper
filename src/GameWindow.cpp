#include "GameWindow.h"
#include "MineGrid.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

/*
 * GameWindow Constructor:
 * - Sets up a vertical layout.
 * - Adds a top panel with a status label and reset button.
 * - Creates and adds the MineGrid (game board) widget.
 */
GameWindow::GameWindow(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Create the top panel layout.
    QHBoxLayout *topLayout = new QHBoxLayout();
    statusLabel = new QLabel(tr("Minesweeper"), this);
    resetButton = new QPushButton(tr("Reset"), this);
    topLayout->addWidget(statusLabel);
    topLayout->addStretch();  // Adds a flexible space between the label and button.
    topLayout->addWidget(resetButton);
    mainLayout->addLayout(topLayout);

    // Create the game board.
    mineGrid = new MineGrid(this);
    mainLayout->addWidget(mineGrid);

    // Connect the reset button signal to the resetGame slot.
    connect(resetButton, &QPushButton::clicked, this, &GameWindow::resetGame);
}

/*
 * Slot to reset the game:
 * Deletes the current MineGrid and creates a new one.
 */
void GameWindow::resetGame() {
    if (mineGrid) {
        mineGrid->deleteLater();
    }
    mineGrid = new MineGrid(this);
    QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout*>(this->layout());
    if (mainLayout) {
        mainLayout->addWidget(mineGrid);
    }
}







