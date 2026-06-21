#include <iostream>
#include <windows.h>

void task1();
void task2();
void task3();
void task4();
void task5();
void task6();

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
  int choice = 0;

  while (true) {
    std::cout << "\nвыберите задачу\n";
    std::cout << "1-6. запустить нужную задачку \n";
    std::cout << "0. выйти из программы\n";
    std::cout << "твой выбор: ";

    if (!(std::cin >> choice)) {
      // если ввели букву то очищяем ее
      std::cin.clear();
      while (std::cin.get() != '\n')
        ;
      std::cout << "глупенький, введи циферку \n";
      continue;
    }

    if (choice == 0) {
      std::cout << "пока-пока! \n";
      break;
    }

    switch (choice) {
    case 1:
      task1();
      break;
    case 2:
      task2();
      break;
    case 3:
      task3();
      break;
    case 4:
      task4();
      break;
    case 5:
      task5();
      break;
    case 6:
      task6();
      break;
    default:
      std::cout << "введите от 1 до 6 -w-\n";
      break;
    }
  }
  return 0;
}