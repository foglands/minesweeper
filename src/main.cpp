// main.cpp
// Entry point for the Minesweeper game using Qt.

#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    // Initialize the Qt application
    QApplication app(argc, argv);
    
    // Create and display the main window
    MainWindow window;
    window.show();
    
    // Start the event loop
    return app.exec();
}
