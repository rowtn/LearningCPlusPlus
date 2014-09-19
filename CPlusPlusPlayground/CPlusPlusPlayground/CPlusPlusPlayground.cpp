// CPlusPlusPlayground.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "windows.h"
#include <string>
#include <ctime>

using namespace std;

int _tmain(int argc, _TCHAR* argv[]) {
    int max = 0;
    int list[100];
    srand(time(0));
    for (int i = 0; i < 100; i++) {
        list[i] = rand();
    }
    for (int i = 0; i < 100; i++) {
        cout << "heh:\t " << list[i] << endl;
        if (max < list[i]) max = list[i];
    }
    cout << "The max number is:\t" << max << endl;
    system("pause");
    return 0;
}
