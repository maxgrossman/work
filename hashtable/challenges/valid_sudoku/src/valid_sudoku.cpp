#include <map>
#include <cassert>
#include <iostream>
#include <string>
//https://leetcode.com/problems/valid-sudoku/


bool validSudoku(char board[9][9]) {
    // keys are...
    // r0->r8; these are for all rows.
    // c0->c8; these are for all columns.
    // 00->22; these are for all squares.
    std::map<std::string, std::map<int, bool>> validParts;
    for (int row = 0; row < 9; ++row) {
        std::string rowKey = "r" + std::to_string(row);
        if (!validParts.count(rowKey))
            validParts[rowKey] = std::map<int,bool>();

        std::map<int,bool> validRow = validParts[rowKey];

        std::string squareKey = std::to_string(row / 3);

        for (int col = 0; col < 9; ++col) {
            char val = board[row][col];

            if (val == '.')
                continue;

            if (validRow.count(val)) {
                return false;
            }

            validRow[val] = true;

            std::string colKey = "c" + std::to_string(col);

            if (row == 0 && !validParts.count(colKey))
                validParts[colKey] = std::map<int,bool>();

            if (validParts[colKey].count(val)) {
                return false;
            }

            validParts[colKey][val] = true;

            squareKey += std::to_string(col / 3);
            // compute, then check to square, see square is valid.
            if (col % 3 == 0 && !validParts.count(squareKey))
                validParts[squareKey] = std::map<int,bool>();

            if (validParts[squareKey].count(val)) {
                return false;
            }

            validParts[squareKey][val] = true;
        }
    }

    return true;
}

int main () {
    char firstBoard[9][9] = {
         {'5','3','.','.','7','.','.','.','.'}
        ,{'6','.','.','1','9','5','.','.','.'}
        ,{'.','9','8','.','.','.','.','6','.'}
        ,{'8','.','.','.','6','.','.','.','3'}
        ,{'4','.','.','8','.','3','.','.','1'}
        ,{'7','.','.','.','2','.','.','.','6'}
        ,{'.','6','.','.','.','.','2','8','.'}
        ,{'.','.','.','4','1','9','.','.','5'}
        ,{'.','.','.','.','8','.','.','7','9'}
    };

    char secondBoard[9][9] = {
         {'8','3','.','.','7','.','.','.','.'}
        ,{'6','.','.','1','9','5','.','.','.'}
        ,{'.','9','8','.','.','.','.','6','.'}
        ,{'8','.','.','.','6','.','.','.','3'}
        ,{'4','.','.','8','.','3','.','.','1'}
        ,{'7','.','.','.','2','.','.','.','6'}
        ,{'.','6','.','.','.','.','2','8','.'}
        ,{'.','.','.','4','1','9','.','.','5'}
        ,{'.','.','.','.','8','.','.','7','9'}
    };

    assert(validSudoku(firstBoard) == true);
    std::cout << "The first board is valid" << std::endl;
    assert(validSudoku(secondBoard) == false);
    std::cout << "The second board is invalid" << std::endl;
    return 0;
}
