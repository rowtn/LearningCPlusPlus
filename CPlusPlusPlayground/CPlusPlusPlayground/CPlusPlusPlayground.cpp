// CPlusPlusPlayground.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

void taskOne(void);
void taskTwo(void);
void taskThree(void);
void taskFour(void);

int _tmain(int argc, _TCHAR* argv[]) {
    system("pause");
    return 0;
}

/*Arrays are not needed for this task.*/
void taskOne() {
    int foo[10];
    int evenCount = 0, evenSum = 0;
    for (int i = 0; i < 10; i++) {
        cout << "Enter number " << i + 1 << " for the list:\t" << endl;
        cin >> foo[i];
        if (foo[i] % 2 == 0) {
            evenCount++;
            evenSum += foo[i];
        }
    }
    cout << "There were " << evenCount << " even numbers, and their average is " << evenSum / evenCount << ".";
}

void taskTwo() {
    string currentWord = "";
    for (int i = 0; i < 10; i++) {
        cout << "Enter word number " << i + 1 << ":\t";
        string foo;
        cin >> foo;
        if (foo.size() > currentWord.size()) {
            currentWord = foo;
        }
        cout << endl;
    }
    cout << "The longest word was \"" << currentWord << "\"." << endl;
}

void taskThree() {
    int totalPayable = 0;
    for (int i = 0; i < 10; i++) {
        cout << "Enter the salary for Employee #" << i + 1 << ":\t";
        int foo;
        cin >> foo;
        totalPayable += foo;
    }
    cout << "You will have to pay anually $" << totalPayable << " to your employees." << endl;
}

void taskFour() {
    string students[10];
    int grades[10];
    for (int i = 0; i < 10; i++) {
        cout << "Enter Student #" << i + 1 << "'s name: \t";
        cin >> students[i];
        cout << "Enter their grade:\t";
        cin >> grades[i];
    }
    cout << "Enter a student's name to see their grade:\t";
    string student;
    cin >> student;
    int grade;
    for (int i = 0; i < 10; i++) {
        if (students[i] == student) {
            grade = grades[i];
            goto finish;
        }
    }
    goto end;
finish:
    cout << student << "'s grade was " << grade << ".\n";
end:
}
