# Broker App

## Info

This is a TUI game which simulates investment market and lets player control a
fund: buy or sell investment lots.

Github repo: <https://github.com/MichaelX-code/BrokerApp>

## Project structure

- 📁 `build`
- 📂 `assets`
  - `available_investments.csv`
- 📂 `include`
  - 📂 `investments`
    - `investment.class`
    - `stock.class`
    - `obligation.class`
    - `metal.class`
    - `currency.class`
  - 📂 `utils`
    - `utils.h`
    - `utils.cpp`
    - `date.class`
    - `list.class`
    - `csv_parser.class`
  - `game.class`
  - `market.class`
  - `fund.class`
- `main.cpp`
- `README.md`
- `CMakeLists.txt`

> `.class` stands for class implementation in 2 files: `.h` or `.hpp` and `.cpp`

### OOP structure

Investments classes:

    - Investment      (abstract)
      - Stock         (inherited from Investment)
      - Obligation    (inherited from Investment)
      - Metal         (inherited from Investment)
      - Currency      (inherited from Investment)

Game classes:

    - Game
    - Market
    - Fund

Utility classes:

    - list            (template)
    - date_t
    - csv_parser_t

## Build instructions

### Windows Visual Studio

1. Open project folder in `Visual Studio`;
1. Set up *CMake* project: *Project > Configure BrokerApp*;
1. Open `main.cpp` file;
1. Build using run button.

### Linux & MacOS

1. If you don't have *CMake*, install it using your package manager;
1. Open project folder in terminal and build using commands:

    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

1. Run using `./BrokerApp` in `build` folder.

## To-do

- [ ] Implement logger class which writes everything into separate file
- [ ] Improve data set to be more realistic
