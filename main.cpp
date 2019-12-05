#include "main.h"

int main() {
    gameGenerate();
    return 0;
}

void gameGenerate() {
    int board[10][10]{};
    char char_board[10][10]{};
    placeShip(board, 4);
    placeShip(board, 3);
    placeShip(board, 3);
    placeShip(board, 2);
    placeShip(board, 2);
    placeShip(board, 2);
    placeShip(board, 1);
    placeShip(board, 1);
    placeShip(board, 1);
    placeShip(board, 1);
    play(board, char_board);
}

void placeShip(int board[10][10], int size) {
    random_device device{};
    mt19937 generator(device());
    uniform_int_distribution<int> board_distribution(0, 9);
    uniform_int_distribution<int> direction_distribution(1, 4);

    int random_x = board_distribution(generator);
    int random_y = board_distribution(generator);
    bool occupied_space = false;
    bool wrong_direction = false;
    int direction{};

    //determining ship direction
    do {
        random_x = board_distribution(generator);
        random_y = board_distribution(generator);
        direction = direction_distribution(generator);
        occupied_space = false;
        wrong_direction = false;
        switch (direction) {
            case 1: //up
                if (random_y < size - 1) wrong_direction = true;
                for (int i = 0; i < size; i++) {
                    if (board[random_x][random_y - i] != 0) {
                        occupied_space = true;
                        break;
                    }
                }
                break;
            case 2: //right
                if (random_x > 10 - size) wrong_direction = true;
                for (int i = 0; i < size; i++) {
                    if (board[random_x + i][random_y] != 0) {
                        occupied_space = true;
                        break;
                    }
                }
                break;
            case 3: //down
                if (random_y > 10 - size) wrong_direction = true;
                for (int i = 0; i < size; i++) {
                    if (board[random_x][random_y + i] != 0) {
                        occupied_space = true;
                        break;
                    }
                }
                break;
            case 4: //left
                if (random_x < size - 1) wrong_direction = true;
                for (int i = 0; i < size; i++) {
                    if (board[random_x - i][random_y] != 0) {
                        occupied_space = true;
                        break;
                    }
                }
                break;
            default:
                break;
        }
    } while (wrong_direction || occupied_space);

    //setting  up the rest of the ship
    switch (direction) {
        case 1: //up
            for (int i = 0; i < size; i++) {
                board[random_x][random_y - i] = size;
            }
            break;
        case 2: //right
            for (int i = 0; i < size; i++) {
                board[random_x + i][random_y] = size;
            }
            break;
        case 3: //down
            for (int i = 0; i < size; i++) {
                board[random_x][random_y + i] = size;
            }
            break;
        case 4: //left
            for (int i = 0; i < size; i++) {
                board[random_x - i][random_y] = size;
            }
            break;
        default:
            break;
    }

    // sorround the ship with -1
    for (int j = 0; j < 10; j++) {
        for (int i = 0; i < 10; i++) {
            if (board[i][j] > 0) {
                if (board[i - 1][j - 1] == 0 && j > 0 && i > 0) board[i - 1][j - 1] = -1;
                if (board[i][j - 1] == 0 && j > 0) board[i][j - 1] = -1;
                if (board[i + 1][j - 1] == 0 && j > 0 && i < 9) board[i + 1][j - 1] = -1;
                if (board[i - 1][j] == 0 && i > 0) board[i - 1][j] = -1;
                if (board[i + 1][j] == 0 && i < 9) board[i + 1][j] = -1;
                if (board[i - 1][j + 1] == 0 && j < 9 && i > 0) board[i - 1][j + 1] = -1;
                if (board[i][j + 1] == 0 && j < 9) board[i][j + 1] = -1;
                if (board[i + 1][j + 1] == 0 && j < 9 && i < 9) board[i + 1][j + 1] = -1;
            }
        }
    }
}

void printBoard(int board[10][10]) {
    cout << "   ";
    for (int k = 0; k < 10; k++) {
        cout.width(4);
        cout << k;
    }
    cout << "\n   ";
    for (int k = 0; k < 10; k++) {
        cout.width(4);
        cout << "-";
    }
    cout << "\n";

    for (int j = 0; j < 10; j++) {
        cout << " " << j << "|";
        for (int i = 0; i < 10; i++) {
            cout.width(4);
            if (board[i][j] == 0 || board[i][j] == -1) cout << " ";
            else cout << board[i][j];
        }
        cout << endl;
    }
}

void printCharBoard(char char_board[10][10]) {
    cout << "   ";
    for (int k = 0; k < 10; k++) {
        cout.width(4);
        cout << k;
    }
    cout << "\n   ";
    for (int k = 0; k < 10; k++) {
        cout.width(4);
        cout << "-";
    }
    cout << "\n";

    for (int j = 0; j < 10; j++) {
        cout << " " << j << "|";
        for (int i = 0; i < 10; i++) {
            cout.width(4);
            cout << char_board[i][j];
        }
        cout << endl;
    }
}

void play(int board[10][10], char char_board[10][10]) {
    int x{};
    int y{};
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            char_board[i][j] = '.';
        }
    }
    printBoard(board);
    cout << endl;
    printCharBoard(char_board);
    while (x != 100) {
        cout << "Enter X: ";
        cin >> x;
        cout << "Enter Y: ";
        cin >> y;
        if (board[x][y] > 0){
            cout << "You hit a ship!" << endl;
            char_board[x][y] = 'X';

        }
        else {
            cout << "You missed." << endl;
            char_board[x][y] = '0';
        }
        printCharBoard(char_board);
    }
}