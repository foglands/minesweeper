#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include "GameWindow.h"

/**
 * @class MainWindow
 * @brief The MainWindow class manages the overall application UI.
 * 
 * This class provides a menu bar for game controls and integrates 
 * the GameWindow for Minesweeper gameplay.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for MainWindow.
     * @param parent The parent QWidget.
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor for MainWindow.
     */
    ~MainWindow();

private:
    GameWindow *gameWindow; ///< The main Minesweeper game window.
    QMenuBar *menuBar; ///< The menu bar.
    QAction *newGameAction; ///< Action for starting a new game.
    QAction *exitAction; ///< Action for exiting the application.

    /**
     * @brief Initializes the menu bar.
     */
    void setupMenuBar();

private slots:
    /**
     * @brief Slot function to start a new game.
     */
    void startNewGame();

    /**
     * @brief Slot function to exit the application.
     */
    void exitGame();
};

#endif // MAINWINDOW_H
