// Space Invaders.cpp 3: Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>
#include <Windows.h>
#include <thread>
#include <vector>
#include <list>
#include <curses.h>

using namespace std;

bool gameRunning = true;
bool won = false;

void init(void);
void display(void);
void gameLoop(void);
void startShoot(int, int, string);
void clearScreen(void);
void hitEnemy(void);

class Player;
class Bullet;
class Enemy;

enum Dir {
    RIGHT, LEFT, STOP
};

const char bar = char(178);
const string barrier[2] = { { bar, bar, bar }, { bar, bar, bar } };
/*char enemyAvatar[3][7] = {
    "  ╔╩╗  ", 
    "╬═╬╦╬═╬",//[2][2] = firing point
    " ╬   ╬"};
*/
char enemyAvatar[3][7] = {
        { ' ', ' ', char(201), char(202), char(187), ' ', ' ' },
        { char(206), char(203), char(206), char(203), char(206), char(203), char(206) },
        { ' ', char(206), ' ', ' ', ' ', char(206), ' ' }
};
char board[30][30];
const string playerAvatar = { char(205), char(202), char(205) };
const char bullet = char(167);
Dir currentDirection = STOP;
list<Bullet> bullets;
int bulletCount = -1;

class Player {
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
        if (j < 29) x = j;
    }

    void move(Dir dir) {
        if (dir == RIGHT) {
            if (x < 26) {
                for (int i = 0; i < 3; i++) {
                    board[y][x + i] = ' ';
                }
                x++;
                for (int i = 0; i < 3; i++) {
                    board[y][x + i] = avatar[i];
                }
            }
        }
        else if (dir == LEFT) {
            if (x > 1) {
                for (int i = 0; i < 3; i++) {
                    board[y][x + i] = ' ';
                }
                x--;
                for (int i = 0; i < 3; i++) {
                    board[y][x + i] = avatar[i];
                }
            }
        }
    }
    void fire() {
        startShoot(x + 1, y - 1, "player");
    }
};

class Bullet {
private:
    int x, y;
    string shooter;
    bool alive = true;
public:
    Bullet(int i, int j, string s) {
        x = i;
        y = j;
        shooter = s;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    void move() {
        if (!alive) return;
        if (shooter == "player") {
            if (y < 2) {
                board[y][x] = ' ';
                return;
            }
            switch (board[y - 1][x]) {
            case bar:
                board[y][x] = ' ';
                board[y - 1][x] = ' ';
                alive = false;
                return;
            }
            char foo = board[y - 1][x];
            if (foo == char(201) || foo == char(202) || foo == char(187) || foo == char(206) || foo == char(203) || foo == char(205)) {
                board[y][x] = ' ';
                board[y - 1][x] = ' ';
                alive = false;
                hitEnemy();
                return;
            }
            board[y][x] = ' ';
            y--;
            board[y][x] = bullet;
        }
        else {
            if (y > 27) {
                board[y][x] = ' ';
                return;
            }
            switch (board[y + 1][x]) {
            case bar:
                board[y][x] = ' ';
                board[y + 1][x] = ' ';
                alive = false;
                return;
            case char(202) :
                won = false;
                gameRunning = false;
                return;
            case char(205):
                won = false;
                gameRunning = false;
                return;
            }
            board[y][x] = ' ';
            y++;
            board[y][x] = bullet;
        }
    }
};

class Enemy {
private:
    int x, y, health = 10, shootCount = 10 + (rand() % 5);;
    Dir direction = RIGHT;
public:
    Enemy(int i, int j) {
        x = i;
        y = j;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    int getHealth() {
        return health;
    }

    void update() {
        if (--shootCount < 1) {
            shootCount = 5 + (rand() % 10);
            startShoot(y + 2, x + 2, "enemy");
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 7; j++) {
                board[i + x][j + y] = ' ';
            }
        }
        if (direction == RIGHT) {
            if (y > 20) {
                direction = LEFT;
                x++;
            }
            else y++;
        }
        else if (direction == LEFT) {
            if (y <= 1) {
                direction = RIGHT;
                x++;
            }
            else y--;
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 7; j++) {
                board[i + x][j + y] = enemyAvatar[i][j];
            }
        }
    }

    void hit() {
        health--;
        if (health <= 0) {
            won = true;
            gameRunning = false;
        }
    }

};

Player player = Player(3, 28, playerAvatar);
Enemy enemy = Enemy(3, 1);

int _tmain(int argc, _TCHAR* argv[]) {
    srand(time(NULL));
    initscr();
    system("mode 32,36");   //Set mode to ensure window does not exceed buffer size
    SMALL_RECT WinRect = { 0, 0, 31, 40 };   //New dimensions for window in 8x12 pixel chars
    SMALL_RECT* WinSize = &WinRect;
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, WinSize);   //Set new size for window
    init();
    enemy.update();
    display();
    long t = GetTickCount();
    clearScreen();
    while (gameRunning) {
        gameLoop();
    }
    clear();
    system("cls");
    refresh();
    cout << "\n\n\n\n\n";
    if (won) {
        cout << "       /===================\\" << endl;
        cout << "       |                   |" << endl;
        cout << "       |       YOU WIN     |" << endl;
        cout << "       |                   |" << endl;
        cout << "       \\===================/" << endl;
    }
    else {
        cout << "       /==================\\" << endl;
        cout << "       |                  |" << endl;
        cout << "       |      YOU LOSS    |" << endl;
        cout << "       |                  |" << endl;
        cout << "       \\==================/" << endl;
    }
    refresh();
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
    /* assign player in thingy */
    for (int i = 0; i < 3; i++) {
        board[player.getY()][player.getX() + i] = avatar[i];
    }
}

void display() {
    for (int i = 0; i < 30; i++) {
        cout << ' ';
        for (int j = 0; j < 30; j++) {
            cout << board[i][j];
        }
        cout << endl;
    }
}

void gameLoop() {
    clearScreen();
    if (GetAsyncKeyState(VK_RIGHT)) {
        currentDirection = RIGHT;
    }
    if (GetAsyncKeyState(VK_LEFT)) {
        currentDirection = LEFT;
    }
    if (GetAsyncKeyState(VK_DOWN)) {
        currentDirection = STOP;
    }
    if (GetAsyncKeyState(VK_SPACE)) {
        player.fire();
    }
    for (list<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it) {
        it->move();
    }
    player.move(currentDirection);
    enemy.update();
    display();
    cout << " X:\t" << player.getX() << "\n Y:\t" << player.getY() << endl << " Enemy health:\t" << enemy.getHealth() << endl;
    Sleep(50);
}

void startShoot(int x, int y, string shooter) {
    bullets.push_back(Bullet(x, y, shooter));
}

void clearScreen() {
    refresh();
}

void hitEnemy() {
    enemy.hit();
}
