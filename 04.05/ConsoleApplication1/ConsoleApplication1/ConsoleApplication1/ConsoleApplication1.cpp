#include <iostream>

// ДЗ 04.05 — Задача 1: «Дробь»
// Класс для работы с простыми дробями: сокращение, арифметика, цепочки вызовов

class Fraction {
private:
    int numerator;    // числитель
    int denominator;  // знаменатель

    // НОД (наибольший общий делитель) по алгоритму Евклида — нужен для сокращения
    int gcd(int a, int b) const {
        a = (a < 0) ? -a : a;
        b = (b < 0) ? -b : b;
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    // Сокращение дроби — вызывается в конструкторе автоматически
    void reduce() {
        // Знак всегда хранится в числителе, знаменатель всегда положительный
        if (denominator < 0) {
            numerator   = -numerator;
            denominator = -denominator;
        }
        int g = gcd(numerator, denominator);
        numerator   /= g;
        denominator /= g;
    }

public:
    // Конструктор с параметрами — список инициализаторов + сокращение в конструкторе
    Fraction(int num, int den) : numerator(num), denominator(den) {
        reduce(); // сразу сокращаем при создании
    }

    // Конструктор по умолчанию — делегирует конструктору с параметрами (0/1 = 0)
    Fraction() : Fraction(0, 1) {}

    // Вывод дроби на экран
    void print() const {
        std::cout << numerator << "/" << denominator;
    }

    // ===== Арифметика дробь + дробь =====

    // Сложение: a/b + c/d = (a*d + c*b) / (b*d)
    Fraction& add(const Fraction& other) {
        numerator   = numerator * other.denominator + other.numerator * denominator;
        denominator = denominator * other.denominator;
        reduce();
        return *this; // возвращаем ссылку на себя — для цепочки вызовов
    }

    // Вычитание: a/b - c/d = (a*d - c*b) / (b*d)
    Fraction& sub(const Fraction& other) {
        numerator   = numerator * other.denominator - other.numerator * denominator;
        denominator = denominator * other.denominator;
        reduce();
        return *this;
    }

    // Умножение: a/b * c/d = (a*c) / (b*d)
    Fraction& mul(const Fraction& other) {
        numerator   = numerator   * other.numerator;
        denominator = denominator * other.denominator;
        reduce();
        return *this;
    }

    // ===== Арифметика дробь + целое число =====
    // Целое число n — это дробь n/1, поэтому просто подставляем

    // Сложение с целым: a/b + n = (a + n*b) / b
    Fraction& add(int n) {
        numerator += n * denominator;
        reduce();
        return *this;
    }

    // Вычитание целого: a/b - n = (a - n*b) / b
    Fraction& sub(int n) {
        numerator -= n * denominator;
        reduce();
        return *this;
    }

    // Умножение на целое: a/b * n = (a*n) / b
    Fraction& mul(int n) {
        numerator *= n;
        reduce();
        return *this;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    // Конструктор по умолчанию — делегирует в Fraction(0, 1)
    Fraction zero;
    std::cout << "Дробь по умолчанию: ";
    zero.print();
    std::cout << std::endl;

    // Обычные дроби — сокращение происходит сразу в конструкторе
    Fraction a(2, 4);   // станет 1/2
    Fraction b(3, 9);   // станет 1/3
    std::cout << "a = "; a.print(); std::cout << "  (из 2/4)" << std::endl;
    std::cout << "b = "; b.print(); std::cout << "  (из 3/9)" << std::endl;

    std::cout << std::endl;

    // Арифметика дробь + дробь
    Fraction c(1, 2);
    Fraction d(1, 3);
    std::cout << "1/2 + 1/3 = ";
    Fraction(1, 2).add(Fraction(1, 3)).print();
    std::cout << std::endl;

    std::cout << "1/2 - 1/3 = ";
    Fraction(1, 2).sub(Fraction(1, 3)).print();
    std::cout << std::endl;

    std::cout << "1/2 * 2/3 = ";
    Fraction(1, 2).mul(Fraction(2, 3)).print();
    std::cout << std::endl;

    std::cout << std::endl;

    // Арифметика дробь + целое число
    std::cout << "1/2 + 2 = ";
    Fraction(1, 2).add(2).print();
    std::cout << std::endl;

    std::cout << "3/4 - 1 = ";
    Fraction(3, 4).sub(1).print();
    std::cout << std::endl;

    std::cout << "2/3 * 3 = ";
    Fraction(2, 3).mul(3).print();
    std::cout << std::endl;

    std::cout << std::endl;

    // Цепочка вызовов через this — 1/6 + 1/6 + 1/6 = 1/2
    std::cout << "Цепочка: 1/6 + 1/6 + 1/6 = ";
    Fraction(1, 6).add(Fraction(1, 6)).add(Fraction(1, 6)).print();
    std::cout << std::endl;
}
