#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Move {
    int row, col;
};

char player = 'x';
char comp = 'o';

void initialTable(char (&arr)[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            arr[i][j] = '_';
        }
    }
}

void printTable(char arr[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << " " << arr[i][j] << " ";
        }
        cout << endl;
    }
}

bool isMoveLeft(char arr[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (arr[i][j] == '_') {
                return true;
            }
        }
    }
    return false;
}

int evaluate(char arr[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2]) {
            if (arr[i][0] == 'x') return 10;
            else if (arr[i][0] == 'o') return -10;
        }
    }

    for (int i = 0; i < 3; i++) {
        if (arr[0][i] == arr[1][i] && arr[1][i] == arr[2][i]) {
            if (arr[0][i] == 'x') return 10;
            else if (arr[0][i] == 'o') return -10;
        }
    }

    if (arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2]) {
        if (arr[0][0] == 'x') return 10;
        else if (arr[0][0] == 'o') return -10;
    }

    if (arr[0][2] == arr[1][1] && arr[1][1] == arr[2][0]) {
        if (arr[0][2] == 'x') return 10;
        else if (arr[0][2] == 'o') return -10;
    }

    return 0;
}

int minimax(char board[3][3], int depth, bool isMax) {
    int score = evaluate(board);

    if (score == 10) return score;
    if (score == -10) return score;
    if (!isMoveLeft(board)) return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = player;
                    best = max(best, minimax(board, depth + 1, false));
                    board[i][j] = '_';
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = comp;
                    best = min(best, minimax(board, depth + 1, true));
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
}

Move findBestMove(char board[3][3]) {
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '_') {
                board[i][j] = player;
                int moveVal = minimax(board, 0, false);
                board[i][j] = '_';

                if (moveVal > bestVal) {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

bool updateValue(char (&arr)[3][3], int num) {
    int row = (num - 1) / 3;
    int col = (num - 1) % 3;
    if (arr[row][col] == '_') {
        arr[row][col] = 'o';
        return true;
    } else {
        cout << "ILLEGAL MOVE" << endl;
        cout << "PLEASE RE-ENTER" << endl;
        return false;
    }
}

int main() {
    char arr[3][3];
    initialTable(arr);
    cout << "Enter your input as an integer representing the corresponding number" << endl;
    cout << "1 2 3" << endl << "4 5 6" << endl << "7 8 9" << endl;
    cout << "You will play as o and I will play as x." << endl;
    cout << "Wanna play first? (y or n)";
    char choice;
    cin >> choice;
    if (choice == 'n') {
        cout << "I will play first then" << endl;
        arr[0][0] = 'x';
        printTable(arr);
    }

    while (isMoveLeft(arr)) {
        int num;
        cout << "Enter where you want to play..." << endl;
        cin >> num;
        bool check = updateValue(arr, num);
        if (!check) continue;

        cout << "Current Board" << endl;
        printTable(arr);

        Move bestMove = findBestMove(arr);
        arr[bestMove.row][bestMove.col] = 'x';
        cout << endl << "OK Then... I will play here" << endl;
        printTable(arr);

        int result = evaluate(arr);
        if (result == 10) {
            cout << "YOU ARE DEFEATED BY A COMPUTER" << endl;
            break;
        }
    }

    if (!isMoveLeft(arr)) {
        cout << "IT'S A DRAW" << endl;
    }

    return 0;
}
