# Homework 3: Recursion, Polymorphism, and Advanced Algorithms

This homework focuses on recursive problem-solving, polymorphism in C++ class hierarchies, and solving mazes. The tasks demonstrate a deeper understanding of algorithmic design and object-oriented programming principles.

## Objectives
- Implement recursive solutions to complex problems.
- Utilize polymorphism to define flexible and reusable class hierarchies.
- Solve pathfinding problems in mazes and explore algorithms for string manipulation.

## Features
1. **Polymorphism with Events**:
   - Creates a base `Event` class with derived classes like `BasketballGame`, `HockeyGame`, and `Concert`.
   - Implements pure and non-pure virtual functions to define class-specific behavior.

2. **Recursive Algorithms**:
   - Implements recursive functions for array manipulation and predicate-based searches:
     - Count elements in arrays.
     - Find subsequences in arrays.
     - Rearrange and order string arrays.

3. **Maze Solver**:
   - Implements recursive backtracking to solve mazes, marking visited cells and returning success if the destination is reached.

## File Descriptions
1. **`event.cpp`**:
   - Defines a polymorphic class hierarchy for events.
   - Demonstrates clean-up and specific needs for each event type with dynamic allocation and virtual destructors.

2. **`linear.cpp`**:
   - Implements recursive functions for searching, counting, and manipulating arrays of strings.

3. **`maze.cpp`**:
   - Implements recursive backtracking to find a path in a maze.
   - Marks visited cells to avoid infinite loops.

4. **`tree.cpp`**:
   - Implements advanced algorithms for:
     - Counting subsequences in arrays.
     - Separating arrays based on a pivot element.
     - Recursively ordering arrays.
