#include "SolverFactory.h"
#include "DiscriminantSolver.h"
#include "VietaSolver.h"

ISolver* SolverFactory::createSolver(const std::string& method) {
    if (method == "1") {
        return new DiscriminantSolver();
    }
    else if (method == "2") {
        return new VietaSolver();
    }
    else {
        return nullptr;
    }
}