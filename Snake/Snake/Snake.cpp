// Snake.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdarg.h>
#include <ctime>
#include <string>
#include <Windows.h>
#include <list>
#include <algorithm>
#include <fstream>
#include <mmsystem.h>
#include <thread>

using namespace std;

/* Variables */
bool gameRunning = true;
bool TRON_MUSIC = true;

char board[30][30];

void initBoard(void);
void display(void);
void gameLoop(void);
void spawnFood(void);
void music(void);

const char FOOD = char(248);
const char SNAKE_PIECE = char(178);
const char EMPTY = ' ';

enum Direction {
    UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4
};

enum Note {
    C4 = 262, Cs4 = 277, D4 = 294, Ds4 = 311, E4 = 330, F4 = 349, Fs4 = 370, G4 = 392, Gs4 = 415, A4 = 440, As4 = 466, B4 = 494,
    C5 = 523, Cs5 = 554, D5 = 587, Ds5 = 622, E5 = 659, F5 = 698, Fs5 = 740, G5 = 784, Gs5 = 831, A5 = 880, As5 = 932, B5 = 986,
    C6 = 1047, Cs6 = 1109, D6 = 1775, Ds6 = 1245, E6 = 1319, F6 = 1397, Fs6 = 1480, G6 = 1568, Gs6 = 1661, A6 = 1760, As6 = 1865, B6 = 1976
};

struct IntPair {
    int x, y;

    bool operator==(IntPair& a) const {
        return (x == a.x && y == a.y);
    }

};

void addToBoard(IntPair, char);

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
        addPiece = true;
        spawnFood();
    }

    void placeOnBoard() {
        for (list<IntPair>::iterator it = pieces.begin(); it != pieces.end(); ++it) {
            addToBoard(*it, SNAKE_PIECE);
        }
        addToBoard(*pieces.begin(), char(177));
    }

    list<IntPair> getAllPieces() {
        return pieces;
    }

    void move() {
        IntPair end = pieces.back();
        addToBoard(end, EMPTY);

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
        int i = next.x, j = next.y;
        if (i == 0 || i == 29 || j == 0 || j == 29) {
            gameRunning = false;
            return;
        }

        IntPair front = pieces.front();
        if (front.x == foodCoords.y && front.y == foodCoords.x) {
            eat();
        }

        if (board[next.y][next.x] == SNAKE_PIECE) {
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
int highScore = 0;

int _tmain(int argc, _TCHAR* argv[]) {
    /* Init */
    TRON_MUSIC = (time(NULL) % 2 == 0);
    string foo;
    cout << "Do you want to listen to the computer think?\t";
    cin >> foo;
    if (foo == "yes" || foo == "y") {
        TRON_MUSIC = true;
    }
    else {
        TRON_MUSIC = false;
    }
    srand(time(NULL));
    system("mode 32,36");
    SMALL_RECT WinRect = { 0, 0, 31, 40 };
    SMALL_RECT* WinSize = &WinRect;
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, WinSize);

    /* read highscores from file */
    ifstream hsFile;
    hsFile.open("highscores.txt");
    hsFile >> highScore;
    hsFile.close();

    initBoard();
    player.placeOnBoard();
    spawnFood();
    thread t(music);
    t.detach();
    while (gameRunning) {
        gameLoop();
        COORD position = { 0, 0 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
        display();
        cout << " Score:\t\t" << player.getLength() * 10 << endl;
        cout << " High score:\t" << highScore << endl;
    }
    system("cls");
    cout << endl << " Your final score was " << player.getLength() * 10 << "!" << endl;
    if (player.getLength() * 10 > highScore) {
        cout << " You beat the high score!" << endl;
        remove("highscores.txt");
        ofstream hs;
        hs.open("highscores.txt");
        hs << player.getLength() * 10;
        hs.close();
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
            cout << board[i][j];
        }
        cout << endl;
    }
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

void addToBoard(IntPair i, char c) {
    board[i.y][i.x] = c;
}

void music() {
    while (true) {
        if (TRON_MUSIC) { 
            Beep(rand() % 1800 + 200, 200); 
        }
        else {
            Beep(D5, 200);
            Beep(Ds5, 200);
            Beep(E5, 200);
            Beep(C6, 400);
            Beep(E5, 200);
            Beep(C6, 400);
            Beep(E5, 200);
            Beep(C6, 400);
            Beep(C5, 200);
            Beep(D5, 200);
            Beep(Ds5, 200);
            Beep(E5, 200);
            Beep(C5, 200);
            Beep(D5, 200);
            Beep(E5, 200);
            Beep(B4, 200);
            Beep(C5, 0);
            Beep(B4, 200);
            Beep(D5, 400);
            Beep(C5, 600);

            Beep(D5, 200);
            Beep(Ds5, 200);
            Beep(E5, 200);
            Beep(C6, 400);
            Beep(E5, 200);
            Beep(C6, 400);
            Beep(E5, 200);
            Beep(C6, 400);
            Beep(A5, 200);
            Beep(G5, 200);
            Beep(Fs5, 200);
            Beep(A4, 200);
            Beep(C5, 200);
            Beep(E5, 400);
            Beep(D5, 200);
            Beep(C5, 200);
            Beep(A4, 200);
            Beep(D5, 600);

            Beep(D5, 200);
            Beep(Ds5, 200);
            Beep(E5, 200);
            Beep(C6, 400);
            Beep(E5, 200);
            Beep(C6, 400);
            Beep(E5, 200);
            Beep(C6, 400);
            Beep(C5, 200);
            Beep(D5, 200);
            Beep(Ds5, 200);
            Beep(E5, 200);
            Beep(C5, 200);
            Beep(D5, 200);
            Beep(E5, 200);
            Beep(B4, 200);
            Beep(C5, 0);
            Beep(B4, 200);
            Beep(D5, 400);
            Beep(C5, 600);

            Beep(C5, 200);
            Beep(D5, 200);
            Beep(E5, 200);
            Beep(C5, 200);
            Beep(D5, 200);
            Beep(E5, 400);
            Beep(C5, 200);
            Beep(D5, 200);
            Beep(E5, 200);
            Beep(C5, 200);
            Beep(D5, 200);
            Beep(E5, 400);
            Beep(C5, 200);
            Beep(D5, 200);
            Beep(E5, 200);
            Beep(C5, 200);
            Beep(D5, 200);
            Beep(E5, 400);
            Beep(B4, 200);
            Beep(D5, 400);
            Beep(C5, 600);
        }
    }
}
