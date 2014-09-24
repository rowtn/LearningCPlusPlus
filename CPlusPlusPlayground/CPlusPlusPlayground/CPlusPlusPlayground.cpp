// CPlusPlusPlayground.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <math.h>
#include <string>
#include <windows.h>

using namespace std;

int _tmain(int argc, _TCHAR* argv[]) {
    string foo;
    cin >> foo;
    double result = 0;
    for (int i = 0; i < 8; i++) {
        cout << i << "\t" << foo[i] << endl;
        if (foo[i] == '1') {
            result += pow(2, 7 - i);
            cout << "Result:\n" << result << endl;
        }
    }
    cout << result;
    system("pause");
    return 0;
}
