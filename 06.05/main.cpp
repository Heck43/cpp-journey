#include <iostream>
#include <windows.h>

void task1();
void task2();
void task3();
void task5();

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    int choice = 0;

    while (true) {
        std::cout << "\nвыберите задачу\n";
        std::cout << "1. Человек (конструкторы, this, счётчик)\n";
        std::cout << "2. Строка (String, конструкторы)\n";
        std::cout << "3. Массив (Array, сортировка, мин/макс)\n";
        std::cout << "5. Телефонная книга\n";
        std::cout << "0. выйти\n";
        std::cout << "твой выбор: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            while (std::cin.get() != '\n');
            std::cout << "введи циферку -w-\n";
            continue;
        }

        if (choice == 0) { std::cout << "пока-пока!\n"; break; }

        switch (choice) {
        case 1: task1(); break;
        case 2: task2(); break;
        case 3: task3(); break;
        case 5: task5(); break;
        default: std::cout << "нет такой задачи\n"; break;
        }
    }
    return 0;
}
