#include <iostream>

using namespace std;

#include "tcomplejo.h"

int main(void) {
    TComplejo c1(3,4), c2(3,6), c3;

    c3 = c1 + c2;
    cout << c3 << endl;

    c3 = c1 + 7;
    cout << c3 << endl;

    c3 = 7 + c3;
    cout << c3 << endl;

    c3 = c1 + 7;
    cout << c3 << endl;
    
    return 0;
}