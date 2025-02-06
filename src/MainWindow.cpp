#include "MainWindow.h"
#include "GameWindow.h"

#include <QMenuBar>
#include <QMenu>
#include <QAction>

/*
 * MainWindow Constructor:
 * - Initializes the central widget (GameWindow).
 * - Sets up the menu bar with "New Game" and "Exit" options.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Create the game window and set it as the central widget.
    gameWindow = new GameWindow(this);
    setCentralWidget(gameWindow);

    // Create a "Game" menu in the menu bar.
    QMenu *gameMenu = menuBar()->addMenu(tr("&Game"));

    // Create "New Game" and "Exit" actions.
    QAction *newGameAction = new QAction(tr("&New Game"), this);
    QAction *exitAction = new QAction(tr("E&xit"), this);

    // Add actions to the menu.
    gameMenu->addAction(newGameAction);
    gameMenu->addSeparator();
    gameMenu->addAction(exitAction);

    // Connect menu actions to corresponding slots.
    connect(newGameAction, &QAction::triggered, this, &MainWindow::newGame);
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);

    setWindowTitle(tr("Minesweeper"));
    resize(800, 600);
}

/*
 * Destructor: Cleanup is handled automatically since gameWindow is a child widget.
 */
MainWindow::~MainWindow() {
}

/*
 * Slot to start a new game:
 * Deletes the current GameWindow and creates a new one.
 */
void MainWindow::newGame() {
    if (gameWindow) {
        gameWindow->deleteLater();
    }
    gameWindow = new GameWindow(this);
    setCentralWidget(gameWindow);
}

