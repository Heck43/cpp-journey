#define NOMINMAX

#include <iostream>
#include <windows.h>

// ===== Задание 3: Класс «Array» (динамический массив) =====

class Array {
private:
    int* data;  // указатель на массив в куче
    int  size;  // текущий размер массива

public:
    // Конструктор с размером — создаёт пустой массив нужного размера
    Array(int sz = 0) : size(sz) {
        if (size > 0) {
            data = new int[size]();  // () — инициализация нулями
        } else {
            data = nullptr;
        }
    }

    // Конструктор копирования — делает глубокую копию данных
    Array(const Array& other) : size(other.size) {
        if (size > 0) {
            data = new int[size];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        } else {
            data = nullptr;
        }
    }

    // Деструктор
    ~Array() {
        delete[] data;
    }

    // Заполнить массив значениями вручную
    void fill() {
        std::cout << "Введите " << size << " чисел:" << std::endl;
        for (int i = 0; i < size; i++) {
            std::cout << "  [" << i << "]: ";
            std::cin >> data[i];
        }
    }

    // Вывести содержимое массива
    void print() const {
        std::cout << "[ ";
        for (int i = 0; i < size; i++) {
            std::cout << data[i];
            if (i < size - 1) std::cout << ", ";
        }
        std::cout << " ]" << std::endl;
    }

    // Изменить размер массива — сохраняет старые данные, новые заполняет нулями
    void resize(int newSize) {
        int* newData = new int[newSize]();
        int  copyCount = (newSize < size) ? newSize : size; // берём минимум
        for (int i = 0; i < copyCount; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        size = newSize;
    }

    // Сортировка пузырьком — простая и понятная
    void sort() {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (data[j] > data[j + 1]) {
                    int temp   = data[j];
                    data[j]   = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }
    }

    // Минимальный элемент
    int min() const {
        int m = data[0];
        for (int i = 1; i < size; i++) {
            if (data[i] < m) m = data[i];
        }
        return m;
    }

    // Максимальный элемент
    int max() const {
        int m = data[0];
        for (int i = 1; i < size; i++) {
            if (data[i] > m) m = data[i];
        }
        return m;
    }

    int getSize() const { return size; }
};

void task3() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Array arr(5);
    arr.fill();

    std::cout << "Массив: "; arr.print();
    std::cout << "Мин: " << arr.min() << ", Макс: " << arr.max() << std::endl;

    arr.sort();
    std::cout << "После сортировки: "; arr.print();

    // Конструктор копирования
    Array arr2(arr);
    arr2.resize(8);
    std::cout << "Копия с resize до 8: "; arr2.print();
}
