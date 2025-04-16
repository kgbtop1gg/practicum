#ifndef ISOLVER_H
#define ISOLVER_H

#include <string>
#include "Complex.h"

class ISolver {
public:
    virtual void solve(const std::string& equation, Complex& x1, Complex& x2) = 0;
    virtual ~ISolver() = default;
};

#endif
