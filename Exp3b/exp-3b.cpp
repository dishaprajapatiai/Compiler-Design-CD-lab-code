#include <iostream>
#include "text.h"   // include user-defined header file

using namespace std;

int main() {
    string str;
    cout << "Enter a string: ";
    cin >> str;

    if (isConstant(str)) {
        cout << str << " is an integer constant." << endl;
    } else {
        cout << str << " is NOT an integer constant." << endl;
    }

    return 0;
}
