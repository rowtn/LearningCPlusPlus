// CPlusPlusPlayground.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "windows.h"
#include <string>

using namespace std;

bool gameRunning = true;
char map[10][20] = {
    "###################",
    "#@                #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "###################"
};

//Character coords
int x = 1, y = 1;

int _tmain(int argc, _TCHAR* argv[]) {
start:
    int posX, posY;
    posX = rand() % 8 + 1;
    posY = rand() % 8 + 1;
    map[posY][posX] = '+';
    while (gameRunning) {
        system("cls");
        for (int display = 0; display < 10; display++) {
            cout << map[display] << endl;
        }
        system("pause>null");

        if (GetAsyncKeyState(VK_DOWN)) {
            int yTo = y + 1;
            if (map[yTo][x] == ' ') {
                map[y][x] = ' ';
                map[yTo][x] = '@';
                y = yTo;
            }
            else if (map[yTo][x] == '+') {
                map[y][x] = ' ';
                map[yTo][x] = '@';
                cout << "You win!!" << endl;
                gameRunning = false;
            }
        } else if (GetAsyncKeyState(VK_UP)) {
            int yTo = y - 1;
            if (map[yTo][x] == ' ') {
                map[y][x] = ' ';
                map[yTo][x] = '@';
                y = yTo;
            }
            else if (map[yTo][x] == '+') {
                map[y][x] = ' ';
                map[yTo][x] = '@';
                cout << "You win!!" << endl;
                gameRunning = false;
            }
        }
        else if (GetAsyncKeyState(VK_RIGHT)) {
            int xTo = x + 1;
            if (map[y][xTo] == ' ') {
                map[y][x] = ' ';
                map[y][xTo] = '@';
                x = xTo;
            }
            else if (map[y][xTo] == '+') {
                map[y][x] = ' ';
                map[y][xTo] = '@';
                cout << "You win!!" << endl;
                gameRunning = false;
            }
        }
        else if (GetAsyncKeyState(VK_LEFT)) {
            int xTo = x - 1;
            if (map[y][xTo] == ' ') {
                map[y][x] = ' ';
                map[y][xTo] = '@';
                x = xTo;
            }
            else if (map[y][xTo] == '+') {
                map[y][x] = ' ';
                map[y][xTo] = '@';
                cout << "You win!!" << endl;
                gameRunning = false;
            }
        }
    }
    cout << "Would you liek to play again? (y/n) \t";
    string input;
    cin >> input;
    if (input == "y") {
        map[y][x] = ' ';
        x = 1;
        y = 1;
        map[y][x] = '@';
        gameRunning = true;
        goto start;
    }
    else {
        cout << "Bye, have a great time!" << endl;
    }
    system("pause");
	return 0;
}

