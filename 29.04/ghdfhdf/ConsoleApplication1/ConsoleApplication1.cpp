#include <iostream>
#include <windows.h>
#include <cstring>  // Для strcpy_s — безопасное копирование строки в char[]

// Задача 1: «Товар на складе»
// Было: struct Product + отдельные функции printProduct и calculateTotalCost
// Стало: class Product — данные и методы объединены внутри одного класса

class Product {
public:
    // Поля класса — хранят данные о товаре
    // char name[50] вместо std::string — как было в исходном задании
    char name[50];
    int quantity;     // количество единиц на складе
    double price;     // цена за одну единицу в рублях

    // Метод вывода информации о товаре
    // Аналог функции printProduct из процедурного кода
    void print() {
        std::cout << "Товар: " << name << std::endl;
        std::cout << "Количество на складе: " << quantity << " шт." << std::endl;
        std::cout << "Цена за единицу: " << price << " руб." << std::endl;
    }

    // Метод расчёта общей стоимости всех единиц товара
    // Аналог функции calculateTotalCost из процедурного кода
    double getTotalCost() {
        return quantity * price;
    }
};

void task1() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Создаём объект класса Product (раньше создавали переменную типа struct)
    Product item;

    // Присваиваем значения полям объекта
    // strcpy нужен для char[], обычное = для него не работает
    strcpy_s(item.name, sizeof(item.name), "Монитор");
    item.quantity = 15;
    item.price = 15000.0;

    // Вызываем методы — теперь они прямо внутри объекта, не снаружи
    item.print();

    std::cout << "Общая стоимость: " << item.getTotalCost() << " руб." << std::endl;

}
