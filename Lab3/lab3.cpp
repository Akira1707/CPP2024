#include <iostream>
#include "Gems.h"

int main() {
    std::vector<char> colors = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
    Gems game(8, colors, 10);
    game.playGame();
    return 0;
}