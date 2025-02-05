// MainWindow.h
// Defines the MainWindow class responsible for handling the main game window.

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "GameWindow.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr); // Constructor
    ~MainWindow(); // Destructor

private:
    GameWindow *gameWindow; // Pointer to game window instance
};

#endif // MAINWINDOW_H
