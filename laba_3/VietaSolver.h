#ifndef VIETASOLVER_H
#define VIETASOLVER_H

#include "ISolver.h"

class VietaSolver : public ISolver {
public:
    void solve(const std::string& equation, Complex& x1, Complex& x2) override;
};

#endif