#include "VietaSolver.h"
#include "for_laba_1.h"
#include <iostream>
using namespace std;

void VietaSolver::solve(const std::string& equation, Complex& x1, Complex& x2) {
    formula_Vieta(equation, x1, x2);
}