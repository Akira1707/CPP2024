#include "Gems.h"
#include <iostream>
#include <vector>

using namespace std;


Gems::Gems(int n, const vector<char>& colors, int moves) : gameBoard(n, colors), movesLeft(moves) 
{
}

void Gems::playGame() {
    while (movesLeft > 0) {
        printStatus();
        int x1, y1, x2, y2;
        bool Matched;
        cout << "Enter the coordinates x1 y1 x2 y2: ";
        cin >> x1 >> y1 >> x2 >> y2;
        if (gameBoard.swapColor(x1, y1, x2, y2)) {
            Matched = gameBoard.FindAndRemoveMatches(true);
            while (Matched) {
                Matched = gameBoard.FindAndRemoveMatches(false);
            }
            if (gameBoard.checkWin()) {
                gameBoard.printBoard();
                cout << "You win!" << endl;
                return;
            }
        }
        else {
            cout << "Error: Can't change these buttons" << endl;
        }
        movesLeft--;
    }
    gameBoard.printBoard();
    cout << "Game over!" << endl;
}

void Gems::printStatus() {
    cout << "Moves left: " << movesLeft << ". Current board : " << endl;
    gameBoard.printBoard();
}