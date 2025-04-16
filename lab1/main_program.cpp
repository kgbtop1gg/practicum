#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cctype> 
#include <stdexcept>
#include <cmath>
#include "for_laba_1.h"
#include "Complex.h"
using namespace std;
int main()
{
    string inputSource, filePath, s;
    Complex x1(0, 0);
    Complex x2(0, 0);
    cout << "Choose your input method: " << endl;
    cout << "1. Console" << endl;
    cout << "2. File" << endl;
    cin >> inputSource;

    if (inputSource == "2") {
        ifstream file("for_laba1.txt");
        if (file.peek() == ifstream::traits_type::eof()) {
            cout << "The file is empty" << endl;
        }
        else {

            getline(file, s);
            cout << "s=" << s << endl;
            cout << "Choose your input method: " << endl;
            cout << "1. Discriminant" << endl;
            cout << "2. Vieta" << endl;
            cin >> inputSource;
            if (inputSource == "1") {
                discriminat(s, x1, x2);
            }
            else if (inputSource == "2") {
                formula_Vieta(s, x1, x2);
            }
            else { cout << "You have entered an uncorrected command, the job is done."; return 0; }

        }
    }
    else if (inputSource == "1") {
        cin >> s;
        cout << "s=" << s << endl;
        cout << "Choose your input method: " << endl;
        cout << "1. Discriminant" << endl;
        cout << "2. Vieta" << endl;
        cin >> inputSource;
        if (inputSource == "1") {
            discriminat(s, x1, x2);
        }
        else if (inputSource == "2") {
            formula_Vieta(s, x1, x2);
        }
        else { cout << "You have entered an uncorrected command, the job is done."; return 0; }
    }
    else { cout << "You have entered an uncorrected command, the job is done."; return 0; }

    /* Complex a(0, 0); Complex b(0, 0);
     a.setValues(2, 10);
     b.setValues(6, 50);
     Complex c(0, 0);
     c.symm(a, b);
     c.print();
     c.minys(b, a);
     c.print();
     c.division(b, a);
     c.print();*/
    cout << "/////////////" << endl;
    int a = 16;
    int n = 4;
    get_n_roots(n, a);
}