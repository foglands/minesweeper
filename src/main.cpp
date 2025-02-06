#include <QApplication>
#include "MainWindow.h"

/**
 * @brief The main entry point of the Minesweeper application.
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 * @return The application's exit status.
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
