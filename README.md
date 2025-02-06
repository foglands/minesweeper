# Minesweeper - Qt C++ Implementation

## Overview
This is a simple implementation of the classic Minesweeper game using **C++ and Qt**. The game features a **30x16 grid** with **99 mines**, a graphical user interface, and basic game mechanics.

## Features
- Left-click to **reveal** a tile.
- Right-click to **flag/unflag** a tile.
- Automatically opens empty spaces when a tile with **zero adjacent mines** is clicked.
- A **win condition** when all non-mine tiles are revealed.
- A **game-over condition** when clicking on a mine.
- A **restart option** via the menu bar.

## Prerequisites
- **Qt 5** or later installed on your system.
- A **Unix/Linux environment** (e.g., Ubuntu, macOS, or Windows with WSL).
- A C++ compiler that supports **C++11** or later.

## Installation and Compilation
1. Clone or download the project files.
2. Open a terminal and navigate to the project directory.
3. Run the following commands:

   ```sh
   qmake Minesweeper.pro
   make
   ```

4. Run the executable:

   ```sh
   ./Minesweeper
   ```

## Game Controls
| Action            | Mouse Input |
|------------------|------------|
| Reveal a tile   | Left-click  |
| Flag a tile     | Right-click |
| Restart Game    | Menu > New Game |
| Exit Game       | Menu > Exit |

## Asset Files
The game uses the following PNG image files for its UI, stored in the `assets/` folder:
- **flag.png** - Flag icon for marking mines.
- **mine.png** - Mine icon for when a mine is revealed.
- **revealed.png** - Generic revealed tile.
- **unrevealed.png** - Default tile before clicking.
- **tile_0.png** to **tile_8.png** - Tiles showing adjacent mine counts.

## Known Issues and Future Improvements
- **Right-click support on some platforms may require additional handling.**
- **A timer and leaderboard could be added in future versions.**
- **Improved UI styling and animations can enhance user experience.**

## License
This project is open-source and can be freely modified and distributed.

## Credits
Developed as part of a **C++ programming assignment** using **Qt** for graphical rendering.

