#include "for_laba_1.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cctype> 
#include <stdexcept>
#include <cmath>
#include "Complex.h"

using namespace std;

void get_n_roots(int n, int a) {
    Complex x(0, 0);
    if (n == 0) { x.print(); }
    else {
        int r = pow(a, 1.0 / n);
        for (int k = 0; k < n; k++) {
            x.setValues(r * cos(2 * 3.14 * k / n), r * sin(2 * 3.14 * k / n));
            x.print();
        }
    }

};

void check_simvol(char Sim, string& pod_slovo, double& coefficient, bool& mistake) {
    switch (Sim) {
    case '+': {
        mistake = false; coefficient = 0;
        break;
    }
    case '-': {
        mistake = false; coefficient = 0;
        break;
    }

    case '.': {
        if (pod_slovo.find(".") != std::string::npos) { mistake = false; coefficient = 0; }
        else {
            if (pod_slovo != "") { pod_slovo += Sim; }
            else { mistake = false;  coefficient = 0; }
        }
        break;
    }

    case '*': {
        if (pod_slovo == "") { mistake = false; coefficient = 0; }
        else { coefficient = coefficient * stod(pod_slovo); }
        pod_slovo = "";
        break;
    }

    default: {
        if (isdigit(Sim)) { pod_slovo += Sim; }
        else { mistake = false; coefficient = 0; }
        break;
    }
    }
}

void split_x(string slovo, int sign, double& a, double& b, double& c, bool& mistake) {
    string pod_slovo = "";
    double prev = 1, last = 1;
    unsigned int u = 0, j = 0;

    if (slovo[0] == '-') { sign = sign * -1; u = 1; }
    else if (slovo[0] == '+') { u = 1; }
    else if (slovo[0] == '*') { mistake = false; };  /////////////////////////////

    while ((u <= slovo.size() - 1) and (mistake != false) and (slovo[u] != 'x')) {
        check_simvol(slovo[u], pod_slovo, prev, mistake);
        u += 1;
    }
    if ((mistake == true) && (pod_slovo != "")) { prev = prev * stod(pod_slovo); }

    if (u + 1 == slovo.size()) { b = b + sign * prev; }
    else
    { // Извлечение коэффициента после 'x'
        u += 1;
        if (slovo[slovo.size() - 1] == '*') { mistake = false; last = 0; };

        // Определение типа коэффицента
        if (slovo[u] == '*') { pod_slovo = "1"; j = 2; }
        else
        {
            if (isdigit(slovo[u])) {
                pod_slovo = slovo[u];
                double e = stod(pod_slovo);
                if (e > 2) { mistake = false; }                                                                                                 /////////////////
                else if (e == 0) { j = 1; }
                else if (e == 2) { j = 3; }
                else if (e == 1) { j = 2; };
                pod_slovo = "1";
                u += 1;
            }
            else { mistake = false; }                                                                                                                          //////////////////
        }
        if ((j != 0) and (u + 1 <= slovo.size())) { if (slovo[u] != '*') { mistake = false; last = 0; } }

        // Выделение множителя
        while ((u <= slovo.size() - 1) and (mistake != false)) {
            check_simvol(slovo[u], pod_slovo, last, mistake);
            u += 1;
        }
        if (pod_slovo != "") { last = last * stod(pod_slovo); }

        if (j == 2) { b = b + sign * prev * last; }
        else if (j == 3) { a = a + sign * prev * last; }
        else if (j == 1) { c = c + sign * prev * last; }
    }
   // cout << b << "  ss " << last << "  " << j << "  " << mistake << "  " << sign << "  " << u << endl;
}


void split_s(std::string s, bool& mistake, double& a, double& b, double& c) {
    string slovo;
    int sign = 1, q = 1, sign_ch = 1;
    bool flag, flag1, fun;
    flag = false; flag1 = false; fun = false;
    a = 0; b = 0; c = 0;
    s += " ";

    // БЛОК РАЗДЕЛЕНИЯ КОЭФФИЦЕНТОВ
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '+' || s[i] == '-' || s[i] == '=' || i == s.size() - 1) {
            bool f;
            //cout << "slovo =|" << slovo << "s[i]=" << s[i] << endl;
            //cout << mistake << endl;
            // ОБРАБОТКА ЗНАКА МЕЖДУ ЧИСЛАМИ

            if (!slovo.empty())
            {
                f = false;

                if (slovo.find("x") != std::string::npos) {
                    sign_ch =   sign_ch * sign * q;
                    split_x(slovo, sign_ch, a, b, c, mistake);
                    sign_ch = 1; sign = 1;
                }
                else
                {
                    try { c += sign * sign_ch * q * stod(slovo); sign = 1; sign_ch = 1; }
                    catch (const invalid_argument& c) { mistake = false; }
                }
                slovo.clear(); 

                if (s[i + 1] == '-' || s[i + 1] == '+') { mistake = false; }
                if (s[i + 1] != ' ') {
                    if (s[i] == '+') { sign_ch = 1; };
                    if (s[i] == '-') { sign_ch = -1; };
                }
                else {
                    if (s[i] == '+') { sign = 1; };
                    if (s[i] == '-') { sign = -1; };
                }
            }
            else {
                if (s[i + 1] == ' ') { mistake = false; }
                else {
                   if (s[i] == '+') { sign_ch = 1; };
                   if (s[i] == '-') { sign_ch = -1; };
                }
            }
            if ((s[i] == '=') && (flag == true)) { mistake = false; } /////////////////////////
            else  if ((s[i] == '=') && (flag == false)) { flag = true; q = -1; };
        }
        else {
            if (s[i] != ' ') { slovo += s[i]; }
        }
    }
    if (mistake == false || q != -1) { a = 0; b = 0; c = 0; }
    cout << a << " | " << b << " | " << c << " | " << mistake << endl;
}

void discriminat(std::string s, Complex& x1, Complex& x2) {
    double a, b, c;
    double D;
    bool mistake = true;
    split_s(s, mistake, a, b, c);
    //cout << "Our coefficients" << endl;

    if (a != 0) {
        D = b * b - 4 * a * c;
        if (D > 0) {
            D = sqrt(D);
            x1.setValues((-b - D) / (2 * a), 0);
            x2.setValues((-b + D) / (2 * a), 0);
            x1.print();
            x2.print();
        }
        else if (D < 0) {
            D = -1 * D;
            D = sqrt(D);
            b = -1 * b;
            x1.setValues(b / (2 * a), D / (2 * a));
            x2.setValues(b / (2 * a), -1 * D / (2 * a));
            x1.print();
            x2.print();
        }
        else if (D == 0) {
            x1.setValues(-1 * b / (2 * a), 0);
            x1.print();
        }
    }
    else { cout << " This equation is non-square! "; }
}

void formula_Vieta(std::string s, Complex x1, Complex x2) {
    double a, b, c;
    double D;
    bool mistake = true;
    split_s(s, mistake, a, b, c);
    double discriminant = b * b - 4 * a * c;
    if (a != 0) {
    // Если дискриминант отрицательный, то корней нет
    if (discriminant < 0) {
        cout << "This equation doesn't have roots." << endl;
    }
    else {
        double x1_plus_x2, x1_times_x2;

        x1_plus_x2 = -b / a;  // Сумма корней (x1 + x2)
        x1_times_x2 = c / a;  // Произведение корней (x1 * x2)

        // Вычисление корней через сумму и произведение
        // x1 и x2 являются корнями квадратного уравнения
        x1.setValues((x1_plus_x2 + sqrt(x1_plus_x2 * x1_plus_x2 - 4 * x1_times_x2)) / 2, 0);
        x2.setValues((x1_plus_x2 - sqrt(x1_plus_x2 * x1_plus_x2 - 4 * x1_times_x2)) / 2, 0);

        // Вывод корней
        cout << "Roots of equation: x1" << endl;
        x1.print();
        x2.print();
    }
    }
    else { cout << " This equation is non-square! "; }
}