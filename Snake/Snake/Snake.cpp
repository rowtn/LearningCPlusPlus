// Snake.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <string>
#include <curses.h>
#include <Windows.h>
#include <list>

using namespace std;

bool won = false;
bool gameRunning = true;

char board[30][30];

void initBoard(void);
void display(void);
void gameLoop(void);

const char FOOD = char(167);
const char SNAKE_PIECE = char(178);

enum Direction {
    UP, DOWN, LEFT, RIGHT
};

struct IntPair {
    int x, y;
};

class Player {
private:
    int length = 3, x, y;
    int lastPiece[2];
    Direction currentDirection = RIGHT;
    list<IntPair> pieces;
public:
    Player(int i, int j) {
        x = i;
        y = j;
        lastPiece[0] = x;
        lastPiece[1] = y;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    int eat() {
        length++;
    }

    void placeOnBoard() {
        for (list<IntPair>::iterator it = pieces.begin(); it != pieces.end(); ++it) {
            board[it->y][it->x] = SNAKE_PIECE;
        }
    }

    list<IntPair> getAllPieceLocations() {
        return pieces;
    }

};

int _tmain(int argc, _TCHAR* argv[]) {
    /* Init */
    srand(time(NULL));
    initscr();
    system("mode 32,36");   //Set mode to ensure window does not exceed buffer size
    SMALL_RECT WinRect = { 0, 0, 31, 40 };   //New dimensions for window in 8x12 pixel chars
    SMALL_RECT* WinSize = &WinRect;
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, WinSize);   //Set new size for window

    initBoard();
    clear();
    system("cls");
    refresh();
    while (gameRunning) {
        gameLoop();
        display();
        refresh();
        gameRunning = false;
    }
    cin.get();
	return 0;
}

void initBoard() {
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            if (i == 0 || i == 29 || j == 0 || j == 29) board[i][j] = char(219);
        }
    }
    board[10][5] = SNAKE_PIECE;
}

void display() {
    cout << endl;
    for (int i = 0; i < 30; i++) {
        cout << ' ';
        for (int j = 0; j < 30; j++) {
            if (board[i][j] == SNAKE_PIECE) {
                //TODO Colour
            }
            else {
                //TODO
            }
            cout << board[i][j];
        }
        cout << endl;
    }
}

void gameLoop() {
    //stuff
}
