#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>

// Forward declarations.
class MineGrid;
class QLabel;
class QPushButton;

/*
 * GameWindow class
 *
 * Contains the top panel (status label and reset button) and the MineGrid (game board).
 */
class GameWindow : public QWidget {
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr);
    
private slots:
    // Slot to reset the current game.
    void resetGame();
    
private:
    MineGrid *mineGrid;   // The Minesweeper grid.
    QLabel *statusLabel;  // Label to display status messages.
    QPushButton *resetButton;  // Button to reset the game.
};

#endif // GAMEWINDOW_H

