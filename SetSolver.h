#ifndef SetSolver_h
#define SetSolver_h

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <array>
#include <cassert>
#include <algorithm>

using std::vector;
using std::string;
#include "SetSolverSquareSet.h"

class SetSolver {
private:
    static constexpr int N = 9;
    vector<vector<SetSolverSquareSet>> board; // board[0] rows

    // safe accessor
    inline int cell(size_t r, size_t c) const {
        return board[0][r].set[c];
    }

public:
    SetSolver() {
        board.clear();
    }
    // '0' is 0, '*' is 99 (means empty), '-' means next char is negative digit, digits '1' to '9' are normal
    void PopulateBoard(const vector<string> &skeletonBoard) {
        board.clear();
        vector<SetSolverSquareSet> rows;
        rows.reserve(N);

        for (size_t i = 0; i < skeletonBoard.size() && i < (size_t)N; ++i) {
            vector<int> conversion;
            conversion.reserve(N);
            const string &currentString = skeletonBoard[i];
            bool negativeIncoming = false;
            for (size_t j = 0; j < currentString.size() && conversion.size() < (size_t)N; ++j) {
                char ch = currentString[j];
                if (ch == '0') conversion.push_back(0);
                else if (ch == '*') conversion.push_back(99);
                else if (ch == '-') { negativeIncoming = true; continue; }
                else if (ch >= '0' && ch <= '9') {
                    int val = ch - '0';
                    if (negativeIncoming) { conversion.push_back(-val); negativeIncoming = false; }
                    else conversion.push_back(val);
                }
            }
            // pad short rows with empties
            while (conversion.size() < (size_t)N) conversion.push_back(99);
            SetSolverSquareSet tempRow;
            tempRow.set = conversion;
            rows.push_back(tempRow);
        }
        // pad missing rows
        while (rows.size() < (size_t)N) {
            SetSolverSquareSet t; t.set = vector<int>(N, 99);
            rows.push_back(t);
        }
        board.clear();
        board.push_back(rows);
    }

     int ReturnValue(size_t row, size_t col) const {
        return cell(row, col);
    }

private:
    // find if number exists in list 
    bool findNumber(const vector<int>& lst, int number) const {
        for (int x : lst) if (x == number) return true;
        return false;
    }

    // bubble sort 
    void bsort(vector<int>& lst) const {
        int size = (int)lst.size();
        for (int i = 0; i < size - 1; ++i) {
            for (int j = 0; j < size - i - 1; ++j) {
                if (lst[j] > lst[j + 1]) {
                    int temp = lst[j];
                    lst[j] = lst[j + 1];
                    lst[j + 1] = temp;
                }
            }
        }
    }

    // build row and column values arrays for a given row/col 4 validation
    void buildRowAndColValues(int row, int col, vector<int>& rowValues, vector<int>& colValues) const {
        rowValues.clear(); rowValues.reserve(N);
        colValues.clear(); colValues.reserve(N);
        for (int i = 0; i < N; ++i) {
            rowValues.push_back(ReturnValue(row, i));
            colValues.push_back(ReturnValue(i, col));
        }
    }

    bool isValidNumber(int guess, int row, int col) const {
        // cannot place on non-empty
        if (board[0][row].set[col] != 99) return false;

        vector<int> rowValues; rowValues.reserve(N);
        vector<int> columnValues; columnValues.reserve(N);
        buildRowAndColValues(row, col, rowValues, columnValues);

        // if guess or -guess appears in row/col, invalid
        if (findNumber(rowValues, guess) || findNumber(rowValues, -guess) || findNumber(columnValues, guess) || findNumber(columnValues, -guess)) {
            return false;
        }

        // collect positive contiguous compartment vals in row around col
        vector<int> rowCompartmentValues;
        if (col > 0) {
            for (int back = col - 1; back >= 0; --back) {
                if (rowValues[back] > 0) rowCompartmentValues.push_back(rowValues[back]);
                else break;
            }
        }
        if (col < N - 1) {
            for (int next = col + 1; next < N; ++next) {
                if (rowValues[next] > 0) rowCompartmentValues.push_back(rowValues[next]);
                else break;
            }
        }

        // column compartment values
        vector<int> columnCompartmentValues;
        if (row > 0) {
            for (int back = row - 1; back >= 0; --back) {
                if (columnValues[back] > 0) columnCompartmentValues.push_back(columnValues[back]);
                else break;
            }
        }
        if (row < N - 1) {
            for (int next = row + 1; next < N; ++next) {
                if (columnValues[next] > 0) columnCompartmentValues.push_back(columnValues[next]);
                else break;
            }
        }

        vector<int> knownNumbers; knownNumbers.reserve(rowCompartmentValues.size());
        vector<int> knownNumbers1; knownNumbers1.reserve(columnCompartmentValues.size());

        int rowCompSize = (int)rowCompartmentValues.size();
        int colCompSize = (int)columnCompartmentValues.size();

        for (int i = 0; i < rowCompSize; ++i) {
            if (rowCompartmentValues[i] != 99) knownNumbers.push_back(rowCompartmentValues[i]);
        }
        for (int i = 0; i < colCompSize; ++i) {
            if (columnCompartmentValues[i] != 99) knownNumbers1.push_back(columnCompartmentValues[i]);
        }

        int max = 0, max1 = 0;
        int min, min1;

        if (!knownNumbers.empty()) {
            min = knownNumbers[0];
            for (size_t i = 0; i < knownNumbers.size(); ++i) {
                if (knownNumbers[i] > max) max = knownNumbers[i];
                if (knownNumbers[i] < min) min = knownNumbers[i];
            }
            // prune by range 
            if (guess < (max - (rowCompSize + 1))) return false;
            if (guess > (min + (rowCompSize + 1))) return false;
        }

        if (!knownNumbers1.empty()) {
            min1 = knownNumbers1[0];
            for (size_t i = 0; i < knownNumbers1.size(); ++i) {
                if (knownNumbers1[i] > max1) max1 = knownNumbers1[i];
                if (knownNumbers1[i] < min1) min1 = knownNumbers1[i];
            }
            if (guess < (max1 - (colCompSize + 1))) return false;
            if (guess > (min1 + (colCompSize + 1))) return false;
        }

        // full = all nearby compartment positive cells are known so none are 99
        bool full = false;
        if (rowCompSize > 0) {
            full = true;
            for (int i = 0; i < rowCompSize; ++i) {
                if (rowCompartmentValues[i] == 99) { full = false; break; }
            }
        }

        bool sequential = true;
        if (full) {
            vector<int> vec; vec.reserve(rowCompSize + 1);
            vec.push_back(guess);
            for (int x : rowCompartmentValues) vec.push_back(x);
            bsort(vec);
            if (vec.size() > 1) {
                for (size_t i = 0; i < vec.size() - 1; ++i) {
                    if (vec[i] + 1 != vec[i + 1]) { sequential = false; break; }
                }
            }
            if (!sequential) return false;
        }

        // column compartments
        full = false;
        if (colCompSize > 0) {
            full = true;
            for (int i = 0; i < colCompSize; ++i) {
                if (columnCompartmentValues[i] == 99) { full = false; break; }
            }
        }
        if (full) {
            vector<int> vec2; vec2.reserve(colCompSize + 1);
            vec2.push_back(guess);
            for (int x : columnCompartmentValues) vec2.push_back(x);
            bsort(vec2);
            if (vec2.size() > 1) {
                for (size_t i = 0; i < vec2.size() - 1; ++i) {
                    if (vec2[i] + 1 != vec2[i + 1]) { sequential = false; break; }
                }
            }
            if (!sequential) return false;
        }

        return true;
    }

    // make list of legal values for (row,col) 
    vector<int> legalValuesAt(int row, int col) const {
        vector<int> out;
        if (board[0][row].set[col] != 99) return out; // not empty
        for (int guess = 1; guess <= 9; ++guess) {
            if (isValidNumber(guess, row, col)) out.push_back(guess);
        }
        return out;
    }

    // find empty cell with minimum remaining legal values if none found, return false
    bool findMRVCell(int &outR, int &outC, vector<int> &outCandidates) const {
        int bestCount = 100;
        bool found = false;
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                if (board[0][r].set[c] == 99) {
                    vector<int> cand = legalValuesAt(r, c);
                    int cnt = (int)cand.size();
                    if (cnt == 0) return false; // dead end
                    if (cnt < bestCount) {
                        bestCount = cnt;
                        outR = r; outC = c;
                        outCandidates = std::move(cand);
                        found = true;
                        if (bestCount == 1) return true;
                    }
                }
            }
        }
        return found;
    }

    // recursive backtracking using mrv
    bool SolveHelper() {
        int row = -1, col = -1;
        vector<int> candidates;
        if (!findMRVCell(row, col, candidates)) {
            // either solved so no empties or dead end so found empty with 0 candidates
            // check for any remaining empty
            for (int r = 0; r < N; ++r) for (int c = 0; c < N; ++c)
                if (board[0][r].set[c] == 99) return false; // dead end
            return true; // solveddd
        }

        // try candidates in natural order 
        for (int val : candidates) {
            board[0][row].set[col] = val;
            if (SolveHelper()) return true;
            // revert
            board[0][row].set[col] = 99;
        }
        return false;
    }

public:
    // wrapper
    bool Solve() {
        return SolveHelper();
    }

    // for debug 
    void printBoard() const {
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                int v = board[0][r].set[c];
                if (v == 99) std::cout << "* ";
                else std::cout << v << ' ';
            }
            std::cout << '\n';
        }
    }
};

#endif /* SetSolver_h */
