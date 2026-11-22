# 🎮 C++ Mini Games — Neon Arcade

A colorful terminal arcade featuring **Tic Tac Toe** and **Snake Game**, built with C++17 and ncurses. Designed for Linux terminals and GitHub Codespaces.

## ✨ Features

- Neon-inspired arcade hub with colored headings and keyboard navigation.
- **Tic Tac Toe:** two-player X/O board, arrow-key selection, win/draw detection, scoreboard, restart and replay.
- **Snake:** real-time arrows/WASD controls, food, growth, score, session best, increasing speed, collision detection, pause and replay.

## Requirements

- C++17 compiler (GCC or Clang)
- CMake 3.16+
- ncurses development library
- Interactive terminal with color support

## Build and run in GitHub Codespaces (Ubuntu)

Install dependencies:

```bash
sudo apt-get update
sudo apt-get install -y build-essential cmake libncurses-dev
```

Build:

```bash
cmake -S . -B build
cmake --build build -j
```

Run in the Codespaces terminal:

```bash
./build/cpp_mini_games
```

Use an interactive terminal (not the Output panel). A terminal at least 70 columns wide and 24 rows high is recommended.

## Controls

| Action | Tic Tac Toe | Snake |
|---|---|---|
| Move | Arrow keys | Arrow keys or WASD |
| Place mark | Enter / Space | — |
| Restart | R | — |
| Pause/resume | — | P |
| Return to menu | Q | Q |

## Project structure

```text
cpp-mini-games/
├── include/ (UI.h, Menu.h, TicTacToe.h, SnakeGame.h)
├── src/ (main.cpp, UI.cpp, Menu.cpp, TicTacToe.cpp, SnakeGame.cpp)
├── CMakeLists.txt
├── .gitignore
└── README.md
```

Run it in a real terminal: ncurses needs interactive keyboard input and terminal rendering.
