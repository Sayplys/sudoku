# Sudoku

A simple Sudoku project designed to generate, validate, and solve Sudoku puzzles. This project provides functionalities for creating Sudoku boards, adding and removing numbers, and includes a user interface for interaction.

## Primary Functionalities

- [x] Structure
    - [x] Table
    - [x] Add random values
        - [x] Difficulty
    - [x] Verify addition
- [ ] Interaction
    - [ ] Add number to square
    - [ ] Remove number from square
- [ ] Interface
    - [ ] Show table
    - [ ] Select square
    - [ ] Add number
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

- C Compiler (e.g., GCC)
- Make (optional, for build automation)

### Build Instructions

1. Clone the repository:
    ```sh
    git clone https://github.com/Sayplys/sudoku.git
    cd sudoku/src
    ```

2. Compile the project:
    ```sh
    gcc -o sudoku sudokuCreator.c
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

