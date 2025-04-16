#include "Complex.h"
#include <iostream>
#include <cmath>
using namespace std;


void Complex::setValues(double r, double i) {
    real = r;
    imag = i;
}

void Complex::print() {
    if (imag >= 0) {
        std::cout << real << " + " << imag << "i" << std::endl;
    }
    else {
        std::cout << real << " - " << -imag << "i" << std::endl;
    }
}

void Complex::symm(Complex num1, Complex num2) {
    real = num1.real + num2.real;
    imag = num1.imag + num2.imag;   
}

void Complex::minys(Complex num1, Complex num2) {
    real = num1.real - num2.real;
    imag = num1.imag - num2.imag;
}

void Complex::multiplication(Complex num1, Complex num2) {
    real = num1.real * num2.real - num1.imag * num2.imag;
    imag = num1.real * num2.imag - num1.imag * num2.real;
}

void Complex::division(Complex num1, Complex num2) {
    if ((num2.real == 0) && (num2.imag == 0)) { cout <<"Dividing numbers is impossible" << endl; }
    else 
    {
        real = (num1.real * num2.real + num1.imag * num2.imag) / (num2.real * num2.real + num2.imag * num2.imag);
        imag = (num1.imag * num2.real - num1.real * num2.imag) / (num2.real * num2.real + num2.imag * num2.imag);
    }
}

void Complex::exponentiation(Complex& num, double n) {

    double r = 0;
    r = sqrt(num.real * num.real + num.imag * num.imag);
    double phi = 0;
    
    phi = n * atan2(num.imag, num.real); 
    num.real = pow(r, n) * cos(phi);
    num.imag = pow(r, n) * sin(phi);
}

