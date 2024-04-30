#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

class Board{
private:
    vector<vector<char>> board;
    int n;
    vector<char> colors;
public:
    Board(int n, vector<char> colors) : n(n), colors(colors) {
        board.resize(n, vector<char>(n));
        initBoard();
    }

    void initBoard() {
        srand(time(0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                board[i][j] = colors[rand() % colors.size()];
            }
        }
        bool hasMatches = true;
        while (hasMatches){
            hasMatches = false;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n - 2; j++) {
                    if (board[i][j] == board[i][j + 1] && board[i][j + 1] == board[i][j + 2]) {
                        while (board[i][j + 2] == board[i][j]) {
                            board[i][j + 2] = colors[rand() % colors.size()];
                            hasMatches = true;
                        }
                    }
                    if (board[j][i] == board[j + 1][i] && board[j + 1][i] == board[j + 2][i]) {
                        while (board[j + 2][i] == board[j][i]) {
                            board[j + 2][i] = colors[rand() % colors.size()];
                            hasMatches = true;
                        }
                    }
                }
            }
            for (int i = 0; i < n - 1; i++) {
                for (int j = 0; j < n - 1; j++) {
                    if (board[i][j] == board[i][j + 1] && board[i][j] == board[i + 1][j]) {
                        while (board[i][j] == board[i][j + 1]) {
                            board[i][j] = colors[rand() % colors.size()];
                            hasMatches = true;
                        }
                    }
                    if (board[i][j] == board[i][j + 1] && board[i][j] == board[i + 1][j + 1]) {
                        while (board[i][j] == board[i][j + 1]) {
                            board[i][j + 1] = colors[rand() % colors.size()];
                            hasMatches = true;
                        }
                    }
                    if (board[i][j] == board[i + 1][j] && board[i][j] == board[i + 1][j + 1]) {
                        while (board[i][j] == board[i + 1][j]) {
                            board[i + 1][j] = colors[rand() % colors.size()];
                            hasMatches = true;
                        }
                    }
                    if (board[i][j + 1] == board[i + 1][j] && board[i][j + 1] == board[i + 1][j + 1]) {
                        while (board[i][j + 1] == board[i + 1][j + 1]) {
                            board[i + 1][j + 1] = colors[rand() % colors.size()];
                            hasMatches = true;
                        }
                    }
                }
            }
        }        
    }

    void printBoard() {
        for (const auto& row : board) {
            for (char cell : row) {
                cout << cell << " ";
            }
            cout << endl;
        }
        cout << "---------------------" << endl;
    }

    bool swapColor(int x1, int y1, int x2, int y2) {
        if (board[x1][y1] == ' ' || board[x2][y2] == ' ' || x1 < 0 || x1 >= n || y1 < 0 || y1 >= n || x2 < 0 || x2 >= n || y2 <0 || y2 >= n) {
            return false;
        }
        if ((abs(x1 - x2) == 1 && y1 == y2) || (abs(y1 - y2) == 1 && x1 == x2)) {
            swap(board[x1][y1], board[x2][y2]);
            return true;
        }
        return false;
    }

    void bombBonus(int x, int y) {
        board[x][y] = '*';
        int i = 0;
        while (i < 4){
            int randX = rand() % n;
            int randY = rand() % n;
            if (board[randX][randY] != ' ') {
                board[randX][randY] = '*';
                i++;
            }            
        }
    }

    void recolorBonus(int x, int y) {
        char Color = board[x][y];
        vector<pair<int, int>> cells;

        for (int i = max(0, x - 3); i <= min(n - 1, x + 3); i++) {
            for (int j = max(0, y - 3); j <= min(n - 1, y + 3); j++) {
                if (board[i][j] != ' ' &&  abs(i - x) + abs(j - y) > 1 && abs(i - x) + abs(j - y) <= 3) {
                    cells.push_back({ i,j });
                }
            }
        }
        random_shuffle(cells.begin(), cells.end());
        board[cells[0].first][cells[0].second] = Color;
        board[cells[1].first][cells[1].second] = Color;
    }

    void applyBonus(int x, int y) {
        vector<pair<int, int>> cells;
        for (int i = max(0, x - 3); i <= min(n - 1, x + 3); i++) {
            for (int j = max(0, y - 3); j <= min(n - 1, y + 3); j++) {
                if (board[i][j] != ' ' && abs(i - x) + abs(j - y) > 1 && abs(i - x) + abs(j - y) <= 3) {
                    cells.push_back({ i,j });
                }
            }
        }
        random_shuffle(cells.begin(), cells.end());

        int type = rand() % 100;
        if (type > 50) {
            bombBonus(cells[0].first, cells[0].second); 
            cout << "You receive Bomb Bonus" << endl;
            printBoard();            
            CollapseBoard();
        }
        else {
            recolorBonus(cells[0].first, cells[0].second);
            cout << "You receive Recolor Bonus" << endl;
        }
        printBoard();
        while (FindAndRemoveMatches(false)) {
            int a = 1;
        }
    }

    bool FindAndRemoveMatches(bool bonus) {
        bool hasMatches = false;
        int x, y;
        vector<vector<bool>> marked(n, vector<bool>(n, false));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - 2; j++) {
                if (board[i][j] != ' ' && board[i][j] == board[i][j + 1] && board[i][j + 1] == board[i][j + 2]) {
                    marked[i][j] = marked[i][j + 1] = marked[i][j + 2] = true;
                    hasMatches = true;
                    x = i; y = j + 1;
                }
                if (board[j][i] != ' ' && board[j][i] == board[j + 1][i] && board[j + 1][i] == board[j + 2][i]) {
                    marked[j][i] = marked[j + 1][i] = marked[j + 2][i] = true;
                    hasMatches = true;
                    x = j + 1; y = i;
                }                
            }
        }
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - 1; j++) {
                if (board[i][j] != ' ' && board[i][j] == board[i][j + 1] && board[i][j] == board[i + 1][j]) {
                    marked[i][j] = marked[i][j + 1] = marked[i + 1][j] = true;
                    hasMatches = true;
                    x = i; y = j;
                }
                if (board[i][j] != ' ' && board[i][j] == board[i][j + 1] && board[i][j] == board[i + 1][j + 1]) {
                    marked[i][j] = marked[i][j + 1] = marked[i + 1][j + 1] = true;
                    hasMatches = true;
                    x = i; y = j + 1;
                }
                if (board[i][j] != ' ' && board[i][j] == board[i + 1][j] && board[i][j] == board[i + 1][j + 1]) {
                    marked[i][j] = marked[i + 1][j] = marked[i + 1][j + 1] = true;
                    hasMatches = true;
                    x = i + 1; y = j;
                }
                if (board[i][j + 1] != ' ' && board[i][j + 1] == board[i + 1][j] && board[i][j + 1] == board[i + 1][j + 1]) {
                    marked[i][j + 1] = marked[i + 1][j] = marked[i + 1][j + 1] = true;
                    hasMatches = true;
                    x = i + 1; y = j + 1;
                }
            }
        }
        if (hasMatches) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (marked[i][j]) {
                        board[i][j] = ' ';
                    }
                }
            }
            CollapseBoard();
            printBoard();
            if (bonus) {
                int k = rand() % 100;          
                if (k > 30) {
                    applyBonus(x, y);
                }
            }
        }
        return hasMatches;
    }

    void CollapseBoard() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == '*') board[i][j] = ' ';
            }
        }
        for (int col = 0; col < n; col++) {
            int insertPos = n - 1;
            for (int row = n - 1; row >= 0; row--) {
                if (board[row][col] != ' ') {
                    board[insertPos][col] = board[row][col];
                    if (insertPos != row) {
                        board[row][col] = ' ';
                    }
                    insertPos--;
                }
            }
        }
    }

    bool checkWin() {
        vector<int> count(colors.size(), 0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (size_t k = 0; k < colors.size(); k++) {
                    if (colors[k] == board[i][j]) {
                        count[k]++;
                        break;
                    }
                }
            }
        }
        for (size_t k = 0; k < colors.size(); k++) {
            if (count[k] > 2) {
                return false;
            }
        }
        return true;
    }
};

class Gems {
private:
    Board gameBoard;
    int movesLeft;

public:
    Gems(int n, vector<char> colors, int moves) : gameBoard(n, colors), movesLeft(moves) {}

    void playGame() {
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

    void printStatus() {
        cout << "Moves left: " << movesLeft << ". Current board : " << endl;
        gameBoard.printBoard();
    }
};

int main() {
    vector<char> colors = { 'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    Gems game(8, colors, 10);  
    game.playGame();
    return 0;
}