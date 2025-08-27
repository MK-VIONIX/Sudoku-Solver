#include "sudoku.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;

Sudoku::Sudoku() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            board[i][j] = 0;
            solution[i][j] = 0;
        }
    }
}

bool Sudoku::isSafe(int b[9][9], int row, int col, int num) {
    for (int i = 0; i < 9; i++) {
        if (b[row][i] == num) return false;
    }
    
    for (int i = 0; i < 9; i++) {
        if (b[i][col] == num) return false;
    }
    
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (b[startRow + i][startCol + j] == num) return false;
        }
    }
    
    return true;
}

bool Sudoku::solveBoard(int b[9][9]) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (b[row][col] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (isSafe(b, row, col, num)) {
                        b[row][col] = num;
                        if (solveBoard(b)) {
                            return true;
                        }
                        b[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

bool Sudoku::solve() {
    int temp[9][9];
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            temp[i][j] = board[i][j];
        }
    }
    
    bool ok = solveBoard(temp);
    if (ok) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                solution[i][j] = temp[i][j];
            }
        }
    }
    return ok;
}

void Sudoku::generate(string difficulty) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            board[i][j] = 0;
        }
    }
    
    srand(time(0));
    
    for (int k = 0; k < 9; k += 3) {
        vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        random_shuffle(nums.begin(), nums.end());
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[k + i][k + j] = nums[i * 3 + j];
            }
        }
    }
    
    solve();
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            board[i][j] = solution[i][j];
        }
    }
    
    int clues = 35;
    if (difficulty == "normal") clues = 32;
    if (difficulty == "hard") clues = 28;
    
    int remove = 81 - clues;
    while (remove > 0) {
        int r = rand() % 9;
        int c = rand() % 9;
        if (board[r][c] != 0) {
            board[r][c] = 0;
            remove--;
        }
    }
}

void Sudoku::printBoard() {
    cout << "   ";
    for (int j = 0; j < 9; j++) {
        cout << j << " ";
        if ((j + 1) % 3 == 0) cout << "  ";
    }
    cout << "\n  -------------------------\n";
    
    for (int i = 0; i < 9; i++) {
        cout << i << " |";
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == 0) cout << ". ";
            else cout << board[i][j] << " ";
            
            if ((j + 1) % 3 == 0) cout << "| ";
        }
        cout << "\n";
        if ((i + 1) % 3 == 0) cout << "  -------------------------\n";
    }
}

bool Sudoku::isComplete() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == 0) return false;
        }
    }
    return true;
}

int Sudoku::hint(int row, int col) {
    if (solution[0][0] == 0) {
        solve();
    }
    return solution[row][col];
}

void Sudoku::updateCell(int row, int col, int num) {
    board[row][col] = num;
}

bool Sudoku::isEmpty(int row, int col) {
    return board[row][col] == 0;
}