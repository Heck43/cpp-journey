#include <iostream>
#include <cstring>  // Для strlen, strcpy_s
#include <windows.h>

// Задача 5: «Термометр»
// Демонстрируем перегрузку конструкторов — один класс, три способа создать объект

class Thermometer {
private:
    double celsius;   // температура в градусах Цельсия
    char* location;   // место измерения (в куче, управляем через new/delete)

    // Вспомогательный метод для копирования строки в поле location
    // Вынесли логику сюда, чтобы не повторять её в каждом конструкторе
    void setLocation(const char* place) {
        location = new char[strlen(place) + 1];
        strcpy_s(location, strlen(place) + 1, place);
    }

public:
    // Конструктор 1: по умолчанию — температура 0, место "Неизвестно"
    Thermometer() {
        celsius = 0.0;
        setLocation("Неизвестно");
    }

    // Конструктор 2: только температура — место по умолчанию "Неизвестно"
    Thermometer(double tempCelsius) {
        celsius = tempCelsius;
        setLocation("Неизвестно");
    }

    // Конструктор 3: и место, и температура — полная инициализация
    Thermometer(const char* place, double tempCelsius) {
        celsius = tempCelsius;
        setLocation(place);
    }

    // Деструктор — освобождаем память от строки location
    ~Thermometer() {
        delete[] location;
    }

    // Аксессор: вернуть температуру в Цельсиях
    double getCelsius() {
        return celsius;
    }

    // Аксессор: перевести и вернуть температуру в Фаренгейтах
    // Формула: F = C * 9/5 + 32
    double getFahrenheit() {
        return celsius * 9.0 / 5.0 + 32.0;
    }

    // Вывод полной информации о замере
    void printInfo() {
        std::cout << "Место: " << location << std::endl;
        std::cout << "Температура: " << celsius << " °C / " << getFahrenheit() << " °F" << std::endl;
    }
};

void task5() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Объект 1: конструктор по умолчанию
    Thermometer t1;
    std::cout << "--- Термометр 1 (по умолчанию) ---" << std::endl;
    t1.printInfo();

    std::cout << std::endl;

    // Объект 2: конструктор с одним параметром — только температура
    Thermometer t2(36.6);
    std::cout << "--- Термометр 2 (только температура) ---" << std::endl;
    t2.printInfo();

    std::cout << std::endl;

    // Объект 3: конструктор с двумя параметрами — место и температура
    Thermometer t3("Улица", -15.5);
    std::cout << "--- Термометр 3 (место + температура) ---" << std::endl;
    t3.printInfo();

}
