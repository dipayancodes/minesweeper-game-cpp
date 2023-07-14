#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

const int SIZE = 10;
const int MINES = 15;

void initializeBoard(vector<vector<char>>& board, vector<vector<bool>>& revealed) {
    for (int i = 0; i < SIZE; ++i) {
        board.push_back(vector<char>(SIZE, ' '));
        revealed.push_back(vector<bool>(SIZE, false));
    }
}

void placeMines(vector<vector<char>>& board) {
    int count = 0;
    while (count < MINES) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        if (board[x][y] != '*') {
            board[x][y] = '*';
            ++count;
        }
    }
}

bool isValid(int x, int y) {
    return (x >= 0 && x < SIZE && y >= 0 && y < SIZE);
}

int countAdjacentMines(const vector<vector<char>>& board, int x, int y) {
    int count = 0;
    for (int i = x - 1; i <= x + 1; ++i) {
        for (int j = y - 1; j <= y + 1; ++j) {
            if (isValid(i, j) && board[i][j] == '*') {
                ++count;
            }
        }
    }
    return count;
}

void revealEmptyCells(vector<vector<char>>& board, vector<vector<bool>>& revealed, int x, int y) {
    if (!isValid(x, y) || revealed[x][y]) {
        return;
    }
    revealed[x][y] = true;
    if (board[x][y] == ' ') {
        for (int i = x - 1; i <= x + 1; ++i) {
            for (int j = y - 1; j <= y + 1; ++j) {
                revealEmptyCells(board, revealed, i, j);
            }
        }
    }
}

void printBoard(const vector<vector<char>>& board, const vector<vector<bool>>& revealed) {
    cout << "   ";
    for (int i = 0; i < SIZE; ++i) {
        cout << i << " ";
    }
    cout << endl;
    for (int i = 0; i < SIZE; ++i) {
        cout << " " << i << " ";
        for (int j = 0; j < SIZE; ++j) {
            if (revealed[i][j]) {
                cout << board[i][j] << " ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}

void playMinesweeper() {
    vector<vector<char>> board;
    vector<vector<bool>> revealed;
    initializeBoard(board, revealed);
    placeMines(board);

    int totalCells = SIZE * SIZE;
    int uncoveredCells = 0;

    while (uncoveredCells < totalCells - MINES) {
        printBoard(board, revealed);

        int x, y;
        cout << "Enter the row and column (e.g., 2 3): ";
        cin >> x >> y;

        if (!isValid(x, y) || revealed[x][y]) {
            cout << "Invalid move! Try again." << endl;
            continue;
        }

        if (board[x][y] == '*') {
            cout << "Game Over! You stepped on a mine." << endl;
            return;
        }

        revealed[x][y] = true;
        ++uncoveredCells;

        if (board[x][y] == ' ') {
            revealEmptyCells(board, revealed, x, y);
        }
    }

    cout << "Congratulations! You won the game." << endl;
    printBoard(board, revealed);
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    playMinesweeper();
    return 0;
}
