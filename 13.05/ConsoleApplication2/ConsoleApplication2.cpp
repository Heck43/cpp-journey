#include <iostream>
#include <cmath>  // Для sqrt — длина вектора
#include <windows.h>

// ===== Задание 1.2: Класс Vector3D с перегрузкой операторов =====

class Vector3D {
private:
    double x, y, z;
    static int count;  // счётчик созданных векторов

public:
    Vector3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) { count++; }
    Vector3D(const Vector3D& o) : x(o.x), y(o.y), z(o.z) { count++; }
    ~Vector3D() { count--; }

    static int getCount() { return count; }

    // ===== Арифметика =====

    Vector3D operator+(const Vector3D& o) const { return Vector3D(x+o.x, y+o.y, z+o.z); }
    Vector3D operator-(const Vector3D& o) const { return Vector3D(x-o.x, y-o.y, z-o.z); }

    // Скалярное произведение: a·b = ax*bx + ay*by + az*bz
    double operator*(const Vector3D& o) const { return x*o.x + y*o.y + z*o.z; }

    // Умножение на скаляр (число)
    Vector3D operator*(double s) const { return Vector3D(x*s, y*s, z*s); }

    // ===== Составные присваивания =====
    Vector3D& operator+=(const Vector3D& o) { x+=o.x; y+=o.y; z+=o.z; return *this; }
    Vector3D& operator-=(const Vector3D& o) { x-=o.x; y-=o.y; z-=o.z; return *this; }
    Vector3D& operator*=(double s)           { x*=s;   y*=s;   z*=s;   return *this; }

    // ===== Инкремент =====

    // Префиксный: ++v — сначала увеличиваем, потом возвращаем
    Vector3D& operator++() { x++; y++; z++; return *this; }

    // Постфиксный: v++ — сохраняем копию, увеличиваем, возвращаем старую копию
    // int — фиктивный параметр, чтобы компилятор отличил постфикс от префикса
    Vector3D operator++(int) { Vector3D old(*this); ++(*this); return old; }

    // ===== Доступ по индексу =====
    // 0 = x, 1 = y, 2 = z
    double& operator[](int i) {
        if (i == 0) return x;
        if (i == 1) return y;
        if (i == 2) return z;
        throw std::out_of_range("Индекс вектора должен быть 0, 1 или 2");
    }

    const double& operator[](int i) const {
        if (i == 0) return x;
        if (i == 1) return y;
        if (i == 2) return z;
        throw std::out_of_range("Индекс вектора должен быть 0, 1 или 2");
    }

    // Длина вектора: sqrt(x² + y² + z²)
    double length() const { return std::sqrt(x*x + y*y + z*z); }

    friend std::ostream& operator<<(std::ostream& os, const Vector3D& v) {
        return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    }
};

int Vector3D::count = 0;

void task2() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    std::cout << "Векторов сейчас: " << Vector3D::getCount() << std::endl;

    Vector3D a(1, 2, 3);
    Vector3D b(4, 5, 6);
    std::cout << "Векторов сейчас: " << Vector3D::getCount() << std::endl;

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "a + b = " << (a + b) << std::endl;
    std::cout << "a - b = " << (a - b) << std::endl;
    std::cout << "a · b (скалярное) = " << (a * b) << std::endl;
    std::cout << "a * 2 = " << (a * 2.0) << std::endl;
    std::cout << "|a| = " << a.length() << std::endl;

    // Доступ по индексу
    std::cout << "a[0]=" << a[0] << " a[1]=" << a[1] << " a[2]=" << a[2] << std::endl;

    // Инкременты
    Vector3D c(1, 1, 1);
    std::cout << "\nc = " << c << std::endl;
    std::cout << "++c = " << ++c << " (c стал: " << c << ")" << std::endl;
    std::cout << "c++ = " << c++ << " (c стал: " << c << ")" << std::endl;

    // Составные присваивания
    a += b;
    std::cout << "\nПосле a += b: " << a << std::endl;
}
