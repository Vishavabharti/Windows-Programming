/*++

Module Name:
			MathExecRefsLib.cpp

Abstract:
			This module handles creation of static file

--*/

#include <iostream>
#include "MathFuncsLib.h"

using namespace std;

int main()
{
    int a = 20;
    int b = 10;

    cout << "a + b = " <<
        MathFuncs::MyMathFuncs::Add(a, b) << endl;
    cout << "a - b = " <<
        MathFuncs::MyMathFuncs::Subtract(a, b) << endl;
    cout << "a * b = " <<
        MathFuncs::MyMathFuncs::Multiply(a, b) << endl;
    cout << "a / b = " <<
        MathFuncs::MyMathFuncs::Divide(a, b) << endl;

    return 0;
}
