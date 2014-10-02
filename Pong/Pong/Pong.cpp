// Pong.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

char board[20][60];
const int BALL = 233, WALLX = 219, WALLY = 220;
int ballX = 0, ballY = 0;

void populate(void);
void display(void);

int _tmain(int argc, _TCHAR* argv[]) {
    system("color a");
    populate();
    display();
    system("pause");
	return 0;
}

void populate() {
    for (int x = 0; x < 20; x++) {
        for (int y = 0; y < 60; y++) {
            if (x == 19 || x == 0) {
                board[x][y] = char(WALLY);
            }
            if (y == 59 || y == 0) {
                board[x][y] = char(WALLX);
            }
        }
    }
}

void display() {
    for (int x = 0; x < 20; x++) {
        for (int y = 0; y < 60; y++) {
            cout << board[x][y];
        }
        cout << endl;
    }
}
