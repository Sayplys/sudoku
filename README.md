# Sudoku

A simple Sudoku project designed to generate, validate, and solve Sudoku puzzles. This project provides functionalities for creating Sudoku boards, adding and removing numbers, and includes a user interface through terminal for interaction.

## Primary Functionalities

- [x] Structure
    - [x] Table
    - [x] Add random values
        - [x] Difficulty
    - [x] Verify addition
- [x] Interaction
    - [x] Add number to square
    - [x] Remove number from square
- [ ] Interface
    - [x] Show table
    - [x] Select square
    - [x] Add number
    - [ ] Remove number
    - [ ] Show win
    - [ ] Make new game
    - [ ] Show answers
- [ ] Implement solution algorithm
    - [ ] Create incidence matrix
    - [ ] Transform to doubly linked structure
    - [ ] Apply DLX algorithm

## Secondary Functionalities

- [ ] ...

## Setup and Running Instructions

### Prerequisites

- Linux
- C Compiler (e.g., GCC)

### Build Instructions

1. Clone the repository:
    ```sh
    git clone https://github.com/Sayplys/sudoku.git
    cd sudoku/src/gameLogic
    ```

2. Compile the project:
    ```sh
    gcc -o bin/sudoku.o src/main.c src/game/sudoku.c src/interface/displayer.c src/interface/handlers.c src/interface/listener.c
    ```

3. Run the executable:
    ```sh
    ./sudoku
    ```

### Usage

1. The program will generate a Sudoku board based on the specified difficulty level.

## Contribution

Feel free to fork this repository and submit pull requests. For major changes, please open an issue first to discuss what you would like to change.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

