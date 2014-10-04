// Snake.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <string>
#include <curses.h>
#include <Windows.h>
#include <list>
#include <algorithm>

using namespace std;

bool gameRunning = true;

char board[30][30];

void initBoard(void);
void display(void);
void gameLoop(void);
void spawnFood(void);

const char FOOD = char(167);
const char SNAKE_PIECE = char(178);
const char EMPTY = ' ';

enum Direction {
    UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4
};

struct IntPair {
    int x, y;

    bool operator==(IntPair& a) const {
        return (x == a.x && y == a.y);
    }

};

IntPair foodCoords;

class Player {
private:
    int length = 3, x, y;
    int lastPiece[2];
    Direction currentDirection = RIGHT;
    list<IntPair> pieces;
    bool addPiece = false;
public:
    Player(int i, int j) {
        x = i++;
        y = j++;
        IntPair first;
        first.x = x;
        first.y = y;
        pieces.push_front(first);
        first.x--;
        pieces.push_back(first);
        first.x--;
        pieces.push_back(first);
        x = pieces.front().y;
        y = pieces.front().x;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    void eat() {
        length++;
        //TODO: Add extra piece
        addPiece = true;
        spawnFood();
    }

    void placeOnBoard() {
        for (list<IntPair>::iterator it = pieces.begin(); it != pieces.end(); ++it) {
            board[it->y][it->x] = SNAKE_PIECE;
        }
    }

    list<IntPair> getAllPieces() {
        return pieces;
    }

    void move() {
        IntPair end = pieces.back();
        board[end.y][end.x] = EMPTY;

        if (!addPiece) pieces.pop_back();
        addPiece = false;

        IntPair next = pieces.front();
        switch (currentDirection) {
        case UP:
            next.y--;
            y--;
            break;
        case DOWN:
            next.y++;
            y++;
            break;
        case RIGHT:
            next.x++;
            x++;
            break;
        case LEFT:
            next.x--;
            x--;
            break;
        }
        //cout << "Next piece is: " << board[next.y][next.x] << endl;
        int i = next.x, j = next.y;
        if (i == 0 || i == 29 || j == 0 || j == 29) {
            gameRunning = false;
            return;
        }

        IntPair front = pieces.front();
        if (front.x == foodCoords.y && front.y == foodCoords.x) {
            eat();
        }

        if (board[next.x][next.y] == SNAKE_PIECE) {
            gameRunning = false;
        }

        pieces.push_front(next);
        placeOnBoard();
    }

    void setDirection(Direction dir) {
        currentDirection = dir;
    }

    int getLength() {
        return length;
    }

    Direction getDirection() {
        return currentDirection;
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
    spawnFood();
    while (gameRunning) {
        gameLoop();
        display();
        refresh();
        //gameRunning = false;
    }
    clear();
    system("cls");
    refresh();
    cout << "Your final score was " << player.getLength() * 10 << "!" << endl;
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
    /* Debug */
    //cout << "Player coords:" << player.getY() << ", " << player.getX() << "     " << endl;
    //cout << "Food coords: " << foodCoords.x << ", " << foodCoords.y << "          "  << endl;
}

void gameLoop() {
    Direction dir = player.getDirection();
    if (GetAsyncKeyState(VK_RIGHT)) {
        if (!(dir == Direction::LEFT)) player.setDirection(Direction::RIGHT);
    }
    if (GetAsyncKeyState(VK_LEFT)) {
        if (!(dir == Direction::RIGHT)) player.setDirection(Direction::LEFT);
    }
    if (GetAsyncKeyState(VK_DOWN)) {
        if (!(dir == Direction::UP)) player.setDirection(Direction::DOWN);
    }
    if (GetAsyncKeyState(VK_UP)) {
        if (!(dir == Direction::DOWN)) player.setDirection(Direction::UP);
    }
    /*
    [DEBUG]
    if (GetAsyncKeyState(VK_SPACE)) {
        system("pause>nul");
    }*/
    player.move();
}

void spawnFood() {
    int i = rand() % 28 + 1, j = rand() % 28 + 1;
    while ((i == 0 || i == 29 || j == 0 || j == 29) || board[i][j] == SNAKE_PIECE) {
        i = rand() % 28 + 1;
        j = rand() % 28 + 1;
    }
    board[i][j] = FOOD;
    foodCoords.x = i;
    foodCoords.y = j;
}
