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
        IntPair first;
        first.x = x;
        first.y = y;
        pieces.push_front(first);
        first.x--;
        pieces.push_back(first);
        first.x--;
        pieces.push_back(first);
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

    void move() {
        for (list<IntPair>::iterator it = pieces.begin(); it != pieces.end(); ++it) {
            board[it->y][it->x] = ' ';
        }
        pieces.pop_back();
        IntPair next;
        next.x = pieces.begin()->x;
        next.y = pieces.begin()->y;
        switch (currentDirection) {
        case UP:
            next.y--;
            pieces.push_front(next);
            break;
        case DOWN:
            next.y++;
            pieces.push_front(next);
            break;
        case RIGHT:
            next.x++;
            pieces.push_front(next);
            break;
        case LEFT:
            next.x--;
            pieces.push_front(next);
            break;
        }
        placeOnBoard();
    }

    void setDirection(Direction dir) {
        currentDirection = dir;
    }

};

Player player(5, 5);

int _tmain(int argc, _TCHAR* argv[]) {
    /* Init */
    srand(time(NULL));
    initscr();
    system("mode 32,36");   //Set mode to ensure window does not exceed buffer size
    SMALL_RECT WinRect = { 0, 0, 31, 40 };   //New dimensions for window in 8x12 pixel chars
    SMALL_RECT* WinSize = &WinRect;
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, WinSize);   //Set new size for window

    initBoard();
    player.placeOnBoard();
    clear();
    system("cls");
    refresh();
    while (gameRunning) {
        gameLoop();
        display();
        refresh();
        //gameRunning = false;
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
    if (GetAsyncKeyState(VK_RIGHT)) {
        player.setDirection(RIGHT);
    }
    if (GetAsyncKeyState(VK_LEFT)) {
        player.setDirection(LEFT);
    }
    if (GetAsyncKeyState(VK_DOWN)) {
        player.setDirection(DOWN);
    }
    if (GetAsyncKeyState(VK_UP)) {
        player.setDirection(UP);
    }
    player.move();
    Sleep(50);
}
