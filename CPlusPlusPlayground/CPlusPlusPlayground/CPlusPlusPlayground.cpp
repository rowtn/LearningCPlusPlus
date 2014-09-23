// CPlusPlusPlayground.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <windows.h>

using namespace std;

char lines[3][3];
char possible[5] = { '+', '*', '$', '@', '~' };
const int MAX_ITERATIONS = 10;

void display(void);

int _tmain(int argc, _TCHAR* argv[]) {
start:
    srand(time(0));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            lines[i][j] = possible[rand() % 5];
        }
    }
    display();
    int iterations = 0;
    while (iterations < MAX_ITERATIONS) {
        for (int i = 0; i < 3; i++) {
            lines[2][i] = lines[1][i];
            lines[1][i] = lines[0][i];
            lines[0][i] = possible[rand() % 5];
        }
        system("cls");
        display();
        iterations++;
        Sleep(iterations * 50);
    }
    /*Checking for wins*/
    bool won = false;
    for (int i = 0; i < 3; i++) {
        if (lines[i][0] == lines[i][1] && lines[i][1] == lines[i][2]) {
            won = true;
            cout << "[DEBUG] horizontal line " << i + 1 << endl;
            break;
        }
        if (lines[0][i] == lines[1][i] && lines[2][i] == lines[1][i]) {
            won = true;
            cout << "[DEBUG] vertical line " << i + 1 << endl;
            break;
        }
    }
    if (lines[0][0] == lines[1][1] && lines[2][2] == lines[1][1]) {
        won = true;
        cout << "[DEBUG] diagonal top right" << endl;
    }
    if (lines[2][0] == lines[1][1] && lines[1][1] == lines[0][2]) {
        won = true;
        cout << "[DEBUG] diagonal bottom right" << endl;
    }
    if (won) {
        cout << "You won!" << endl;
    }
    else {
        cout << "You lost :(" << endl;
    }
    cout << "Would you like to play again? (y/n)" << endl;
prompt:
    system("pause>null");
    if (GetAsyncKeyState('Y')) {
        system("cls");
        goto start;
    }
    else if (GetAsyncKeyState('N')) {
        cout << "Bye, have a great time!" << endl;
    }
    else {
        cout << "Sorry, what was that?" << endl;
        goto prompt;
    }
    system("pause");
    return 0;
}

void display() {
    cout << "-------" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << "-";
            cout << lines[i][j];
        }
        cout << "-";
        cout << endl;
    }
    cout << "-------" << endl;
}
