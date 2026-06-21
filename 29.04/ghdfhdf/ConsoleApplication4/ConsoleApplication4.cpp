#include <iostream>
#include <cstring>  // Для strlen, strcpy_s
#include <windows.h>

// Задача 4: «Банковский счёт»
// Инкапсуляция + конструктор с проверками + ручное управление памятью

class BankAccount {
private:
    char* owner;        // имя владельца (в куче, управляем через new/delete)
    int accountNumber;  // номер счёта
    double balance;     // текущий баланс

public:
    // Конструктор — создаёт счёт с проверкой начального баланса
    BankAccount(const char* ownerName, int accNumber, double initialBalance) {
        // Выделяем память и копируем имя через strcpy_s (безопасная версия strcpy)
        owner = new char[strlen(ownerName) + 1];
        strcpy_s(owner, strlen(ownerName) + 1, ownerName);

        accountNumber = accNumber;

        // Проверяем начальный баланс — отрицательный не допускается
        if (initialBalance < 0) {
            std::cout << "Предупреждение: начальный баланс не может быть отрицательным. Установлен 0." << std::endl;
            balance = 0;
        } else {
            balance = initialBalance;
        }
    }

    // Деструктор — освобождаем память от имени владельца
    ~BankAccount() {
        delete[] owner;
    }

    // Пополнить счёт — сумма должна быть строго положительной
    void deposit(double amount) {
        if (amount <= 0) {
            std::cout << "Ошибка: сумма пополнения должна быть больше нуля." << std::endl;
            return;
        }
        balance += amount;
        std::cout << "Счёт пополнен на " << amount << " руб. Новый баланс: " << balance << " руб." << std::endl;
    }

    // Снять деньги — возвращает false если денег не хватает
    bool withdraw(double amount) {
        if (amount > balance) {
            std::cout << "Ошибка: недостаточно средств. На счету: " << balance << " руб." << std::endl;
            return false;
        }
        balance -= amount;
        std::cout << "Снято " << amount << " руб. Остаток: " << balance << " руб." << std::endl;
        return true;
    }

    // Аксессор для получения текущего баланса
    double getBalance() {
        return balance;
    }

    // Вывод полной информации о счёте
    void printInfo() {
        std::cout << "Владелец: " << owner << std::endl;
        std::cout << "Счёт №: " << accountNumber << std::endl;
        std::cout << "Баланс: " << balance << " руб." << std::endl;
    }
};

void task4() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Создаём счёт с нормальным начальным балансом
    BankAccount acc("Иван Иванов", 1001, 5000.0);
    acc.printInfo();

    std::cout << std::endl;

    // Пополняем счёт
    acc.deposit(3000.0);

    // Снимаем допустимую сумму
    acc.withdraw(2000.0);

    std::cout << std::endl;

    // Попытка снять больше, чем есть на счёте
    acc.withdraw(99999.0);

    std::cout << std::endl;

    // Попытка пополнить на отрицательную сумму
    acc.deposit(-500.0);

    std::cout << std::endl;

    // Создаём счёт с отрицательным балансом — должно сработать предупреждение
    BankAccount badAcc("Пётр Петров", 1002, -1000.0);
    badAcc.printInfo();

}
