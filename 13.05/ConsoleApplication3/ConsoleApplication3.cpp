#include <iostream>
#include <stdexcept>
#include <windows.h>

// ===== Задание 1.3: Шаблонный класс Matrix<T> =====
// Шаблон — класс умеет работать с любым типом T (int, double и т.д.)

template<typename T>
class Matrix {
private:
    T** data;    // двумерный массив в куче
    int rows;
    int cols;

    // Выделить память
    void alloc() {
        data = new T*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new T[cols]();  // () — инициализация нулями
        }
    }

    // Освободить память
    void free() {
        for (int i = 0; i < rows; i++) delete[] data[i];
        delete[] data;
    }

    // Проверка что размеры совпадают — иначе операция невозможна
    void checkSize(const Matrix& o) const {
        if (rows != o.rows || cols != o.cols)
            throw std::invalid_argument("Размеры матриц не совпадают!");
    }

public:
    Matrix(int r, int c) : rows(r), cols(c) { alloc(); }

    // Конструктор копирования (правило трёх)
    Matrix(const Matrix& o) : rows(o.rows), cols(o.cols) {
        alloc();
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                data[i][j] = o.data[i][j];
    }

    // Оператор присваивания (правило трёх) — с защитой от самоприсваивания
    Matrix& operator=(const Matrix& o) {
        if (this == &o) return *this;  // a = a — ничего не делаем
        free();
        rows = o.rows; cols = o.cols;
        alloc();
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                data[i][j] = o.data[i][j];
        return *this;
    }

    ~Matrix() { free(); }

    // ===== Доступ к элементу: matrix(i,j) =====
    T& operator()(int i, int j)             { return data[i][j]; }
    const T& operator()(int i, int j) const { return data[i][j]; }

    // ===== Арифметика =====

    Matrix operator+(const Matrix& o) const {
        checkSize(o);
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                result(i,j) = data[i][j] + o.data[i][j];
        return result;
    }

    Matrix operator-(const Matrix& o) const {
        checkSize(o);
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                result(i,j) = data[i][j] - o.data[i][j];
        return result;
    }

    // Умножение матриц: A(n×m) * B(m×k) = C(n×k)
    Matrix operator*(const Matrix& o) const {
        if (cols != o.rows)
            throw std::invalid_argument("Для умножения: столбцы A должны равняться строкам B!");
        Matrix result(rows, o.cols);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < o.cols; j++)
                for (int k = 0; k < cols; k++)
                    result(i,j) += data[i][k] * o.data[k][j];
        return result;
    }

    // Умножение на скаляр
    Matrix operator*(T scalar) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                result(i,j) = data[i][j] * scalar;
        return result;
    }

    // ! — транспонирование (строки и столбцы меняются местами)
    Matrix operator!() const {
        Matrix result(cols, rows);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                result(j,i) = data[i][j];
        return result;
    }

    // ===== Сравнение =====
    bool operator==(const Matrix& o) const {
        if (rows != o.rows || cols != o.cols) return false;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                if (data[i][j] != o.data[i][j]) return false;
        return true;
    }
    bool operator!=(const Matrix& o) const { return !(*this == o); }

    // ===== Вывод =====
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m) {
        for (int i = 0; i < m.rows; i++) {
            os << "[ ";
            for (int j = 0; j < m.cols; j++) {
                os << m.data[i][j];
                if (j < m.cols - 1) os << "\t";
            }
            os << " ]\n";
        }
        return os;
    }

    // ===== Ввод =====
    friend std::istream& operator>>(std::istream& is, Matrix& m) {
        std::cout << "Введите " << m.rows << "x" << m.cols << " элементов построчно:\n";
        for (int i = 0; i < m.rows; i++)
            for (int j = 0; j < m.cols; j++)
                is >> m.data[i][j];
        return is;
    }
};

void task3() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    Matrix<int> a(2, 2);
    a(0,0)=1; a(0,1)=2;
    a(1,0)=3; a(1,1)=4;

    Matrix<int> b(2, 2);
    b(0,0)=5; b(0,1)=6;
    b(1,0)=7; b(1,1)=8;

    std::cout << "A:\n" << a;
    std::cout << "B:\n" << b;
    std::cout << "A + B:\n" << (a + b);
    std::cout << "A - B:\n" << (a - b);
    std::cout << "A * B:\n" << (a * b);
    std::cout << "A * 3:\n" << (a * 3);
    std::cout << "!A (транспонирование):\n" << (!a);
    std::cout << "A == B: " << (a == b ? "да" : "нет") << std::endl;

    // Правило трёх: конструктор копирования и присваивание
    Matrix<int> c = a;  // конструктор копирования
    c(0,0) = 99;
    std::cout << "Копия c (изменённая):\n" << c;
    std::cout << "Оригинал a (не изменился):\n" << a;
}
