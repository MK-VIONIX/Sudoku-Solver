#include "sudoku.h"
#include <iostream>
#include <chrono>
using namespace std;

int main() {
    Sudoku game;
    string difficulty;
    cout << "Choose difficulty (easy/normal/hard): ";
    cin >> difficulty;

    game.generate(difficulty);
    auto start = chrono::steady_clock::now();

    while (!game.isComplete()) {
        game.printBoard();
        cout << "Enter row(0-8) col(0-8) num(1-9) or -1 -1 0 for hint: ";
        int r, c, n;
        cin >> r >> c >> n;

        if (r == -1 && c == -1 && n == 0) {
            int hr, hc;
            cout << "Enter row and col for hint: ";
            cin >> hr >> hc;
            if (hr >= 0 && hr < 9 && hc >= 0 && hc < 9) {
                if (game.isEmpty(hr, hc)) {
                    cout << "Hint at [" << hr << "," << hc << "] = " << game.hint(hr, hc) << "\n";
                } else {
                    cout << "Cell is already filled!\n";
                }
            } else {
                cout << "Invalid row or column!\n";
            }
            continue;
        }

        if (r >= 0 && r <= 8 && c >= 0 && c <= 8 && n >= 1 && n <= 9) {
            if (!game.isEmpty(r, c)) {
                cout << "Cell already filled, choose another.\n";
                continue;
            }
            int correct = game.hint(r, c);
            if (correct == n) {
                game.updateCell(r, c, n);
                cout << "Correct move!\n";
            } else {
                cout << "Incorrect move, try again.\n";
            }
        } else {
            cout << "Invalid input, try again.\n";
        }
    }

    auto end = chrono::steady_clock::now();
    auto elapsed = chrono::duration_cast<chrono::seconds>(end - start).count();
    game.printBoard();
    cout << "Congratulations! You solved the puzzle in " << elapsed << " seconds.\n";

    return 0;
}