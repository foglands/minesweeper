#include "MainWindow.h"
#include <QApplication>

/**
 * @brief Constructor for MainWindow.
 * @param parent The parent QWidget.
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    gameWindow = new GameWindow(this);
    setCentralWidget(gameWindow);

    setupMenuBar();
    setWindowTitle("Minesweeper");
    resize(900, 500);
}

/**
 * @brief Destructor for MainWindow.
 */
MainWindow::~MainWindow()
{
    delete gameWindow;
}

/**
 * @brief Initializes the menu bar with actions.
 */
void MainWindow::setupMenuBar()
{
    menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    QMenu *gameMenu = menuBar->addMenu("Game");

    // Create "New Game" action
    newGameAction = new QAction("New Game", this);
    connect(newGameAction, &QAction::triggered, this, &MainWindow::startNewGame);
    gameMenu->addAction(newGameAction);

    // Create "Exit" action
    exitAction = new QAction("Exit", this);
    connect(exitAction, &QAction::triggered, this, &MainWindow::exitGame);
    gameMenu->addAction(exitAction);
}

/**
 * @brief Slot function to start a new game.
 */
void MainWindow::startNewGame()
{
    gameWindow->resetGame();
}

/**
 * @brief Slot function to exit the application.
 */
void MainWindow::exitGame()
{
    QApplication::quit();
}


