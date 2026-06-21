#include <iostream>
#include <stdexcept>  // Для std::invalid_argument при делении на ноль
#include <windows.h>

// ===== Задание 1.1: Класс Fraction с перегрузкой операторов =====

class Fraction {
private:
    int numerator;
    int denominator;

    int gcd(int a, int b) const {
        a = (a < 0) ? -a : a;
        b = (b < 0) ? -b : b;
        while (b) { int t = b; b = a % b; a = t; }
        return a;
    }

    void reduce() {
        if (denominator < 0) { numerator = -numerator; denominator = -denominator; }
        int g = gcd(numerator, denominator);
        numerator /= g; denominator /= g;
    }

public:
    Fraction(int num = 0, int den = 1) : numerator(num), denominator(den) {
        if (den == 0) throw std::invalid_argument("Знаменатель не может быть нулём!");
        reduce();
    }

    // ===== Арифметические операторы =====

    // a/b + c/d = (a*d + c*b) / (b*d)
    Fraction operator+(const Fraction& o) const {
        return Fraction(numerator * o.denominator + o.numerator * denominator,
                        denominator * o.denominator);
    }

    Fraction operator-(const Fraction& o) const {
        return Fraction(numerator * o.denominator - o.numerator * denominator,
                        denominator * o.denominator);
    }

    Fraction operator*(const Fraction& o) const {
        return Fraction(numerator * o.numerator, denominator * o.denominator);
    }

    // a/b / c/d = a/b * d/c
    Fraction operator/(const Fraction& o) const {
        if (o.numerator == 0) throw std::invalid_argument("Деление на ноль!");
        return Fraction(numerator * o.denominator, denominator * o.numerator);
    }

    // ===== Операторы сравнения =====
    // Приводим к одному знаменателю и сравниваем числители
    bool operator==(const Fraction& o) const { return numerator * o.denominator == o.numerator * denominator; }
    bool operator!=(const Fraction& o) const { return !(*this == o); }
    bool operator< (const Fraction& o) const { return numerator * o.denominator <  o.numerator * denominator; }
    bool operator> (const Fraction& o) const { return numerator * o.denominator >  o.numerator * denominator; }

    // ===== Операторы ввода/вывода =====
    // friend — разрешаем оператору видеть private-поля
    friend std::ostream& operator<<(std::ostream& os, const Fraction& f) {
        return os << f.numerator << "/" << f.denominator;
    }

    friend std::istream& operator>>(std::istream& is, Fraction& f) {
        char slash;
        int num, den;
        is >> num >> slash >> den;  // ожидаем формат: 3/4
        f = Fraction(num, den);
        return is;
    }
};

void task1() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    Fraction a(1, 2);
    Fraction b(3, 4);

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "a + b = " << (a + b) << std::endl;
    std::cout << "a - b = " << (a - b) << std::endl;
    std::cout << "a * b = " << (a * b) << std::endl;
    std::cout << "a / b = " << (a / b) << std::endl;
    std::cout << "a == b: " << (a == b ? "да" : "нет") << std::endl;
    std::cout << "a < b:  " << (a <  b ? "да" : "нет") << std::endl;

    // Проверка ввода через >>
    std::cout << "\nВведите дробь (например, 2/3): ";
    Fraction c;
    std::cin >> c;
    std::cout << "Вы ввели: " << c << std::endl;
    std::cout << "a + введённая = " << (a + c) << std::endl;

    // Проверка исключения при делении на ноль
    try {
        Fraction zero(0, 1);
        Fraction bad = a / zero;
    } catch (const std::invalid_argument& e) {
        std::cout << "\nПойманное исключение: " << e.what() << std::endl;
    }
}
