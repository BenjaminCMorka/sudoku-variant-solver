# Sudoku Variant Solver

A fast C++ solver for a custom 9×9 Sudoku-like puzzle with additional rules:

- Numbers may be positive or negative.
- Compartments of contiguous positive numbers must follow **range** and **sequential** constraints.
- Standard Sudoku row/column uniqueness applies to absolute values.

The solver uses **MRV (Minimum Remaining Values)** heuristic and **search space pruning** for speed.

---

## Features

- **Board parsing** from a compact ASCII format:
  - `0` → literal zero
  - `*` → empty cell
  - `-` before a digit → negative number
  - Digits `1`–`9` → positive number
- **Constraint propagation** before guessing:
  - Row/column uniqueness for absolute values.
  - Range and sequential checks within compartments.
- **MRV heuristic** to choose the most constrained cell first.
- **Recursive backtracking** with early failure detection.

---

## Example Input

The board is passed as a `vector<string>` in `NumberSetSolveTest.cpp`:

```cpp
vector<string> skeletonBoard{
    "00**0-31*0",
    "*****0**0",
    "7*003*-5**",
    "**05**7**",
    "*0**0*6-9*",
    "4***650**",
    "*2-8**00**",
    "-23*0*****",
    "043-608*0-1"
};
---

## Tech Stack
