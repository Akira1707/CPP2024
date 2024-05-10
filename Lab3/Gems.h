#pragma once
#include "Board.h"

class Gems {
public:
    Gems(int n, const std::vector<char>& colors, int moves);
    void playGame();
    void printStatus();

private:
    Board gameBoard;
    int movesLeft;
};
