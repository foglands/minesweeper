# Qt project file for building Minesweeper using QMake

QT += core gui
CONFIG += c++11

# Add required Qt modules
QT += widgets

# Define the target executable name
TARGET = Minesweeper
TEMPLATE = app

# Include all source and header files
SOURCES += \
    src/main.cpp \
    src/MainWindow.cpp \
    src/GameWindow.cpp \
    src/MineGrid.cpp

HEADERS += \
    src/MainWindow.h \
    src/GameWindow.h \
    src/MineGrid.h

# Specify UI forms if any (currently none)
FORMS += 

# Set the build directory
DESTDIR = bin/

# Include paths if needed
INCLUDEPATH += src/

# Additional libraries (if needed in future)
LIBS += 

# Compiler and linker settings
QMAKE_CXXFLAGS += -Wall -Wextra
