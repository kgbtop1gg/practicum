#ifndef SOLVERFACTORY_H
#define SOLVERFACTORY_H

#include <string>
#include "ISolver.h"

class SolverFactory {
public:
    static ISolver* createSolver(const std::string& method);
};

#endif
