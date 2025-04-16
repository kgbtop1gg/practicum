#pragma once
class Complex
{
private:
    double real;   // Действительная часть
    double imag;   // Мнимая часть
public:
    // Конструктор для создания комплексного числа
    Complex(double r, double i) : real(r), imag(i) {}

    // Метод для установки значений
    void setValues(double r, double i);

    // Метод для печати комплексного числа
    void print();

    // Метод суммы 
    void symm(Complex num1, Complex num2);

    //
    void minys(Complex num1, Complex num2);

    //
    void multiplication(Complex num1, Complex num2);

    //
    void division(Complex num1, Complex num2);

    //
    void exponentiation(Complex& num1, double n);

    //
    void root_extraction(Complex num, double n);

};

