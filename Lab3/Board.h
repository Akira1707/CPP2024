#pragma once
#include <vector>
#include <string>

class Board {
private:
    int n;
    std::vector<std::vector<char>> board;
    std::vector<char> colors;

public:
    Board(int n, const std::vector<char>& colors);
    void initBoard();
    void printBoard();
    bool swapColor(int x1, int y1, int x2, int y2);
    void bombBonus(int x, int y);
    void recolorBonus(int x, int y);
    void applyBonus(int x, int y);
    bool FindAndRemoveMatches(bool bonus);
    void CollapseBoard();
    bool checkWin();
};
