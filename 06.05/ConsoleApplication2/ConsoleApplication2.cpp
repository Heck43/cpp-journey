#include <iostream>
#include <cstring>
#include <windows.h>

// ===== Задание 2: Класс «String» =====

class String {
private:
    char* data;    // указатель на строку в куче
    int   capacity; // размер выделенного буфера

    // Вспомогательный метод — выделить память и скопировать строку
    void allocAndCopy(const char* src, int size) {
        capacity = size;
        data = new char[capacity];
        // Если передали исходную строку — копируем, иначе заполняем нулями
        if (src != nullptr) {
            strncpy_s(data, capacity, src, capacity - 1);
            data[capacity - 1] = '\0'; // гарантируем завершающий ноль
        } else {
            data[0] = '\0';
        }
    }

public:
    // Конструктор по умолчанию — строка длиной 80 символов, пустая
    String() {
        allocAndCopy(nullptr, 80);
    }

    // Конструктор с размером — строка произвольного размера, пустая
    String(int size) {
        allocAndCopy(nullptr, size > 0 ? size : 80);
    }

    // Конструктор из готовой строки — инициализирует данными из src
    String(const char* src) {
        int len = (int)strlen(src) + 1;
        allocAndCopy(src, len);
    }

    // Конструктор копирования
    String(const String& other) {
        allocAndCopy(other.data, other.capacity);
    }

    // Деструктор
    ~String() {
        delete[] data;
    }

    // Ввод строки с клавиатуры — читаем в буфер до конца строки
    void input() {
        std::cin.getline(data, capacity);
    }

    // Вывод строки на экран
    void print() const {
        std::cout << data;
    }

    // Вернуть длину хранимой строки
    int length() const {
        return (int)strlen(data);
    }

    // Вернуть вместимость буфера
    int getCapacity() const {
        return capacity;
    }
};

void task2() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Конструктор по умолчанию — 80 символов
    String s1;
    std::cout << "s1 (по умолчанию), вместимость: " << s1.getCapacity() << std::endl;

    // Конструктор с размером
    String s2(200);
    std::cout << "s2 (200 символов), вместимость: " << s2.getCapacity() << std::endl;

    // Конструктор из строки
    String s3("Привет, мир!");
    std::cout << "s3: "; s3.print(); std::cout << " (длина: " << s3.length() << ")" << std::endl;

    // Конструктор копирования
    String s4(s3);
    std::cout << "s4 (копия s3): "; s4.print(); std::cout << std::endl;

    // Ввод с клавиатуры
    std::cout << "\nВведите строку: ";
    s1.input();
    std::cout << "Вы ввели: "; s1.print(); std::cout << std::endl;
}
