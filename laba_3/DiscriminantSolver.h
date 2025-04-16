#ifndef DISCRIMINANTSOLVER_H
#define DISCRIMINANTSOLVER_H

#include "ISolver.h"

class DiscriminantSolver : public ISolver {
public:
    void solve(const std::string& equation, Complex& x1, Complex& x2) override;
};

#endif
