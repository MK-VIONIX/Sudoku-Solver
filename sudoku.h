#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>
#include <string>
using namespace std;

class Sudoku {
private:
    int board[9][9];
    int solution[9][9];
    bool isSafe(int b[9][9], int row, int col, int num);
    bool solveBoard(int b[9][9]);
public:
    Sudoku();
    void generate(string difficulty);
    bool solve();
    void printBoard();
    bool isComplete();
    int hint(int row, int col);
    void updateCell(int row, int col, int num);
    bool isEmpty(int row, int col);
};

#endif