#include <iostream>
#include <windows.h>

void task1();  // 1.1 Fraction — перегрузка операторов
void task2();  // 1.2 Vector3D — перегрузка операторов
void task3();  // 1.3 Matrix<T> — шаблонный класс
void task4();  // 2.1 Shape — наследование, полиморфизм
void task5();  // 2.2 Employee + Department — наследование

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    int choice = 0;

    while (true) {
        std::cout << "\nвыберите задачу\n";
        std::cout << "1. Fraction (перегрузка +,-,*,/,==,<<,>>)\n";
        std::cout << "2. Vector3D (перегрузка +,-,*,++,[],+=)\n";
        std::cout << "3. Matrix<T> (шаблон, правило трёх, !)\n";
        std::cout << "4. Фигуры (Circle, Rectangle, Triangle)\n";
        std::cout << "5. Сотрудники (Manager, Developer, Intern, Department)\n";
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
        case 4: task4(); break;
        case 5: task5(); break;
        default: std::cout << "нет такой задачи\n"; break;
        }
    }
    return 0;
}
