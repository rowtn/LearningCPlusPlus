// Space Invaders.cpp 3: Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

void init(void);
void display(void);
void gameLoop(void);
struct Player;
enum Dir {
    RIGHT, LEFT
};

const char bar = char(178);
const string barrier[2] = { { bar, bar, bar }, { bar, bar, bar } };
char board[30][30];
const string playerAvatar = { char(205), char(202), char(205) };

struct Player {
private:
    int x, y;
    string avatar;
public:
    Player(int j, int i, string s) {
        y = i;
        x = j;
        avatar = s;
    }

    string getAvatar() {
        return avatar;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    bool coordIsPlayer(int cx, int cy) {
        return (cx < x + 3 && cy == y);
    }

    void setPositionX(int j) {
        if (j < 29 ) x = j;
    }

    void move(Dir dir) {
        if (dir == RIGHT) {
            if (x < 28) {
                x++; 
            }
        }
        else if (dir == LEFT) {
            if (x > 1) x--;
        }
    }
};

Player player = Player(3, 28, playerAvatar);

bool gameRunning = true;

int _tmain(int argc, _TCHAR* argv[]) {
    init();
    display();
    while (gameRunning) {
        gameLoop();
    }
    cin.get();
	return 0;
}

void init() {
    string avatar = player.getAvatar();
    int startY = 3, startX = 24, gap = 5;
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            if (i == 0 || i == 29 || j == 0 || j == 29) board[i][j] = char(219);
        }
    }
    for (int n = 0; n < 3; n++) {
        for (int numOfBars = 0; numOfBars < 5; numOfBars++) {
            board[startX][startY + n + gap * numOfBars] = bar;
            board[startX + 1][startY + n + gap * numOfBars] = bar;
        }
    }
    /*assign player in thingy*/
    for (int i = 0; i < 3; i++) {
        board[player.getY()][player.getX() + i] = avatar[i];
    }
}

void display() {
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            cout << board[i][j];
        }
        cout << endl;
    }
}

void gameLoop() {
    system("cls");
    if (GetAsyncKeyState(VK_RIGHT)) {
        for (int i = 0; i < 3; i++) {
            board[player.getY()][player.getX() + i] = ' ';
        }
        player.move(RIGHT);
        for (int i = 0; i < 3; i++) {
            board[player.getY()][player.getX() + i] = player.getAvatar()[i];
        }
    }
    if (GetAsyncKeyState(VK_LEFT)) {
        for (int i = 0; i < 3; i++) {
            board[player.getY()][player.getX() + i] = ' ';
        }
        player.move(LEFT);
        for (int i = 0; i < 3; i++) {
            board[player.getY()][player.getX() + i] = player.getAvatar()[i];
        }
    }
    display();
    cout << player.getX() << " and " << player.getY() << endl;
    system("pause");
}