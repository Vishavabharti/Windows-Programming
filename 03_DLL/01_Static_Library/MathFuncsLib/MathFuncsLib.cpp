/*++

Module Name:
			MathFuncsLib.cpp

Abstract:
			This module handles creation of static file

--*/

#include <stdexcept>
#include "MathFuncsLib.h"

using namespace std;

namespace MathFuncs
{
    double MyMathFuncs::Add(double a, double b)
    {
        return a + b;
    }

    double MyMathFuncs::Subtract(double a, double b)
    {
        return a - b;
    }

    double MyMathFuncs::Multiply(double a, double b)
    {
        return a * b;
    }

    double MyMathFuncs::Divide(double a, double b)
    {
        return a / b;
    }
}
