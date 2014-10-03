#pragma once
class Player {
private:
    int length = 3, x, y;
public:

    Player(int i, int j) {
        x = i;
        y = j;
    }

    int getLength() {
        return length;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

};
