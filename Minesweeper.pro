# Minesweeper.pro
# Qt project file for building Minesweeper using QMake

QT += core gui widgets
CONFIG += c++11

TARGET = Minesweeper
TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/MainWindow.cpp \
    src/GameWindow.cpp \
    src/MineGrid.cpp

HEADERS += \
    src/MainWindow.h \
    src/GameWindow.h \
    src/MineGrid.h

DESTDIR = bin/
INCLUDEPATH += src/
