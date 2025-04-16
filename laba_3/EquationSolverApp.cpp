#include "EquationSolverApp.h"
#include "SolverFactory.h"
#include "Complex.h"
#include <iostream>
#include <fstream>

using namespace std;

void EquationSolverApp::run() {
    string inputSource, method, s;
    Complex x1(0, 0), x2(0, 0);

    cout << "Choose input method:\n1. Console\n2. File\n";
    cin >> inputSource;

    if (inputSource == "2") {
        ifstream file("for_laba1.txt");
        if (!file || file.peek() == ifstream::traits_type::eof()) {
            cout << "File is empty or not found.\n";
            return;
        }
        getline(file, s);
    }
    else if (inputSource == "1") {
        cout << "Enter your equation:\n";
        cin.ignore();
        getline(cin, s);
    }
    else {
        cout << "Invalid input method.\n";
        return;
    }

    cout << "Choose solving method:\n1. Discriminant\n2. Vieta\n";
    cin >> method;

    ISolver* solver = SolverFactory::createSolver(method);
    if (!solver) {
        cout << "Invalid solving method.\n";
        return;
    }

    solver->solve(s, x1, x2);
    delete solver;

    cout << "/////////////\n";
}
