#include "DiscriminantSolver.h"
#include "for_laba_1.h"
#include <iostream>
using namespace std;

void DiscriminantSolver::solve(const std::string& equation, Complex& x1, Complex& x2) {
    discriminat(equation, x1, x2);
}