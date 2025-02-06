#include <QApplication>
#include "MainWindow.h"

/*
 * Entry point for the Minesweeper application.
 * Creates a QApplication instance and displays the MainWindow.
 */
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
