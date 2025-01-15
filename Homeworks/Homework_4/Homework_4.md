# Homework 4: Advanced Data Manipulation and Sorting

This homework explores advanced techniques for manipulating data in STL containers like vectors and lists. It also introduces sorting algorithms, handling dynamic data, and optimizing algorithm performance.

## Objectives
- Learn to traverse and manipulate STL containers like `list` and `vector`.
- Implement custom sorting algorithms and understand time complexity analysis.
- Optimize operations like removing elements and managing large data structures.

## Features
1. **Removing Unwanted Elements**:
   - Implements functions to remove:
     - Restaurants with low ratings from `vector` and `list`.
     - Even numbers from `vector` and `list`.

2. **Recursive and Iterative List Traversal**:
   - Implements traversal functions for nested menu items (`listAll`).
   - Demonstrates efficient navigation through linked data structures.

3. **Sorting**:
   - Compares sorting efficiency using:
     - STL sort (introsort).
     - Custom insertion sort for small datasets.
     - Pointer-based sorting to minimize object copying overhead.

4. **Performance Analysis**:
   - Analyzes time complexity for operations like sorting and traversal.

## File Descriptions
1. **`badlist.cpp` and `badvector.cpp`**:
   - Functions to remove restaurants with low ratings from `list` and `vector`.

2. **`evenlist.cpp` and `evenvector.cpp`**:
   - Functions to remove even numbers from `list` and `vector`.

3. **`list.cpp`**:
   - Implements the `listAll` function for recursive traversal of nested menu items.

4. **`sorts.cpp`**:
   - Demonstrates sorting techniques, including STL sort, insertion sort, and pointer-based sorting.
   - Includes performance comparisons and complexity analysis.

5. **`Sequence.h`**:
   - Provides a generic `Sequence` class with operations for linked list manipulation.

6. **`hw.txt`**:
   - Contains detailed explanations of the homework's challenges, observations, and time complexity analysis.
