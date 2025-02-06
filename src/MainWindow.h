#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Forward declaration of GameWindow so we can use it as a pointer.
class GameWindow;

/*
 * MainWindow class
 *
 * Inherits from QMainWindow. It creates the main window of the application,
 * including the menu bar with "New Game" and "Exit" actions, and holds the GameWindow.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private slots:
    // Slot to start a new game.
    void newGame();
    
private:
    GameWindow *gameWindow;  // The central game widget.
};

#endif // MAINWINDOW_H
