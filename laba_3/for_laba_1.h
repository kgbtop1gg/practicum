#ifndef for_laba_1_H 
#define for_laba_1_H 

#include <string> 
#include "Complex.h"

//class Complex;
void split_s(std::string s, double& a, double& b, double& c);
void discriminat(std::string s, Complex& x1, Complex& x2);
void formula_Vieta(std::string s, Complex x1, Complex x2);
void get_n_roots(int n, int a);
#endif 