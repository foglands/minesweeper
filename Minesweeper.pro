# Qt project file for Minesweeper
QT       += widgets
CONFIG   += c++11
TARGET = Minesweeper
TEMPLATE = app

# List of source files.
SOURCES += src/main.cpp \
           src/MainWindow.cpp \
           src/GameWindow.cpp \
           src/MineGrid.cpp

# List of header files.
HEADERS += src/MainWindow.h \
           src/GameWindow.h \
           src/MineGrid.h

