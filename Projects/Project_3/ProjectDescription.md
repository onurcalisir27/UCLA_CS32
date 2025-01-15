# Project 2: Mancala (Kalah) Game Implementation

This project implements the game of Mancala (Kalah) in C++, allowing for human and computer players. The game mechanics include sown seeds, capturing moves, and turn-based gameplay with support for AI decision-making.

## Objectives
- Design and implement the game mechanics of Mancala.
- Develop AI players with varying strategies.
- Apply object-oriented programming principles to manage game components and interactions.

## Features
1. **Game Mechanics**:
   - Sowing seeds in pits and capturing opponent's seeds.
   - Determining game outcomes, including ties and wins.

2. **Players**:
   - **HumanPlayer**: Allows interactive gameplay for human players.
   - **BadPlayer**: A basic AI player that selects the first valid move.
   - **SmartPlayer**: An advanced AI using a recursive search strategy and heuristic evaluation.

3. **Custom Board and Rules**:
   - Adjustable number of pits and seeds per pit.
   - Support for standard Mancala rules with pots for each player.

## File Descriptions
1. **`Board.h` and `Board.cpp`**:
   - Implements the game board, including pits, pots, and beans.
   - Functions for sowing seeds, capturing moves, and managing game state.

2. **`Game.h` and `Game.cpp`**:
   - Handles the overall gameplay, including turns, status checks, and winner determination.
   - Manages interactions between players and the board.

3. **`Player.h` and `Player.cpp`**:
   - Defines the base `Player` class and derived classes for human and AI players.
   - `SmartPlayer` uses recursive search with heuristic evaluation to choose optimal moves.

4. **`Side.h`**:
   - Defines enumerations for player sides (NORTH and SOUTH) and helper functions like `opponent()`.

5. **`Main.cpp`**:
   - Contains test cases for individual components and an example gameplay simulation.

## Challenges Overcome
- Debugging complex interactions between the board and players.
- Optimizing the AI's recursive search to balance decision quality and computation time.
- Managing edge cases like empty pits and tied games.

## Sample Gameplay
1. **Game Initialization**:
   ```cpp
   SmartPlayer sp1("Alice");
   SmartPlayer sp2("Bob");
   Board b(6, 4);
   Game g(b, &sp1, &sp2);
   g.play();
   
## Skills Developed
  - Recursive search and heuristic evaluation for AI decision-making.
  - Designing multi-class systems with OOP principles.
  - Debugging complex, interdependent game logic.
