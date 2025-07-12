#ifndef SetSolver_h
#define SetSolver_h

#include <string>
#include <iostream>
#include <memory>
#include "SetSolverSquareSet.h"

using std::vector;
using std::string;
//do not add additional libraries

class SetSolver
{
private:
    int boardSize = 9;
    vector<vector<SetSolverSquareSet>>board;
    
public:
SetSolver()
{
    
}
void PopulateBoard(vector<string>skeletonBoard)
{

    vector<SetSolverSquareSet> rows;
    bool negativeIncoming = false;
    for(int i = 0; i < skeletonBoard.size(); i++){
        vector<int>conversion;
        string currentString = skeletonBoard[i];
        for(int j = 0; j < currentString.size(); j++){
            if(currentString[j] == '0'){
                conversion.push_back(0);
            }
            else if(currentString[j] == '*'){
                conversion.push_back(99);
            }
            else if(currentString[j] == '-'){
                negativeIncoming = true;
                continue;
            }
            else if(negativeIncoming){
                string character;
                character.push_back(currentString[j]);
                conversion.push_back(-(std::stoi(character)));
                negativeIncoming = false;
            }
            else{
                string character2;
                character2.push_back(currentString[j]);
                conversion.push_back(std::stoi(character2));
            }
        }
        
        SetSolverSquareSet tempRow;
        tempRow.set = conversion;
        rows.push_back(tempRow);
    }
    board.push_back(rows);
}

int ReturnValue(size_t row, size_t col)
{
    
    
    SetSolverSquareSet values = board[0][row];

    int cell = values.set[col];

    // return the right value
    return cell;  // This line was added temporarily 
}

bool findNumber(const vector<int>&lst, int number){
    for(int i = 0; i < lst.size(); i++){
        if(lst[i] == number){
            return true;
        }
    }
    return false;
}


void bsort(vector<int>& lst){
    int size = lst.size();
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

bool isValidNumber(vector<vector<SetSolverSquareSet> >&b, int guess, int& row, int& col){

    vector<int> rowValues;
    rowValues.reserve(9);
    vector<int> columnValues;
    columnValues.reserve(9);

    // no previous cells in row if on first cell in row
    for (int i = 0; i < 9; i++) {
        rowValues.push_back(ReturnValue(row, i));
        columnValues.push_back(ReturnValue(i, col));
    }

    if (findNumber(rowValues, guess) || findNumber(rowValues, -guess) || findNumber(columnValues, guess) || findNumber(columnValues, -guess)) {
        return false;
    }

    vector<int>rowCompartmentValues;

    if(col > 0){
        // checking previous cells in the row
        for(int back = col-1; back >= 0; back--){
            if(rowValues[back] > 0){
                rowCompartmentValues.push_back(rowValues[back]);
            }
            else{
                break;
            }
        }
    }
        // checking next cells in the row
    if(col < 8){
        for(int next = col+1; next < 9; next++){
            if(rowValues[next] > 0){
                rowCompartmentValues.push_back(rowValues[next]);
            }
            else{
                break;
            }
        }
    }



    vector<int> columnCompartmentValues;
    if(row > 0){
        // checking previous cells in the column
        for(int back = row - 1; back >= 0; back--){
            if(columnValues[back] > 0){
                columnCompartmentValues.push_back(columnValues[back]);
            }
            else{
                break;
            }
        }
    }
        // checking next cells in the column
    if(row < 8){
        for(int next = row + 1; next < 9; next++){
            if(columnValues[next] > 0){
                columnCompartmentValues.push_back(columnValues[next]);
            }
            else{
                break;
            }
        }
    }
    vector<int>knownNumbers;
    vector<int>knownNumbers1;

    int rowCompSize = rowCompartmentValues.size();
    int colCompSize = columnCompartmentValues.size();
    for(int i = 0; i < rowCompSize; i++){
        if(rowCompartmentValues[i] != 99){
            knownNumbers.push_back(rowCompartmentValues[i]);
        }
    }

    for(int i = 0; i < colCompSize; i++){
        if(columnCompartmentValues[i] != 99){
            knownNumbers1.push_back(columnCompartmentValues[i]);
        }
    }

    int max = 0;
    int max1 = 0;

    int min;
    int min1;
    if(knownNumbers.size() > 0){
        min = knownNumbers[0];
        for(int i = 0; i < knownNumbers.size(); i++){
            if(knownNumbers[i] > max){
                max = knownNumbers[i];
            }

            if(knownNumbers[i] < min){
                min = knownNumbers[i];
            }
        }
    }

    if(knownNumbers.size() > 0){
        if(guess < (max - (rowCompSize+1))){
            return false;
        }

        if(guess > (min + (rowCompSize+1))){
            return false;
        }
    }

    if(knownNumbers1.size() > 0){
        min1 = knownNumbers1[0];
        for(int i = 0; i < knownNumbers1.size(); i++){
            if(knownNumbers1[i] > max1){
                max1 = knownNumbers1[i];
            }

            if(knownNumbers1[i] < min1){
                min1 = knownNumbers1[i];
            }
        }
    }

    if(knownNumbers1.size() > 0){
        if(guess < (max1 - (colCompSize+1))){
            return false;
        }

        if(guess > (min1 + (colCompSize+1))){
            return false;
        }
    }
    

    bool full;
    if(rowCompSize > 0){
        full = true;
        for(int i = 0; i < rowCompSize; ++i){
            if(rowCompartmentValues[i] == 99){
                full = false;
            }
        }
    }
    else{
        full = false;
    }

    bool sequential = true;
    if(full){
        vector<int> vec;
        
        vec.push_back(guess);
        for(int i = 0; i < rowCompSize; i++){
            vec.push_back(rowCompartmentValues[i]);
        }
        bsort(vec);
        if(vec.size() > 1){
            for (size_t i = 0; i < vec.size() - 1; ++i) {
                if (vec[i] + 1 != vec[i + 1]) {
                    sequential = false;  
                }
            }
        }

        if(!sequential){
            return false;
        }
        full = true;
    }
    // for column compartments

    if(colCompSize > 0){
        full = true;
        for(int i = 0; i < colCompSize; ++i){
            if(columnCompartmentValues[i] == 99){
                full = false;
            }
        }
    }
    else{
        full = false;
    }

    if(full){
        vector<int> vec2;
        vec2.push_back(guess);
        for(int i = 0; i < colCompSize; i++){
            vec2.push_back(columnCompartmentValues[i]);
        }
        bsort(vec2);
        if(vec2.size() > 1){
            for (size_t i = 0; i < vec2.size() - 1; ++i) {
                if (vec2[i] + 1 != vec2[i + 1]) {
                    sequential = false; 
                }
            }
        }

        if(!sequential){
            return false;
        }
    }


    return true;
}

bool findEmpty(vector<vector<SetSolverSquareSet> >&b, int& row, int& col){
    for(row = 0; row < 9; row++){
        for(col = 0; col < 9; col ++){
            if(b[0][row].set[col] == 99){
                return true;
            }
        }
    }
    return false;
}

bool SolveHelper(vector<vector<SetSolverSquareSet> >&b)
{
  
    int row;
    int col;

    if(!findEmpty(b, row, col)){
        return true;
    }

    for(int guess = 1; guess <= 9; guess++){
        if(isValidNumber(b, guess, row, col)){
            b[0][row].set[col] = guess;
            
            if(SolveHelper(b)){
                return true;
            }
        }
        b[0][row].set[col] = 99;
    }

    return false;
}

void Solve()
{
    
    SolveHelper(board);

}



    
};
#endif /* SetSolver_h */
