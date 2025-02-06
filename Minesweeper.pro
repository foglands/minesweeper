# Qt project file for Minesweeper

QT += core gui widgets

CONFIG += c++11

# Define the target application
TARGET = Minesweeper
TEMPLATE = app

# Include the source and header files
SOURCES += \
    main.cpp \
    MainWindow.cpp \
    GameWindow.cpp \
    MineGrid.cpp

HEADERS += \
    MainWindow.h \
    GameWindow.h \
    MineGrid.h

# Resource file for assets (if needed)
RESOURCES += assets.qrc

# Compiler settings
QMAKE_CXXFLAGS += -Wall -Wextra
