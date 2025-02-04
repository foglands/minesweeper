# Minesweeper in C++ using Qt

## Overview
This project is a simple implementation of the classic **Minesweeper** game using **C++** and **Qt**. The game features a **30x16 grid** with **99 randomly placed mines**. The objective is to clear the board without clicking on any mines. 

## Features
- **Graphical interface using Qt**
- **Left-click to reveal a tile**
- **Right-click to flag/unflag a tile**
- **Randomized mine placement**
- **Winning and losing conditions** with popup messages
- **Game restart functionality**
- **Optimized game logic for performance**

## Requirements
To compile and run the game, you need:
- **A Unix/Linux environment (or Windows with WSL)**
- **Qt development tools (Qt 5 or Qt 6 recommended)**
- **C++ compiler (g++, clang, or MSVC)**
- **Git (for version control, optional)**

## Installation & Setup
### Linux & MacOS
1. Install Qt development tools:
   ```bash
   sudo apt update
   sudo apt install qtbase5-dev qtchooser qttools5-dev-tools qttools5-dev qmake
   ```
   *(For MacOS, use Homebrew: `brew install qt`)*

2. Clone the project repository:
   ```bash
   git clone https://github.com/foglands/minesweeper.git
   cd minesweeper
   ```

3. Compile the project:
   ```bash
   qmake
   make
   ```

4. Run the game:
   ```bash
   ./Minesweeper
   ```

### Windows (WSL Recommended)
1. Install **Windows Subsystem for Linux (WSL)** with Ubuntu.
2. Install Qt and required dependencies:
   ```bash
   sudo apt update && sudo apt install qtbase5-dev qtchooser qttools5-dev-tools qttools5-dev qmake
   ```
3. Follow the **Linux** compilation and execution steps above.

## How to Play
- **Left-click** on a tile to reveal it.
- **Right-click** on a tile to flag/unflag it as a suspected mine.
- **If you click on a mine, you lose the game.**
- **If you reveal all non-mine tiles, you win!**
- **After losing or winning, you can restart the game from the popup window.**

## Troubleshooting
- **Game doesn’t start?** Ensure Qt is properly installed:
  ```bash
  qmake --version
  ```
- **Errors while compiling?** Run `qmake` before `make` to regenerate the Makefile.
- **Graphics not showing in WSL?** Install an X server like **VcXsrv** and run:
  ```bash
  export DISPLAY=:0
  ```

## File Structure
```
/minesweeper/
│── src/
│   ├── main.cpp
│   ├── MineGrid.h
│   ├── MineGrid.cpp
│   ├── GameWindow.h
│   ├── GameWindow.cpp
│   ├── MainWindow.h
│   ├── MainWindow.cpp
│── assets/ (icons for flags, mines)
│── Minesweeper.pro (Qt project file)
│── README.md
```

## Contribution
1. Fork the repository on GitHub.
2. Create a feature branch:
   ```bash
   git checkout -b feature-branch
   ```
3. Commit your changes and push to your fork:
   ```bash
   git commit -m "Add new feature"
   git push origin feature-branch
   ```
4. Submit a pull request for review.

## Author
- **Foglands**
- Peng Peng
- Contact: ppeng8@uwo.ca
- Date: **February 2025**

## License
This project is licensed under the **MIT License**.
