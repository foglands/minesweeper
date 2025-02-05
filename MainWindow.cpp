// MainWindow.cpp
// Implements the MainWindow class, setting up the main UI and event handling.

#include "MainWindow.h"

// Constructor: Initializes the main window and game window
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    gameWindow = new GameWindow(this);
    setCentralWidget(gameWindow);
    setWindowTitle("Minesweeper"); // Set the window title
    resize(900, 500); // Set the initial window size
}

// Destructor: Cleans up dynamically allocated objects
MainWindow::~MainWindow() {
    delete gameWindow;
}

